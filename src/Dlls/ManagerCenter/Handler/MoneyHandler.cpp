#include "MoneyHandler.h"
#include "define/protocol_error.h"
#include "include/OperationManager/OperationManager.h"
#include "accounthandler.h"
#include "utility/utility_fun.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "MoneyHandler");

namespace AllTrade {
    namespace NPMgrCenter {

        CMoneyHandler::CMoneyHandler()
        {
            m_money_st_obj = std::make_shared<SMoneyInfo>();
        }

        CMoneyHandler::CMoneyHandler(const SMoneyInfoPtr& money_st)
            : m_money_st_obj(money_st)
        {

        }

        CMoneyHandler::CMoneyHandler(const AccountHrPtr& parent)
            : m_parent(parent)
        {
            m_money_st_obj = std::make_shared<SMoneyInfo>();
        }

        CMoneyHandler::~CMoneyHandler()
        {

        }

        YDouble CMoneyHandler::getPositionCost() const
        {
            readLock lock(m_mtx_sp);
            return m_money_st_obj->position_cost_price_;
        }

        YDouble CMoneyHandler::getTradingFee() const
        {
            readLock lock(m_mtx_sp);
            return m_money_st_obj->getAllTradeFee();
        }

        YDouble CMoneyHandler::getCanExtract() const
        {
            readLock lock(m_mtx_sp);
            YDouble rslt = m_money_st_obj->getCanExtract();
            if (rslt < 0.0)
                return 0;

            return rslt;
        }

        YDouble CMoneyHandler::getOrderFreeze() const
        {
            readLock lock(m_mtx_sp);
            return m_money_st_obj->order_freeze_;
        }

        YDouble CMoneyHandler::getDeposit() const
        {
            readLock lock(m_mtx_sp);
            return m_money_st_obj->user_deposit_;
        }

        YDouble CMoneyHandler::getPriorityFund() const
        {
            readLock lock(m_mtx_sp);
            return m_money_st_obj->priority_fund_;
        }

        YDouble CMoneyHandler::getTotal() const
        {
            readLock lock(m_mtx_sp);
            return m_money_st_obj->getCanUse() + m_money_st_obj->order_freeze_ /*+ 市值*/;
        }

        YDouble CMoneyHandler::getCanUse() const
        {
            readLock lock(m_mtx_sp);
            return m_money_st_obj->getCanUse();
        }

        AllTrade::ErrorCodeType CMoneyHandler::changePositionCost(YDouble cost_money, int vol, DirectType direct)
        {
            LOG4CXX_INFO(logger, "账户"LOG_NOVAR(getParentAccHandler()->getAccountID())
                "持仓成本待发生改变,新增持仓总价"LOG_NOVAR(cost_money)",新增持仓手数"LOG_NOVAR(vol)",方向"LOG_NOVAR((int)direct));

            writeLock lock(m_mtx_sp);
            if ((cost_money < 0.0 && direct == AllTrade::DirectType::DIRECT_BUY) || vol < 0 || (direct == AllTrade::DirectType::DIRECT_SELL && m_money_st_obj->position_all_vol_ < vol))
                return Err_Unknown;

            YDouble old_pos_cost_price(m_money_st_obj->position_cost_price_);
            int old_pos_all_vol(m_money_st_obj->position_all_vol_);

            switch (direct)
            {
            case AllTrade::DirectType::DIRECT_BUY:
                m_money_st_obj->position_cost_price_ += cost_money;
                m_money_st_obj->position_all_vol_ += vol;
                break;
            case AllTrade::DirectType::DIRECT_SELL:
                m_money_st_obj->position_cost_price_ += cost_money;
                m_money_st_obj->position_all_vol_ -= vol;
                break;
            default:
                return Err_Unknown;
                break;
            }
            ErrorCodeType errcode = serialize();
            if (errcode != Err_Succeed)
            {
                m_money_st_obj->position_cost_price_ = old_pos_cost_price;
                m_money_st_obj->position_all_vol_ = old_pos_all_vol;
            }
            LOG4CXX_INFO(logger, "账户"LOG_NOVAR(getParentAccHandler()->getAccountID())
                "持仓成本序列化结果"LOG_NOVAR(errcode)",原持仓总价"LOG_NOVAR(old_pos_cost_price)",原持仓手数"LOG_NOVAR(old_pos_all_vol)
                ",现持仓总价"LOG_NOVAR(m_money_st_obj->position_all_vol_)",现持仓手数"LOG_NOVAR(m_money_st_obj->position_all_vol_));
            return errcode;
        }

        AllTrade::ErrorCodeType CMoneyHandler::moneyChange(Money_Change_Type money_change, YDouble money, const RemarkTextType remark)
        {
            if (money == 0.0 && money_change != MC_Money_Settle) return Err_Succeed;

            LOG4CXX_INFO(logger, "账户"LOG_NOVAR(getParentAccHandler()->getAccountID())"资金信息发生改变,类型"LOG_NOVAR(money_change)",金额"LOG_NOVAR(money)",备注"LOG_NOVAR(remark));

            writeLock w1(m_mtx_sp);
            SMoneyDetailInfoPtr money_detail = std::make_shared<SMoneyDetailInfo>();
            strncpy_s(money_detail->stream_, UtilityFun::createGUID().c_str(), sizeof(money_detail->stream_) -1);
            money_detail->total_before_ = m_money_st_obj->getCanUse() + m_money_st_obj->order_freeze_;
            money_detail->money_before_ = *m_money_st_obj.get();
            money_detail->change_money_ = money;
            money_detail->change_type_ = money_change;
            strncpy_s(money_detail->remark_, remark, sizeof(money_detail->remark_) - 1);
            strncpy_s(money_detail->date_time_, UtilityFun::getCurrentDateTime().c_str(), sizeof(money_detail->date_time_) - 1);

            switch (money_change)
            {
            case AllTrade::MC_In_Deposit:
                m_money_st_obj->addDeposit(money);
                break;
            case AllTrade::MC_In_Equipment:
                m_money_st_obj->addEquipment(money);
                break;
            case AllTrade::MC_In_BlueAdd:
                m_money_st_obj->logic_can_extract_ += money;
                break;
            case AllTrade::MC_Out_Deposit:
                if (m_money_st_obj->getCanExtract() < money)
                    return Error_CashCheck_MoneyNotEnough;

                m_money_st_obj->addDeposit(-money);
                break;
            case AllTrade::MC_Out_Equipment:
                if (m_money_st_obj->getAllCanExtract() < money || m_money_st_obj->priority_fund_ < money)
                    return Error_CashCheck_MoneyNotEnough;

                m_money_st_obj->addEquipment(-money);
                break;
            case AllTrade::MC_Out_RedSub:
                if (m_money_st_obj->getCanExtract() < money)
                    return Error_CashCheck_MoneyNotEnough;

                m_money_st_obj->logic_can_extract_ -= money;
                break;
            case AllTrade::MC_Order_Freeze:
                if (m_money_st_obj->getCanUse() < money)
                    return Error_CashCheck_MoneyNotEnough;

                m_money_st_obj->orderFreeze(money);
                break;
            case AllTrade::MC_Order_Cancel:
                m_money_st_obj->cancelOrderThaw(money);
                break;
            case AllTrade::MC_Trade_Open:
                m_money_st_obj->order_freeze_ -= money;
                if (m_money_st_obj->logic_can_extract_ >= money)
                    m_money_st_obj->logic_can_extract_ -= money;
                else
                {
                    money -= m_money_st_obj->logic_can_extract_;
                    m_money_st_obj->logic_wait_thaw_ -= money;
                    m_money_st_obj->logic_can_extract_ = 0;
                }
                break;
            case AllTrade::MC_Trade_Open_Fee:
            case AllTrade::MC_Trade_Open_TransferFee:
                m_money_st_obj->trading_fee_ += money;
                m_money_st_obj->order_freeze_ -= money;

                if (m_money_st_obj->logic_can_extract_ >= money)
                    m_money_st_obj->logic_can_extract_ -= money;
                else
                {
                    money -= m_money_st_obj->logic_can_extract_;
                    m_money_st_obj->logic_wait_thaw_ -= money;
                    m_money_st_obj->logic_can_extract_ = 0;
                }

                break;
            case AllTrade::MC_Trade_Open_InfoMatchFee:
                m_money_st_obj->customize_fee_ += money;
                m_money_st_obj->order_freeze_ -= money;

                if (m_money_st_obj->logic_can_extract_ >= money)
                    m_money_st_obj->logic_can_extract_ -= money;
                else
                {
                    money -= m_money_st_obj->logic_can_extract_;
                    m_money_st_obj->logic_wait_thaw_ -= money;
                    m_money_st_obj->logic_can_extract_ = 0;
                }
                
                break;
            case AllTrade::MC_Trade_Thaw:
                m_money_st_obj->order_freeze_ -= money;

                break;
            case AllTrade::MC_Trade_Close:
                m_money_st_obj->logic_wait_thaw_ += money;
                break;
//             case AllTrade::MC_Trade_Close_Position:
//                 m_money_st_obj->position_fee_ -= money;
//                 break;
            case AllTrade::MC_Trade_Close_Fee:
            case AllTrade::MC_Trade_Close_TransferFee:
            case AllTrade::MC_Trade_Close_StampFee:
                m_money_st_obj->trading_fee_ += money;

                if (m_money_st_obj->logic_can_extract_ >= money)
                    m_money_st_obj->logic_can_extract_ -= money;
                else
                {
                    money -= m_money_st_obj->logic_can_extract_;
                    m_money_st_obj->logic_wait_thaw_ -= money;
                    m_money_st_obj->logic_can_extract_ = 0;
                }
                
                break;
            case AllTrade::MC_Trade_Close_InfoMatchFee:
                m_money_st_obj->customize_fee_ += money;

                if (m_money_st_obj->logic_can_extract_ >= money)
                    m_money_st_obj->logic_can_extract_ -= money;
                else
                {
                    money -= m_money_st_obj->logic_can_extract_;
                    m_money_st_obj->logic_wait_thaw_ -= money;
                    m_money_st_obj->logic_can_extract_ = 0;
                }
                
                break;
            case AllTrade::MC_Commission:
                m_money_st_obj->logic_can_extract_ += money;
                break;
            case AllTrade::MC_Money_Settle:
                money_detail->change_money_ = m_money_st_obj->logic_wait_thaw_;
                m_money_st_obj->moneySettle();
                break;
            case AllTrade::MC_Profit:
                if (m_money_st_obj->logic_can_extract_ >= money)
                    m_money_st_obj->logic_can_extract_ -= money;
                else
                {
                    money -= m_money_st_obj->logic_can_extract_;
                    m_money_st_obj->logic_wait_thaw_ -= money;
                    m_money_st_obj->logic_can_extract_ = 0;
                }
                break;
            default:
                break;
            }
            if (m_money_st_obj->order_freeze_ < 0.0 || m_money_st_obj->logic_wait_thaw_ < 0.0 || m_money_st_obj->logic_can_extract_ < 0.0)
            {
                assert(0);
                m_money_st_obj = std::make_shared<SMoneyInfo>(money_detail->money_before_);
                LOG4CXX_ERROR(logger, "账户"LOG_NOVAR(getParentAccHandler()->getAccountID())"资金信息有误!");
                return Err_Unknown;
            }


            money_detail->total_after_ = m_money_st_obj->getCanUse() + m_money_st_obj->order_freeze_;
            money_detail->money_after_ = *m_money_st_obj.get();

            ErrorCodeType err_code = serializeDetail(money_detail);
            if (err_code != Err_Succeed)
            {
                m_money_st_obj = std::make_shared<SMoneyInfo>(money_detail->money_before_);
                LOG4CXX_ERROR(logger, "账户"LOG_NOVAR(getParentAccHandler()->getAccountID())"资金流水信息序列化失败!");
                return err_code;
            }

            err_code = serialize();
            if (err_code != Err_Succeed)
            {
                m_money_st_obj = std::make_shared<SMoneyInfo>(money_detail->money_before_);
                LOG4CXX_ERROR(logger, "账户"LOG_NOVAR(getParentAccHandler()->getAccountID())"资金信息序列化失败!");
            }

            LOG4CXX_INFO(logger, "账户"LOG_NOVAR(getParentAccHandler()->getAccountID())
                "资金信息发生变化,当前交易总手续费"LOG_NOVAR(m_money_st_obj->getAllTradeFee())
                ",当前持仓总成本"LOG_NOVAR(m_money_st_obj->position_cost_price_)
                ",当前总可用金额"LOG_NOVAR(m_money_st_obj->getCanUse())
                ",当前总可提取金额"LOG_NOVAR(m_money_st_obj->getAllCanExtract())
                ",当前用户可提取金额"LOG_NOVAR(m_money_st_obj->getCanExtract())
                ",当前总委托冻结资金"LOG_NOVAR(m_money_st_obj->order_freeze_)
                ",当前用户保证金"LOG_NOVAR(m_money_st_obj->user_deposit_)
                ",当前优先资金"LOG_NOVAR(m_money_st_obj->priority_fund_));
            return err_code;
        }

        AllTrade::ErrorCodeType CMoneyHandler::serialize()
        {
            if (!OperationManager::COperationManager::instance()->updateUserMoneyInfo(getParentAccHandler()->getAccountID().c_str(), m_money_st_obj))
                return Err_Database;

            return Err_Succeed;
        }

        AllTrade::ErrorCodeType CMoneyHandler::unserialize()
        {
            if (!OperationManager::COperationManager::instance()->getUserMoneyInfo(getParentAccHandler()->getAccountID().c_str(), m_money_st_obj))
                return Err_Database;

            return Err_Succeed;
        }

        void CMoneyHandler::setParent(AccountHrPtr parent)
        {
            writeLock lock(m_mtx_sp);
            m_parent = parent;
        }

        AllTrade::ErrorCodeType CMoneyHandler::serializeDetail(const SMoneyDetailInfoPtr& money_change)
        {
            if (!OperationManager::COperationManager::instance()->updateUserMoneyDetailInfo(getParentAccHandler()->getAccountID().c_str(), money_change))
                return Err_Database;

            return Err_Succeed;
        }

    }
}