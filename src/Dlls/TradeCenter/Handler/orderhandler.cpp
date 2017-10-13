#include <assert.h>
#include "utility/utility_fun.h"
#include "utility/scopeguard.h"
#include "orderhandler.h"
#include "quotehandler.h"
#include "define/struct_extern.h"
#include "define/protocol_error.h"
#include "include/OperationManager/OperationManager.h"
#include "../Application/taskmsg.h"
#include "../Application/taskmsg_order_mgr.h"
#include "../Application/TradeFeeManager.h"
#include "positionlistmanager.h"
#include "positionhandler.h"
#include "tradehandler.h"
#include "tradelistmanager.h"
#include "orderlistmanager.h"
#include "include/ManagerCenter/ManagerCenter.h"
#include "quotelistmanager.h"
#include "../Application/GlobalDataManager.h"
#include "../Application/ForbidTradeManager.h"
#include "../Application/PositionRateManager.h"
#include "../Application/RiskControlManager.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "OrderHandler");

using namespace AllTrade::NPMgrCenter;

namespace AllTrade {
    namespace NPTradeCenter {
        OrderBaseHandler::OrderBaseHandler(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online)
            : m_order_ptr(order_ptr)
            , m_is_modify(true)
            , m_user_online(user_online)
        {
            assert(order_ptr);
            strncpy_s(m_user_id, use_id, sizeof(m_user_id) - 1);
        }

        OrderBaseHandler::~OrderBaseHandler()
        {

        }

        ErrorCodeType OrderBaseHandler::isOrderValid() const
        {
            readLock lock(m_mtx);

            if (strnlen_s(m_user_id, sizeof(m_user_id)) != 0
                && strnlen_s(m_order_ptr->order_stream_, sizeof(m_order_ptr->order_stream_)) != 0
                && strnlen_s(m_order_ptr->contract_id_, sizeof(m_order_ptr->contract_id_)) != 0
                && m_order_ptr->order_state_ != OrderStateType::ORDER_STATE_Invalid
//                 && strnlen_s(m_order_ptr->currency_id_, sizeof(m_order_ptr->currency_id_)) != 0
                && m_order_ptr->currency_rate_ != 0
                && (m_order_ptr->order_price_ > 0.0 || (m_order_ptr->order_type_ == OrderTypeType::ORDER_TYPE_MARKET))
                && m_order_ptr->order_vol_ > 0
                && m_order_ptr->effected_vol_ >= 0 && m_order_ptr->effected_vol_ <= m_order_ptr->order_vol_
                && m_order_ptr->trade_vol_ >= 0 && m_order_ptr->trade_vol_ <= m_order_ptr->order_vol_
                && m_order_ptr->order_type_ != OrderTypeType::ORDER_TYPE_Invalid
                && m_order_ptr->order_trade_mode_ != OrderTradeModeType::ORDERTRADE_MODE_Invalid
                && strnlen_s(m_order_ptr->exchange_id_, sizeof(m_order_ptr->exchange_id_)) != 0
//                 && m_order_ptr->api_type_ != ApiTypeType::APIType_TYPE_Invalid
                && m_order_ptr->commodity_type_ != CommodityTypeType::COMMODITY_TYPE_Invalid
                && m_order_ptr->op_type_ != OperatorTradeType::OPERATOR_TRADE_Invalid
                && m_order_ptr->order_mode_ != OrderModeType::ORDER_MODE_Invalid
                && m_order_ptr->order_vol_ % 100 == 0)
                return Err_Succeed;

            LOG4CXX_INFO(logger, "当前委托无效"LOG_NOVAR(m_user_id)
                LOG_NOVAR(m_order_ptr->order_stream_)LOG_NOVAR((int)m_order_ptr->order_state_)
                LOG_NOVAR(m_order_ptr->contract_id_)LOG_NOVAR((int)m_order_ptr->currency_rate_)
                LOG_NOVAR(m_order_ptr->order_price_)LOG_NOVAR((int)m_order_ptr->order_type_)
                LOG_NOVAR(m_order_ptr->order_vol_)LOG_NOVAR((int)m_order_ptr->effected_vol_)LOG_NOVAR((int)m_order_ptr->trade_vol_)
                LOG_NOVAR((int)m_order_ptr->order_trade_mode_)LOG_NOVAR(m_order_ptr->exchange_id_)
                LOG_NOVAR((int)m_order_ptr->commodity_type_)LOG_NOVAR((int)m_order_ptr->op_type_)
                LOG_NOVAR((int)m_order_ptr->order_mode_));
            return Err_Order_Param_Error;
        }

        bool OrderBaseHandler::isOrderTime() const
        {
            return IManagerCenter::instance()->curCanOrder(CommodityTypeType::COMMODITY_TYPE_STOCK, m_order_ptr->exchange_id_, m_order_ptr->contract_id_);
        }

        bool OrderBaseHandler::isTradeTime() const
        {
            return IManagerCenter::instance()->curCanTrade(CommodityTypeType::COMMODITY_TYPE_STOCK, m_order_ptr->exchange_id_, m_order_ptr->contract_id_);
        }

        AllTrade::ErrorCodeType OrderBaseHandler::canOrder() const
        {
            ErrorCodeType err_code = canTrade();
            if (err_code != Err_Succeed)
                return err_code;

            if (m_order_ptr->direct_type_ == DirectType::DIRECT_SELL)
            {
                PositionHrPtr pos_hr = PositionListManager::instance()->getReversePosition(m_user_id, m_order_ptr->contract_id_, m_order_ptr->direct_type_);
                if (!pos_hr || m_order_ptr->order_vol_ - m_order_ptr->effected_vol_ > pos_hr->getCanCloseVol())
                    return Err_MaxCanCloseVol;

                return Err_Succeed;
            }
            else
            {
                QuoteHrPtr quote_ptr = QuoteListManager::instance()->getQuoteHrByID(m_order_ptr->contract_id_);
                if (!quote_ptr)
                    return Err_No_QuoteInfo;

                return IManagerCenter::instance()->canOrder(m_user_id, getOrderFreezeFee(quote_ptr));
            }
        }

        ErrorCodeType OrderBaseHandler::canTrade() const
        {
            ErrorCodeType err_code= IManagerCenter::instance()->canTradeContract(CommodityTypeType::COMMODITY_TYPE_STOCK, m_order_ptr->exchange_id_, m_order_ptr->contract_id_);
            if (err_code != Err_Succeed)
                return err_code;

            if (!QuoteListManager::instance()->getCurQuoteStatus())
                return Err_No_QuoteInfo;
             
            if (m_order_ptr->order_vol_ <= 0)
            {
                return Err_Order_Param_Error;
            }

            QuoteHrPtr quote_ptr = QuoteListManager::instance()->getQuoteHrByID(m_order_ptr->contract_id_);
            if (!quote_ptr)
                return Err_No_QuoteInfo;

            if (!quote_ptr->canTrade())
            {
                LOG4CXX_INFO(logger, "当前合约处于无法交易状态"LOG_NOVAR(m_order_ptr->contract_id_));
                return Err_Contract_NoTrade;
            }

            if (quote_ptr->isRiseStop() && m_order_ptr->direct_type_ == DirectType::DIRECT_BUY)
                return Error_User_NoOpen_RiseStop;

            if (quote_ptr->isFallStop() && m_order_ptr->direct_type_ == DirectType::DIRECT_SELL)
                return Error_User_NoClose_FallStop;

            if (m_order_ptr->trade_vol_ >= m_order_ptr->order_vol_)
            {
                LOG4CXX_ERROR(logger, "已成交手数大于委托手数"
                    LOG_NOVAR(m_order_ptr->order_stream_)
                    LOG_NOVAR(m_order_ptr->trade_vol_)
                    LOG_NOVAR(m_order_ptr->order_vol_));
                return Err_Unknown;
            }

            if (m_order_ptr->order_state_ == OrderStateType::ORDER_STATE_Invalid
                || m_order_ptr->order_state_ == OrderStateType::ORDER_STATE_FAIL
                || m_order_ptr->order_state_ == OrderStateType::ORDER_STATE_DELETEING
                || m_order_ptr->order_state_ == OrderStateType::ORDER_STATE_PARTDELETED
                || m_order_ptr->order_state_ == OrderStateType::ORDER_STATE_DELETED
                || m_order_ptr->order_state_ == OrderStateType::ORDER_STATE_FINISHED)
                return Err_OrderStatus_Cannot_Trade;

            err_code = ForbidTradeManager::instance()->canTrade(quote_ptr, m_order_ptr->direct_type_);
            if (err_code != Err_Succeed)
                return err_code;

            if (m_order_ptr->direct_type_ == DirectType::DIRECT_SELL)
                return Err_Succeed;

            YDouble highest_price = getOrderFreezeFee(quote_ptr);
            // 风控
            err_code = RiskControlManager::instance()->init_calculate(CommodityTypeType::COMMODITY_TYPE_STOCK, m_user_id, false, false, highest_price);
            if (err_code != Err_Succeed)
                return err_code;

            err_code = PositionRateManager::instance()->canTrade(m_user_id, m_order_ptr->contract_id_, highest_price);
            if (err_code != Err_Succeed)
                return err_code;

            return IManagerCenter::instance()->canTrade(m_user_id, highest_price);
        }

        YDouble OrderBaseHandler::getOrderFreezeFee(const QuoteHrPtr& quote_ptr) const
        {
            if (m_order_ptr->direct_type_ != DirectType::DIRECT_BUY)
                return 0.0;

            // 是否为上交所
            YDouble highest_price(0);

            switch (m_order_ptr->order_type_)
            {
            case AllTrade::OrderTypeType::ORDER_TYPE_LIMIT:
                highest_price = m_order_ptr->order_price_ * m_order_ptr->order_vol_;;
                break;
            case AllTrade::OrderTypeType::ORDER_TYPE_MARKET:
                highest_price = UtilityFun::Round(quote_ptr->getRisePrice() * m_order_ptr->order_vol_, 0.00001);
                break;
            default:
                assert(0);
                break;
            }

            highest_price += UtilityFun::Round(getUserOpenFee(m_order_ptr->direct_type_, highest_price, m_order_ptr->order_vol_), 0.00001);
            return highest_price;
        }

        ErrorCodeType OrderBaseHandler::canCancelOrder() const
        {
            readLock lock(m_mtx);
            if (m_order_ptr->order_vol_ > 0
                && m_order_ptr->trade_vol_ < m_order_ptr->order_vol_
                && m_order_ptr->effected_vol_ < m_order_ptr->order_vol_
                && m_order_ptr->order_state_ != OrderStateType::ORDER_STATE_Invalid
                && m_order_ptr->order_state_ != OrderStateType::ORDER_STATE_FAIL
                && m_order_ptr->order_state_ != OrderStateType::ORDER_STATE_PARTDELETED
                && m_order_ptr->order_state_ != OrderStateType::ORDER_STATE_DELETED
                && m_order_ptr->order_state_ != OrderStateType::ORDER_STATE_FINISHED)
                return Err_Succeed;

            LOG4CXX_INFO(logger, "当前不可撤单"LOG_NOVAR(getOrderStream())LOG_NOVAR(m_order_ptr->order_vol_)LOG_NOVAR(m_order_ptr->trade_vol_)
                                    LOG_NOVAR(m_order_ptr->effected_vol_)LOG_NOVAR((int)m_order_ptr->order_state_));
            return Err_CancelOrder_Cannot_Cancel;
        }

        const POrderIDType OrderBaseHandler::getOrderID() const
        {
            readLock lock(m_mtx);
            return m_order_ptr->order_id_;
        }

        void OrderBaseHandler::setOrderID(const OrderIDType order_id)
        {
            writeLock lock(m_mtx);
            strncpy_s(m_order_ptr->order_id_, order_id, sizeof(m_order_ptr->order_id_) - 1);
            m_is_modify = true;
        }

        AllTrade::PSystemIDType OrderBaseHandler::getSystemOrderID()
        {
            readLock lock(m_mtx);
            return m_order_ptr->system_order_id_;
        }

        void OrderBaseHandler::setSystemOrderID(const SystemIDType sys_order_id)
        {
            writeLock lock(m_mtx);
            strncpy_s(m_order_ptr->system_order_id_, sys_order_id, sizeof(m_order_ptr->system_order_id_) - 1);
            m_is_modify = true;
        }

        const POrderRefType OrderBaseHandler::getOrderRef() const
        {
            readLock lock(m_mtx);
            return m_order_ptr->order_ref_;
        }

        void OrderBaseHandler::setOrderRef(const OrderRefType order_ref)
        {
            writeLock lock(m_mtx);
            strncpy_s(m_order_ptr->order_ref_, order_ref, sizeof(m_order_ptr->order_ref_) - 1);
            m_is_modify = true;
        }

        const PUserIDType OrderBaseHandler::getUserID() const
        {
            return m_user_id;
        }

        const PContractIDType OrderBaseHandler::getContractID() const
        {
            return m_order_ptr->contract_id_;
        }

        AllTrade::OrderStateType OrderBaseHandler::getOrderState() const
        {
            readLock lock(m_mtx);
            return m_order_ptr->order_state_;
        }

        void OrderBaseHandler::setOrderState(OrderStateType order_state)
        {
            LOG4CXX_DEBUG(logger, LOG_NOVAR(getOrderStream())"改变当前委托状态"LOG_NOVAR((int)order_state)"原状态"LOG_NOVAR((int)getOrderState()));

            CommonTools::ScopeGuard ext([&]{
                if (serialize() != Err_Succeed)
                    LOG4CXX_ERROR(logger, LOG_NOVAR(getOrderStream())"修改委托状态时,写入数据库失败"LOG_NOVAR((int)order_state));
            });

            {
                writeLock lock(m_mtx);
                if (m_order_ptr->order_state_ == order_state)
                    return;

                strncpy_s(m_order_ptr->update_datetime_, UtilityFun::getCurrentDateTime().c_str(), sizeof(m_order_ptr->update_datetime_) - 1);

                // 即使状态相同也要返回,如部分成交时,手数发生了变化
                m_order_ptr->order_state_ = order_state;
                m_is_modify = true;
            }
        }

        AllTrade::OrderStateExplainType OrderBaseHandler::getOrderStateExplain() const
        {
            readLock lock(m_mtx);
            return m_order_ptr->orser_state_explain_;
        }

        const POrderStreamType OrderBaseHandler::getOrderStream() const
        {
            return m_order_ptr->order_stream_;
        }

        const PShadowOrderIDType OrderBaseHandler::getShadowOrderID() const
        {
            return m_order_ptr->shadow_order_id_;
        }

        void OrderBaseHandler::setShadowOrderID(const ShadowOrderIDType shadoworder_id)
        {
            strncpy_s(m_order_ptr->shadow_order_id_, shadoworder_id, sizeof(m_order_ptr->shadow_order_id_) - 1);
        }

        const PDateTimeType OrderBaseHandler::getGenerateDatetime() const
        {
            readLock lock(m_mtx);
            return m_order_ptr->generate_datetime_;
        }

        const PDateTimeType OrderBaseHandler::getUpdateDatetime() const
        {
            readLock lock(m_mtx);
            return m_order_ptr->update_datetime_;
        }

        YDouble OrderBaseHandler::getCurrencyRate() const
        {
            return m_order_ptr->currency_rate_;
        }

        const PCurrencyIDType OrderBaseHandler::getCurrencyID() const
        {
            return m_order_ptr->currency_id_;
        }

        YDouble OrderBaseHandler::getOrderPrice(const CurrencyIDType currency_id) const
        {
            return m_order_ptr->order_price_;
        }

        YDouble OrderBaseHandler::getOrderPrice() const
        {
            return m_order_ptr->order_price_;
        }

        void OrderBaseHandler::setOrderPrice(YDouble order_price)
        {
            writeLock lock(m_mtx);
            m_order_ptr->order_price_ = order_price;
            m_is_modify = true;
        }

        DirectType OrderBaseHandler::getDirect() const
        {
            return m_order_ptr->direct_type_;
        }

        int OrderBaseHandler::getOrderVol() const
        {
            return m_order_ptr->order_vol_;
        }

        int OrderBaseHandler::getTradeVol() const
        {
            readLock lock(m_mtx);
            return m_order_ptr->trade_vol_;
        }

        bool OrderBaseHandler::addTradeVol(int vol)
        {
            writeLock lock(m_mtx);
            if (m_order_ptr->order_vol_ <= 0
                || m_order_ptr->order_vol_ <= m_order_ptr->trade_vol_
                || m_order_ptr->order_vol_ - m_order_ptr->trade_vol_ < vol)
            {
                m_order_ptr->orser_state_explain_ = OSET_Err_EffectVol;
                assert(0);
                return false;
            }

            LOG4CXX_DEBUG(logger, "新增委托成交手数"LOG_NOVAR(vol)
                ",委托流号"LOG_NOVAR(m_order_ptr->order_stream_)
                ",委托方向"LOG_NOVAR((int)m_order_ptr->direct_type_)
                ",原委托手数"LOG_NOVAR(m_order_ptr->order_vol_)
                ",原委托生效手数"LOG_NOVAR(m_order_ptr->effected_vol_)
                ",原成交手数"LOG_NOVAR(m_order_ptr->trade_vol_));

            m_order_ptr->trade_vol_ += vol;
            return true;
        }

        void OrderBaseHandler::setTradeVol(int vol)
        {
            writeLock lock(m_mtx);
            m_order_ptr->trade_vol_ = vol;
        }

        int OrderBaseHandler::getEffectVol() const
        {
            readLock lock(m_mtx);
            return m_order_ptr->effected_vol_;
        }

        AllTrade::OrderTypeType OrderBaseHandler::getOrderType() const
        {
            return m_order_ptr->order_type_;
        }

        void OrderBaseHandler::setOrderType(OrderTypeType type)
        {
            writeLock lock(m_mtx);
            m_order_ptr->order_type_ = type;
            m_is_modify = true;
        }

        AllTrade::OrderTradeModeType OrderBaseHandler::getOrderTradeMode() const
        {
            return m_order_ptr->order_trade_mode_;
        }

        YDouble OrderBaseHandler::getOrderTradePrice(const CurrencyIDType currency_id) const
        {
            readLock lock(m_mtx);
            return m_order_ptr->order_trade_price_;
        }

        YDouble OrderBaseHandler::getOrderTradePrice() const
        {
            readLock lock(m_mtx);
            return m_order_ptr->order_trade_price_;
        }

        YDouble OrderBaseHandler::getPoitionCost() const
        {
            readLock lock(m_mtx);
            return m_order_ptr->position_cost_;
        }

        YDouble OrderBaseHandler::getFreezeMoney() const
        {
            readLock lock(m_mtx);
            return m_order_ptr->freeze_money_;
        }

        const PSystemIDType OrderBaseHandler::getSystemID() const
        {
            readLock lock(m_mtx);
            return m_order_ptr->system_order_id_;
        }

        const PExchangeIDType OrderBaseHandler::getExchangeID() const
        {
            return m_order_ptr->exchange_id_;
        }

        AllTrade::ApiTypeType OrderBaseHandler::getApiType() const
        {
            return m_order_ptr->api_type_;
        }

        AllTrade::CommodityTypeType OrderBaseHandler::getCommodityType() const
        {
            return m_order_ptr->commodity_type_;
        }

        AllTrade::OperatorTradeType OrderBaseHandler::getOperatorType() const
        {
            return m_order_ptr->op_type_;
        }

        AllTrade::OrderModeType OrderBaseHandler::getOrderMode() const
        {
            return m_order_ptr->order_mode_;
        }

        const PDateTimeType OrderBaseHandler::getValidDatetime() const
        {
            return m_order_ptr->valid_datetime_;
        }

        bool OrderBaseHandler::matchQuote(const QuoteInfoPtr& quote_ptr) const
        {
            if (m_order_ptr->order_type_ == OrderTypeType::ORDER_TYPE_MARKET)
                return true;
            if (m_order_ptr->direct_type_ == DirectType::DIRECT_BUY)
                return quote_ptr->ask_price_[0] > 0.0 && getOrderPrice() >= quote_ptr->ask_price_[0];
            else
                return quote_ptr->bid_price_[0] > 0.0 && getOrderPrice() <= quote_ptr->bid_price_[0];
        }

        bool OrderBaseHandler::simulateTrade(const QuoteHrPtr& quote_hr_ptr)
        {
            // 设置操作状态锁,锁定撮合状态/操作状态
            // 注:必须在最前
            if (!m_status_mtx.try_lock())
                return false;

//             m_status_mtx.lock();
            CommonTools::ScopeGuard ext([&]{
                m_status_mtx.unlock();
            });

            bool needDeal(true);
            int change_vol(0);
            QuoteInfoPtr quote_ptr = quote_hr_ptr->getQuoteInfoCopy();
            {
                readLock lock(m_mtx);
                if (m_order_ptr->order_state_ != OrderStateType::ORDER_STATE_QUEUED && m_order_ptr->order_state_ != OrderStateType::ORDER_STATE_PARTFINISHED)
                {
                    return false;
                }

                if (!isTradeTime())
                    return false;

                ErrorCodeType errCode = canTrade();
                if (errCode != Err_Succeed)
                {
                    LOG4CXX_WARN(logger, "模拟成交时,当前状态不可成交!"LOG_NOVAR(errCode));
                    return false;
                }

                // 对委托做比对,比对失败或处于不可交易状态中无需向前置机发送信息
                if (!matchQuote(quote_ptr))
                {
                    if (quote_ptr->ask_price_[0] == 0.0 || quote_ptr->bid_price_[0] == 0.0)
                    {
                        LOG4CXX_DEBUG(logger, "行情不匹配"LOG_NOVAR(quote_ptr->contract_id_)LOG_NOVAR(quote_ptr->last_price_)LOG_NOVAR(quote_ptr->ask_price_[0])LOG_NOVAR(quote_ptr->bid_price_[0]));
                    }
                    return false;
                }

                // 初始化随机数,相当于漂移位
                srand((unsigned)time(NULL));
                // 获取[1,b]范围内随机数,b为未成交委托数
                int b = (m_order_ptr->order_vol_ - m_order_ptr->trade_vol_) / quote_hr_ptr->getMultiplier();
                if (b == 0)
                    change_vol = m_order_ptr->order_vol_ - m_order_ptr->trade_vol_;
                else
                {
                    change_vol = (rand() % b) + 1;
                    if (change_vol > 50)
                        change_vol = (rand() % 50) + 1;

                    change_vol *= quote_hr_ptr->getMultiplier();
                }
            }

            // 修改委托手数
            if (!addTradeVol(change_vol))
            {
                LOG4CXX_ERROR(logger, "模拟成交时,修改委托手数失败!");
                return true;
            }

            {
                readLock lock(m_mtx);
                needDeal = m_order_ptr->order_vol_ > m_order_ptr->trade_vol_;
            }

            OrderInfoPtr tmp_order_ptr = getOrderInfoCopy();
            if (needDeal)
                tmp_order_ptr->order_state_ = OrderStateType::ORDER_STATE_PARTFINISHED;
            else
                tmp_order_ptr->order_state_ = OrderStateType::ORDER_STATE_FINISHED;

            TaskMsgOrderManager::instance()->handleOrderChangeCbk(tmp_order_ptr, m_user_id);

            TradeInfoPtr trade_ptr = createTradeByQuote(quote_ptr, change_vol);
            TaskMsgOrderManager::instance()->handleTradeCbk(trade_ptr, m_user_id);
            
            return needDeal;
        }

        TradeInfoPtr OrderBaseHandler::createTradeByQuote(const QuoteInfoPtr& quote_info_ptr, int trade_vol, TradeInfoPtr trade_ptr) const
        {
            if (!trade_ptr)
            {
                assert(0);
                LOG4CXX_FATAL(logger, "无效委托类型,无法创建对应成交指针!");
            }
            YDouble cur_trade(0);
            if (getOrderType() == OrderTypeType::ORDER_TYPE_MARKET)
            {
                trade_ptr->trade_price_ = quote_info_ptr->last_price_;
            }
            else
            {
                if (m_order_ptr->direct_type_ == DirectType::DIRECT_BUY)
                    trade_ptr->trade_price_ = quote_info_ptr->ask_price_[0];
                else
                    trade_ptr->trade_price_ = quote_info_ptr->bid_price_[0];
            }

            strncpy_s(trade_ptr->trade_id_, UtilityFun::createGUID().c_str(), sizeof(trade_ptr->trade_id_) - 1);
            strncpy_s(trade_ptr->order_stream_, getOrderStream().c_str(), sizeof(trade_ptr->order_stream_) - 1);
            strncpy_s(trade_ptr->exchange_id_, getExchangeID().c_str(), sizeof(trade_ptr->exchange_id_) - 1);
            strncpy_s(trade_ptr->contract_id_, getContractID().c_str(), sizeof(trade_ptr->contract_id_) - 1);
            strncpy_s(trade_ptr->generate_datetime_, UtilityFun::getCurrentDateTime().c_str(), sizeof(trade_ptr->generate_datetime_) - 1);
            trade_ptr->volume_ = trade_vol;
            strncpy_s(trade_ptr->shadow_order_id_, m_order_ptr->shadow_order_id_, sizeof(trade_ptr->shadow_order_id_));
            strncpy_s(trade_ptr->shadow_trade_id_, GlobalDataManager::instance()->getCurShadowTradeID_c().c_str(), sizeof(trade_ptr->shadow_trade_id_));
            strncpy_s(trade_ptr->currency_id_, getCurrencyID().c_str(), sizeof(trade_ptr->currency_id_) - 1);
            trade_ptr->commodity_type_ = getCommodityType();
            trade_ptr->api_type_ = getApiType();
            trade_ptr->direct_type_ = getDirect();
            trade_ptr->op_type_ = getOperatorType();

            return trade_ptr;
        }

        void OrderBaseHandler::realTrade(const TradeInfoPtr& trade_ptr)
        {
            strncpy_s(trade_ptr->generate_datetime_, UtilityFun::getCurrentDateTime().c_str(), sizeof(trade_ptr->generate_datetime_) - 1);
            strncpy_s(trade_ptr->trade_id_, UtilityFun::createGUID().c_str(), sizeof(trade_ptr->trade_id_) - 1);
            strncpy_s(trade_ptr->order_stream_, getOrderStream().c_str(), sizeof(trade_ptr->order_stream_) - 1);
            strncpy_s(trade_ptr->exchange_id_, getExchangeID().c_str(), sizeof(trade_ptr->exchange_id_) - 1);
            strncpy_s(trade_ptr->contract_id_, getContractID().c_str(), sizeof(trade_ptr->contract_id_) - 1);
            strncpy_s(trade_ptr->shadow_order_id_, m_order_ptr->shadow_order_id_, sizeof(trade_ptr->shadow_order_id_));
            strncpy_s(trade_ptr->shadow_trade_id_, GlobalDataManager::instance()->getCurShadowTradeID_c().c_str(), sizeof(trade_ptr->shadow_trade_id_));
            strncpy_s(trade_ptr->currency_id_, getCurrencyID().c_str(), sizeof(trade_ptr->currency_id_) - 1);
            trade_ptr->op_type_ = getOperatorType();
            trade_ptr->api_type_ = getApiType();
            trade_ptr->commodity_type_ = getCommodityType();
            trade_ptr->api_type_ = getApiType();
            trade_ptr->direct_type_ = getDirect();
            trade_ptr->op_type_ = getOperatorType();
     
            TaskMsgOrderManager::instance()->handleTradeCbk(trade_ptr, m_user_id);
        }

        void OrderBaseHandler::simulateCancelOrder()
        {
            ErrorCodeType err_code = Err_Unknown;

            m_status_mtx.lock();
            CommonTools::ScopeGuard ext([&]{
                m_status_mtx.unlock();
            });

            err_code = canCancelOrder();
            if (err_code != Err_Succeed)
                return;

            OrderInfoPtr tmp_order_ptr = getOrderInfoCopy();
            tmp_order_ptr->order_state_ = OrderStateType::ORDER_STATE_DELETED;

            TaskMsgOrderManager::instance()->handleCancelOrderCbk(tmp_order_ptr, m_user_id);
        }

        void OrderBaseHandler::checkOrderTradeStatus()
        {
            bool needthaw(false);
            if (((m_order_ptr->order_state_ == OrderStateType::ORDER_STATE_FAIL
                || m_order_ptr->order_state_ == OrderStateType::ORDER_STATE_DELETED)
                && m_order_ptr->trade_vol_ == m_order_ptr->effected_vol_)
                || (m_order_ptr->order_state_ == OrderStateType::ORDER_STATE_FINISHED && m_order_ptr->order_vol_ == m_order_ptr->effected_vol_))
                needthaw = true;

            if (needthaw)
            {
                thawMoney();
                thawPosition();
                OrderListManager::instance()->removefromList(shared_from_this());
            }
        }

        AllTrade::ErrorCodeType OrderBaseHandler::serialize()
        {
            writeLock lock(m_mtx);

            // 无修改则无需重复序列化
            if (!m_is_modify)
                return Err_Succeed;
            strncpy_s(m_order_ptr->update_datetime_, UtilityFun::getCurrentDateTime().c_str(), sizeof(m_order_ptr->update_datetime_));

			 
			if (!OperationManager::COperationManager::instance()->updateOrderInfo(m_order_ptr, m_user_id))
				return Err_Database;
           

            m_is_modify = false;
            return Err_Succeed;
        }

        YDouble OrderBaseHandler::getUserOpenFee(DirectType direct, YDouble all_money, int vol) const
        {
            YDouble rslt(0);
            SRiskInfoPtr risk_ptr = IManagerCenter::instance()->getRiskInfoByUserID(m_user_id);

            // 是否为上交所
            bool isXSHG(QuoteListManager::instance()->getQuoteHrByID(m_order_ptr->contract_id_)->getExchangeCode() == "XSHG");

            // 本次持仓成本 = 本次成交金额 + 总手续费 - 上次总手续费
            switch (direct)
            {
            case DirectType::DIRECT_BUY:
                if (risk_ptr->commissionrate_ == 0.0)
                    rslt = TradeFeeManager::instance()->getOpenFee(all_money, vol, isXSHG);
                else
                    rslt = TradeFeeManager::instance()->getSpecifyOpenFee(risk_ptr->commissionrate_, all_money, vol, isXSHG);
                break;
            case DirectType::DIRECT_SELL:
                if (risk_ptr->commissionrate_ == 0.0)
                    rslt = TradeFeeManager::instance()->getCloseFee(all_money, vol, isXSHG);
                else
                    rslt = TradeFeeManager::instance()->getSpecifyCloseFee(risk_ptr->commissionrate_, all_money, vol, isXSHG);
                break;
            default:
                break;
            }
            return rslt;
        }

        YDouble OrderBaseHandler::getUserTradeCommissionFee(YDouble all_money) const
        {
            YDouble rslt(0);
            SRiskInfoPtr risk_ptr = IManagerCenter::instance()->getRiskInfoByUserID(m_user_id);

            if (risk_ptr->commissionrate_ == 0.0)
                rslt = TradeFeeManager::instance()->getTradeCommissionFee(all_money);
            else
                rslt = TradeFeeManager::instance()->getSpecifyTradeCommissionFee(risk_ptr->commissionrate_, all_money);

            return rslt;
        }

        //////////////////////////////////////////////////////////////////////////
        StockOrderHandler::StockOrderHandler(const StockOrderPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online)
            : OrderBaseHandler(order_ptr, use_id, user_online)
        {

        }

        AllTrade::StockAreaType StockOrderHandler::getStockAreaType() const
        {
            StockOrderPtr tmp = std::dynamic_pointer_cast<StockOrderInfo>(m_order_ptr);
            return tmp->stock_area_;
        }

        ErrorCodeType StockOrderHandler::isOrderValid() const
        {
            ErrorCodeType err_code = OrderBaseHandler::isOrderValid();
            if (err_code != Err_Succeed)
                return err_code;

            if (m_order_ptr->direct_type_ == DirectType::DIRECT_BUY)
                return Err_Succeed;

            PositionHrPtr reverse_position = PositionListManager::instance()->getReversePosition(m_user_id, m_order_ptr->contract_id_, m_order_ptr->direct_type_);
            if (!reverse_position)
            {
                LOG4CXX_INFO(logger, "卖出委托无买方向持仓");
                return Err_Succeed;
            }

            if (m_order_ptr->order_vol_ > reverse_position->getCanCloseVol())
            {
                LOG4CXX_INFO(logger, "卖出委托手数大于其可平仓手数");
                return Err_Trade_InvalidVolume;
            }

            return Err_Succeed;
        }

        AllTrade::ErrorCodeType StockOrderHandler::freezeMoney()
        {
            // 卖方向无需冻结资金
            if (m_order_ptr->direct_type_ == DirectType::DIRECT_SELL)
                return Err_Succeed;

            YDouble highest_price(0);
            QuoteHrPtr quote_ptr = QuoteListManager::instance()->getQuoteHrByID(getContractID().c_str());
            if (quote_ptr)
                highest_price = getOrderFreezeFee(quote_ptr);
            
            ErrorCodeType err_code(Err_Unknown);
            err_code = IManagerCenter::instance()->moneyChange(getUserID().c_str(), MC_Order_Freeze, highest_price, "系统委托冻结");
            if (err_code != Err_Succeed)
            {
                LOG4CXX_WARN(logger, "提交委托"LOG_NOVAR(getOrderStream())"时,资金变更失败" LOG_NOVAR(err_code));
                return err_code;
            }

            writeLock lock(m_mtx);
            m_order_ptr->freeze_money_ = highest_price;
            m_order_ptr->b_freeze_money_ = true;
            m_is_modify = true;
            return err_code;
        }

        AllTrade::ErrorCodeType StockOrderHandler::freezePosition()
        {
            // 买方向无需冻结持仓
            if (m_order_ptr->direct_type_ == DirectType::DIRECT_BUY)
                return Err_Succeed;

            PositionHrPtr reverse_position = PositionListManager::instance()->getReversePosition(m_user_id, m_order_ptr->contract_id_, m_order_ptr->direct_type_);
            if (!reverse_position)
            {
                LOG4CXX_WARN(logger, "提交委托"LOG_NOVAR(getOrderStream())"时,未找到买方向持仓!");
                return Err_MaxCanCloseVol;
            }

            if (!reverse_position->addFreezeVol(m_order_ptr->order_vol_))
            {
                LOG4CXX_WARN(logger, "提交委托"LOG_NOVAR(getOrderStream())"时,冻结持仓手数失败!"LOG_NOVAR(m_order_ptr->order_vol_)LOG_NOVAR(reverse_position->getCanCloseVol()));
                return Err_MaxCanCloseVol;
            }

            writeLock lock(m_mtx);
            m_order_ptr->b_freeze_position_ = true;
            m_is_modify = true;
            return Err_Succeed;
        }

        AllTrade::ErrorCodeType StockOrderHandler::thawMoney()
        {
            writeLock lock(m_mtx);
            if (m_order_ptr->b_freeze_money_)
            {
                ErrorCodeType err_code(Err_Unknown);
                err_code = IManagerCenter::instance()->moneyChange(getUserID().c_str(), MC_Trade_Thaw, m_order_ptr->freeze_money_ - m_order_ptr->position_cost_, "系统冻结资金返还");
                if (err_code != Err_Succeed)
                {
                    LOG4CXX_WARN(logger, "解冻委托"LOG_NOVAR(getOrderStream())"资金时,资金变更失败" LOG_NOVAR(err_code));
                    return err_code;
                }
                m_order_ptr->b_freeze_money_ = false;
                m_is_modify = true;
            }
            return Err_Succeed;
        }

        AllTrade::ErrorCodeType StockOrderHandler::thawPosition()
        {
            writeLock lock(m_mtx);
            if (m_order_ptr->b_freeze_position_)
            {
                PositionHrPtr reverse_position = PositionListManager::instance()->getReversePosition(m_user_id, m_order_ptr->contract_id_, m_order_ptr->direct_type_);
                if (!reverse_position)
                {
                    LOG4CXX_WARN(logger, "解冻委托"LOG_NOVAR(getOrderStream())"持仓时,未找到买方向持仓!");
                    return Err_MaxCanCloseVol;
                }

                if (!reverse_position->addFreezeVol(m_order_ptr->effected_vol_ - m_order_ptr->order_vol_))
                {
                    LOG4CXX_WARN(logger, "解冻委托"LOG_NOVAR(getOrderStream())"持仓时失败!"
                        LOG_NOVAR(m_order_ptr->order_vol_)LOG_NOVAR(m_order_ptr->effected_vol_)
                        LOG_NOVAR(reverse_position->getPositionAllVol())LOG_NOVAR(reverse_position->getCanCloseVol()));
                    return Err_MaxCanCloseVol;
                }
                m_order_ptr->b_freeze_position_ = false;
                m_is_modify = true;
            }
            return Err_Succeed;
        }

        AllTrade::NPTradeCenter::StockOrderInfo StockOrderHandler::getOrderInfo() const
        {
            readLock lock(m_mtx);
            StockOrderPtr tmp = std::dynamic_pointer_cast<StockOrderInfo>(m_order_ptr);
            assert(tmp);
            return *(tmp.get());
        }

        void StockOrderHandler::realTrade(const TradeInfoPtr& trade_ptr)
        {
            StockTradePtr trade_ptr_tmp = std::dynamic_pointer_cast<StockTradeInfo>(trade_ptr);
            StockOrderPtr order_ptr_tmp = std::dynamic_pointer_cast<StockOrderInfo>(m_order_ptr);
            trade_ptr_tmp->stock_area_ = order_ptr_tmp->stock_area_;

            OrderBaseHandler::realTrade(trade_ptr);
        }

        void StockOrderHandler::generateTradeFeeVarious(const TradeInfoPtr& trade_ptr)
        {
            StockTradePtr trade_ptr_tmp = std::dynamic_pointer_cast<StockTradeInfo>(trade_ptr);

            assert(trade_ptr_tmp);
            if (!trade_ptr_tmp)
                return;

            {
                writeLock lock(m_mtx);
                // 上次总成交金额
                YDouble last_all_money = m_order_ptr->order_trade_price_ * m_order_ptr->effected_vol_;
                // 上次总手续费 = 上次总持仓成本 - 上次总成交金额
                YDouble last_fee = m_order_ptr->position_cost_ - last_all_money;

                // 本次成交金额
                YDouble cur_trade = UtilityFun::Round(trade_ptr->trade_price_ * trade_ptr->volume_, 0.00001);

                // 累计成交金额 = 本次成交金额 + 上次总成交金额
                YDouble all_money = cur_trade + last_all_money;

                // 总佣金-上次佣金
                if (m_order_ptr->effected_vol_ == 0)
                    trade_ptr_tmp->trade_fee_ = getUserTradeCommissionFee(all_money);
                else
                    trade_ptr_tmp->trade_fee_ = getUserTradeCommissionFee(all_money) - getUserTradeCommissionFee(last_all_money);

                if (getDirect() == DirectType::DIRECT_SELL)
                    trade_ptr_tmp->stamp_fee_ = TradeFeeManager::instance()->getStampDutyFee(cur_trade);

                // 是否为上交所
                bool isXSHG(QuoteListManager::instance()->getQuoteHrByID(m_order_ptr->contract_id_)->getExchangeCode() == "XSHG");
                if (isXSHG)
                    trade_ptr_tmp->transfer_fee_ = TradeFeeManager::instance()->getTransferFee(m_order_ptr->effected_vol_ + trade_ptr->volume_) - TradeFeeManager::instance()->getTransferFee(m_order_ptr->effected_vol_);

                trade_ptr_tmp->infomatch_fee_ = TradeFeeManager::instance()->getInfoMatchFee(cur_trade);

                if (m_order_ptr->effected_vol_ == 0)
                    m_order_ptr->order_trade_price_ = trade_ptr->trade_price_;
                else
                    m_order_ptr->order_trade_price_ = UtilityFun::Round((trade_ptr_tmp->trade_price_ * trade_ptr->volume_ + m_order_ptr->order_trade_price_ * (m_order_ptr->effected_vol_)) / (m_order_ptr->effected_vol_ + trade_ptr->volume_), 0.00001);

                StockOrderPtr tmp = std::dynamic_pointer_cast<StockOrderInfo>(m_order_ptr);
                tmp->effected_vol_ += trade_ptr->volume_;
                tmp->cur_trade_fee_ += trade_ptr_tmp->trade_fee_;
                tmp->cur_stamp_fee_ += trade_ptr_tmp->stamp_fee_;
                tmp->cur_transfer_fee_ += trade_ptr_tmp->transfer_fee_;
                tmp->cur_infomatch_fee_ += trade_ptr_tmp->infomatch_fee_;
                tmp->position_cost_ += UtilityFun::Round(trade_ptr->trade_price_ * trade_ptr->volume_ 
                                                        + trade_ptr_tmp->trade_fee_ + trade_ptr_tmp->stamp_fee_
                                                        + trade_ptr_tmp->transfer_fee_ + trade_ptr_tmp->infomatch_fee_, 0.00001);
                m_is_modify = true;
            }
            checkOrderTradeStatus();
            serialize();
        }

        AllTrade::NPTradeCenter::OrderInfoPtr StockOrderHandler::getOrderInfoCopy() const
        {
            readLock lock(m_mtx);
            return std::make_shared<StockOrderInfo>(*std::dynamic_pointer_cast<StockOrderInfo>(m_order_ptr).get());
        }

        AllTrade::NPTradeCenter::TradeInfoPtr StockOrderHandler::createTradeByQuote(const QuoteInfoPtr& quote_info_ptr, int trade_vol, TradeInfoPtr trade_ptr_self)const
        {
            StockTradePtr trade_ptr_tmp = std::make_shared<StockTradeInfo>();
            StockOrderPtr order_ptr_tmp = std::dynamic_pointer_cast<StockOrderInfo>(m_order_ptr);
            trade_ptr_tmp->stock_area_ = order_ptr_tmp->stock_area_;

            if (m_order_ptr->order_type_ == OrderTypeType::ORDER_TYPE_MARKET)
            {
                trade_ptr_tmp->trade_price_ = quote_info_ptr->last_price_;
            }
            else
            {
                if (m_order_ptr->direct_type_ == DirectType::DIRECT_BUY)
                    trade_ptr_tmp->trade_price_ = quote_info_ptr->ask_price_[0];
                else
                    trade_ptr_tmp->trade_price_ = quote_info_ptr->bid_price_[0];
            }
            return OrderBaseHandler::createTradeByQuote(quote_info_ptr, trade_vol, trade_ptr_tmp);
        }

        //////////////////////////////////////////////////////////////////////////
        ForeignFutureOrderHandler::ForeignFutureOrderHandler(const ForeignFutureOrderPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online)
            : OrderBaseHandler(order_ptr, use_id, user_online)
        {

        }
        ErrorCodeType ForeignFutureOrderHandler::isOrderValid() const
        {
            ForeignFutureOrderPtr ffuture_order_ptr = std::dynamic_pointer_cast<ForeignFutureOrderInfo>(m_order_ptr);
            assert(ffuture_order_ptr);

            return OrderBaseHandler::isOrderValid()
                && strnlen_s(ffuture_order_ptr->product_id_, sizeof(ffuture_order_ptr->product_id_)) != 0;
        }

        const PProductIDType ForeignFutureOrderHandler::getProductID() const
        {
            ForeignFutureOrderPtr ffuture_order_ptr = std::dynamic_pointer_cast<ForeignFutureOrderInfo>(m_order_ptr);
            assert(ffuture_order_ptr);
            return ffuture_order_ptr->product_id_;
        }

        AllTrade::NPTradeCenter::ForeignFutureOrderInfo ForeignFutureOrderHandler::getOrderInfo() const
        {
            readLock lock(m_mtx);
            ForeignFutureOrderPtr tmp = std::dynamic_pointer_cast<ForeignFutureOrderInfo>(m_order_ptr);
            assert(tmp);
            return *(tmp.get());
        }

        AllTrade::NPTradeCenter::OrderInfoPtr ForeignFutureOrderHandler::getOrderInfoCopy() const
        {
            readLock lock(m_mtx);
            return std::make_shared<ForeignFutureOrderInfo>(*std::dynamic_pointer_cast<ForeignFutureOrderInfo>(m_order_ptr).get());
        }

        AllTrade::NPTradeCenter::TradeInfoPtr ForeignFutureOrderHandler::createTradeByQuote(const QuoteInfoPtr& quote_info_ptr, int trade_vol, TradeInfoPtr trade_ptr_self /*= nullptr*/) const
        {
            ForeignFutureTradePtr ftrade_ptr = std::make_shared<ForeignFutureTradeInfo>();
            strncpy_s(ftrade_ptr->product_id_, getProductID().c_str(), sizeof(ftrade_ptr->product_id_) - 1);

            return OrderBaseHandler::createTradeByQuote(quote_info_ptr, trade_vol, ftrade_ptr);
        }

        //////////////////////////////////////////////////////////////////////////
        ChinaFutureOrderHandler::ChinaFutureOrderHandler(const ChinaFutureOrderPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online)
            : OrderBaseHandler(order_ptr, use_id, user_online)
        {

        }
        ErrorCodeType ChinaFutureOrderHandler::isOrderValid() const
        {
            ChinaFutureOrderPtr cfuture_order_ptr = std::dynamic_pointer_cast<ChinaFutureOrderInfo>(m_order_ptr);
            assert(cfuture_order_ptr);

            return OrderBaseHandler::isOrderValid()
                && strnlen_s(cfuture_order_ptr->product_id_, sizeof(cfuture_order_ptr->product_id_)) != 0
                && cfuture_order_ptr->offset_type_ != OffsetType::OFFSET_Invalid;

        }

        const PProductIDType ChinaFutureOrderHandler::getProductID() const
        {
            ChinaFutureOrderPtr cfuture_order_ptr = std::dynamic_pointer_cast<ChinaFutureOrderInfo>(m_order_ptr);
            assert(cfuture_order_ptr);
            return cfuture_order_ptr->product_id_;
        }

        OffsetType ChinaFutureOrderHandler::getOffsetType() const
        {
            ChinaFutureOrderPtr cfuture_order_ptr = std::dynamic_pointer_cast<ChinaFutureOrderInfo>(m_order_ptr);
            assert(cfuture_order_ptr);
            return cfuture_order_ptr->offset_type_;
        }

        AllTrade::NPTradeCenter::ChinaFutureOrderInfo ChinaFutureOrderHandler::getOrderInfo() const
        {
            readLock lock(m_mtx);
            ChinaFutureOrderPtr tmp = std::dynamic_pointer_cast<ChinaFutureOrderInfo>(m_order_ptr);
            assert(tmp);
            return *(tmp.get());
        }

        AllTrade::NPTradeCenter::OrderInfoPtr ChinaFutureOrderHandler::getOrderInfoCopy() const
        {
            readLock lock(m_mtx);
            return std::make_shared<ForeignFutureOrderInfo>(*std::dynamic_pointer_cast<ForeignFutureOrderInfo>(m_order_ptr).get());
        }

        AllTrade::NPTradeCenter::TradeInfoPtr ChinaFutureOrderHandler::createTradeByQuote(const QuoteInfoPtr& quote_info_ptr, int trade_vol, TradeInfoPtr trade_ptr_self /*= nullptr*/) const
        {
            ChinaFutureTradePtr ctrade_ptr = std::make_shared<ChinaFutureTradeInfo>();
            strncpy_s(ctrade_ptr->product_id_, getProductID().c_str(), sizeof(ctrade_ptr->product_id_) - 1);
            ctrade_ptr->offset_type_ = getOffsetType();

            return OrderBaseHandler::createTradeByQuote(quote_info_ptr, trade_vol, ctrade_ptr);
        }

		//////////////////////////////////////////////////////////////////////////
		MarginOrderHandler::MarginOrderHandler(const MarginOrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online)
			: OrderBaseHandler(order_ptr, use_id, user_online)
		{

		}

		AllTrade::ErrorCodeType MarginOrderHandler::isOrderValid() const
		{
			return Err_Succeed;
		}

		AllTrade::NPTradeCenter::OrderInfoPtr MarginOrderHandler::getOrderInfoCopy() const
		{
			readLock lock(m_mtx);
			return std::make_shared<MarginOrderInfo>(*std::dynamic_pointer_cast<MarginOrderInfo>(m_order_ptr).get());

		}

		AllTrade::NPTradeCenter::MarginOrderInfo MarginOrderHandler::getOrderInfo() const
		{
			readLock lock(m_mtx);
			MarginOrderInfoPtr tmp = std::dynamic_pointer_cast<MarginOrderInfo>(m_order_ptr);
			assert(tmp);
			return *(tmp.get());
		}

		AllTrade::NPTradeCenter::TradeInfoPtr MarginOrderHandler::createTradeByQuote(const QuoteInfoPtr& quote_info_ptr, int trade_vol, TradeInfoPtr trade_ptr_self /*= nullptr*/) const
		{
			return nullptr;
		}

	}
}