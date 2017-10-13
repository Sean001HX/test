#include <assert.h>
#include "utility/utility_fun.h"
#include "stockservermgr.h"
#include "../Handler/quotehandler.h"
#include "../Handler/quotelistmanager.h"
#include "../Handler/orderhandler.h"
#include "../Handler/orderlistmanager.h"
#include "../Handler/tradehandler.h"
#include "define/struct_extern.h"
#include "define/protocol_error.h"
#include "TradeFeeManager.h"
#include "include/ManagerCenter/ManagerCenter.h"
#include "../Handler/positionhandler.h"
#include "../Handler/positionlistmanager.h"
#include "RiskControlManager.h"
#include "include/OperationManager/OperationManager.h"
#include "taskmsg.h"
#include "taskmsg_order_mgr.h"
#include "../GlobalLock.h"
#include "utility/scopeguard.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"

NG_LOGGER(logger, "StockServerMgr");

using namespace AllTrade::NPMgrCenter;

namespace AllTrade{
    namespace NPTradeCenter {
        StockServerMgr::StockServerMgr()
            : ServerMgrBase(CommodityTypeType::COMMODITY_TYPE_STOCK)
        {

        }

        StockServerMgr::~StockServerMgr()
        {

        }

        void StockServerMgr::updateQuote(const QuoteInfoPtr& quote_ptr, const NPMgrCenter::SExchangeCPtr& exchange_ptr, const NPMgrCenter::SContractCPtr& contract_ptr)
        {
            QuoteListManager::instance()->updateQuote(quote_ptr, exchange_ptr, contract_ptr);
        }

        void StockServerMgr::dealTradeMsg(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id)
        {
            assert(trade_info_ptr);

			CGlobalLock::instance()->lock(use_id);

			CommonTools::ScopeGuard ext([&]{
				CGlobalLock::instance()->unlock(use_id);
			});
			

            OrderHrPtr order_hr_ptr = OrderListManager::instance()->getOrderHrPtrByUserID(use_id, trade_info_ptr->order_stream_);
            if (!order_hr_ptr)
            {
                LOG4CXX_ERROR(logger, "���յ��ɽ��ص�ʱ,�޷��ҵ�ί��!"LOG_NOVAR(use_id)LOG_NOVAR(trade_info_ptr->order_stream_));
                return;
            }

            LOG4CXX_DEBUG(logger, "���յ���Ʊ�ɽ���Ϣ"LOG_NOVAR(trade_info_ptr->trade_id_)
                ".ί������"LOG_NOVAR(trade_info_ptr->order_stream_)
                ",�ɽ�����"LOG_NOVAR(trade_info_ptr->volume_)
                ",�ɽ�����"LOG_NOVAR((int)trade_info_ptr->direct_type_)
                ",�ɽ�����"LOG_NOVAR(trade_info_ptr->trade_price_));

            order_hr_ptr->generateTradeFeeVarious(trade_info_ptr);

            StockTradeHrPtr stock_trade_hr_ptr = std::make_shared<StockTradeHandler>(std::dynamic_pointer_cast<StockTradeInfo>(trade_info_ptr), use_id);

            // �Ƿ�Ϊ�Ͻ���
            bool isXSHG(QuoteListManager::instance()->getQuoteHrByID(trade_info_ptr->contract_id_)->getExchangeCode() == "XSHG");

            ErrorCodeType err_code(Err_Unknown);
            YDouble position_cost(0);

#pragma region ��ʼ�����ʽ�䶯
            LOG4CXX_INFO(logger, "��ʼ�����ʽ�䶯"LOG_NOVAR(use_id));

            switch (stock_trade_hr_ptr->getDirect())
            {
            case AllTrade::DirectType::DIRECT_BUY:
                err_code = IManagerCenter::instance()->changePositionCost(stock_trade_hr_ptr->getUserID().c_str(), stock_trade_hr_ptr->getPositionCost(), stock_trade_hr_ptr->getTradeVol(), stock_trade_hr_ptr->getDirect());
                if (err_code != Err_Succeed)
                    break;

                err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Open, UtilityFun::Round(stock_trade_hr_ptr->getTradePrice()*stock_trade_hr_ptr->getTradeVol(), 0.00001), "���ֳɽ�");
                if (err_code != Err_Succeed)
                    break;
        
                err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Open_Fee, stock_trade_hr_ptr->getTradeCommissionFee(), "ϵͳ������ȡ����Ӷ��");
                if (err_code != Err_Succeed)
                    break;

                if (isXSHG)
                {
                    err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Open_TransferFee, stock_trade_hr_ptr->getTransferFee(), "ϵͳ������ȡ������");
                    if (err_code != Err_Succeed)
                        break;
                }

                err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Open_InfoMatchFee, stock_trade_hr_ptr->getInfoMatchFee(), "ϵͳ������ȡ��Ϣ��Ϸ�");

                break;
            case AllTrade::DirectType::DIRECT_SELL:
            {
                auto pos_item = PositionListManager::instance()->getReversePosition(stock_trade_hr_ptr->getUserID().c_str(), stock_trade_hr_ptr->getContractID().c_str(), stock_trade_hr_ptr->getDirect());
                assert(pos_item);

                err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Close, stock_trade_hr_ptr->getTradePrice()*stock_trade_hr_ptr->getTradeVol(), "ϵͳƽ���ʽ𷵻�");
                if (err_code != Err_Succeed)
                    break;

                err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Close_Fee, stock_trade_hr_ptr->getTradeCommissionFee(), "ϵͳƽ����ȡ����Ӷ��");
                if (err_code != Err_Succeed)
                    break;

                err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Close_StampFee, stock_trade_hr_ptr->getStampFee(), "ϵͳƽ����ȡӡ��˰");
                if (err_code != Err_Succeed)
                    break;

                if (isXSHG)
                {
                    err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Close_TransferFee, stock_trade_hr_ptr->getTransferFee(), "ϵͳƽ����ȡ������");
                    if (err_code != Err_Succeed)
                        break;
                }

                err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Close_InfoMatchFee, stock_trade_hr_ptr->getInfoMatchFee(), "ϵͳƽ����ȡ��Ϣ��Ϸ�");
                if (err_code != Err_Succeed)
                    break;

                dealProfitParentMoney(pos_item, stock_trade_hr_ptr);
            }
                break;
            default:
                assert(0);
                break;
            }

            dealCommissionParentMoney(stock_trade_hr_ptr, isXSHG);

            LOG4CXX_INFO(logger, "�����ʽ�䶯����"LOG_NOVAR(use_id));
#pragma endregion

            // �ֲָı�
            PositionHrPtr pos_hr_ptr = PositionListManager::instance()->changePosition(stock_trade_hr_ptr);

            TaskMsgOrderManager::instance()->handlePositionCbk(pos_hr_ptr->getUserID().c_str(), pos_hr_ptr->getPositionCopy(), trade_info_ptr);
        }

//         void StockServerMgr::dealTradeMsg(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id)
//         {
//             assert(trade_info_ptr);
// 
//             OrderHrPtr order_hr_ptr = OrderListManager::instance()->getOrderHrPtrByUserID(use_id, trade_info_ptr->order_stream_);
//             if (!order_hr_ptr)
//             {
//                 LOG4CXX_ERROR(logger, "���յ��ɽ��ص�ʱ,�޷��ҵ�ί��!"LOG_NOVAR(use_id)LOG_NOVAR(trade_info_ptr->order_stream_));
//                 return;
//             }
// 
//             LOG4CXX_DEBUG(logger, "���յ���Ʊ�ɽ���Ϣ"LOG_NOVAR(trade_info_ptr->trade_id_)
//                 ".ί������"LOG_NOVAR(trade_info_ptr->order_stream_)
//                 ",�ɽ�����"LOG_NOVAR(trade_info_ptr->volume_)
//                 ",�ɽ�����"LOG_NOVAR((int)trade_info_ptr->direct_type_)
//                 ",�ɽ�����"LOG_NOVAR(trade_info_ptr->trade_price_));
// 
//             order_hr_ptr->generateTradeFeeVarious(trade_info_ptr);
// 
//             StockTradeHrPtr stock_trade_hr_ptr = std::make_shared<StockTradeHandler>(std::dynamic_pointer_cast<StockTradeInfo>(trade_info_ptr), use_id);
// 
//             // �Ƿ�Ϊ�Ͻ���
//             bool isXSHG(QuoteListManager::instance()->getQuoteHrByID(trade_info_ptr->contract_id_)->getExchangeCode() == "XSHG");
// 
//             ErrorCodeType err_code(Err_Unknown);
//             YDouble position_cost(0);
// 
// #pragma region ��ʼ�����ʽ�䶯
//             LOG4CXX_INFO(logger, "��ʼ�����ʽ�䶯"LOG_NOVAR(use_id));
// 
//             switch (stock_trade_hr_ptr->getDirect())
//             {
//             case AllTrade::DirectType::DIRECT_BUY:
//                 err_code = IManagerCenter::instance()->changePositionCost(stock_trade_hr_ptr->getUserID().c_str(), stock_trade_hr_ptr->getPositionCost(), stock_trade_hr_ptr->getTradeVol(), stock_trade_hr_ptr->getDirect());
//                 if (err_code != Err_Succeed)
//                     break;
// 
//                 err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Open, UtilityFun::Round(stock_trade_hr_ptr->getTradePrice()*stock_trade_hr_ptr->getTradeVol(), 0.00001), "���ֳɽ�");
//                 if (err_code != Err_Succeed)
//                     break;
// 
//                 err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Open_Fee, stock_trade_hr_ptr->getTradeCommissionFee(), "ϵͳ������ȡ����Ӷ��");
//                 if (err_code != Err_Succeed)
//                     break;
// 
//                 if (isXSHG)
//                 {
//                     err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Open_TransferFee, stock_trade_hr_ptr->getTransferFee(), "ϵͳ������ȡ������");
//                     if (err_code != Err_Succeed)
//                         break;
//                 }
// 
//                 err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Open_InfoMatchFee, stock_trade_hr_ptr->getInfoMatchFee(), "ϵͳ������ȡ��Ϣ��Ϸ�");
// 
//                 break;
//             case AllTrade::DirectType::DIRECT_SELL:
//             {
//                 err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Close, stock_trade_hr_ptr->getTradePrice()*stock_trade_hr_ptr->getTradeVol(), "ϵͳƽ���ʽ𷵻�");
//                 if (err_code != Err_Succeed)
//                     break;
// 
//                 err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Close_Fee, stock_trade_hr_ptr->getTradeCommissionFee(), "ϵͳƽ����ȡ����Ӷ��");
//                 if (err_code != Err_Succeed)
//                     break;
// 
//                 err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Close_StampFee, stock_trade_hr_ptr->getStampFee(), "ϵͳƽ����ȡӡ��˰");
//                 if (err_code != Err_Succeed)
//                     break;
// 
//                 if (isXSHG)
//                 {
//                     err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Close_TransferFee, stock_trade_hr_ptr->getTransferFee(), "ϵͳƽ����ȡ������");
//                     if (err_code != Err_Succeed)
//                         break;
//                 }
// 
//                 err_code = IManagerCenter::instance()->moneyChange(stock_trade_hr_ptr->getUserID().c_str(), MC_Trade_Close_InfoMatchFee, stock_trade_hr_ptr->getInfoMatchFee(), "ϵͳƽ����ȡ��Ϣ��Ϸ�");
//                 if (err_code != Err_Succeed)
//                     break;
// 
//             }
//             break;
//             default:
//                 assert(0);
//                 break;
//             }
// 
//             dealCommissionParentMoney(stock_trade_hr_ptr, isXSHG);
// 
//             PositionHrPtr pos_hr_ptr(nullptr);
//             {
//                 writeLock lock(m_mtx);
//                 if (stock_trade_hr_ptr->getDirect() == DirectType::DIRECT_SELL)
//                 {
//                     auto pos_item = PositionListManager::instance()->getReversePosition(stock_trade_hr_ptr->getUserID().c_str(), stock_trade_hr_ptr->getContractID().c_str(), stock_trade_hr_ptr->getDirect());
//                     assert(pos_item);
//                     dealProfitParentMoney(pos_item, stock_trade_hr_ptr);
//                 }
// 
//                 LOG4CXX_INFO(logger, "�����ʽ�䶯����"LOG_NOVAR(use_id));
// #pragma endregion
// 
//                 // �ֲָı�
//                 pos_hr_ptr = PositionListManager::instance()->changePosition(stock_trade_hr_ptr);
//             }
//             TaskMsgOrderManager::instance()->handlePositionCbk(pos_hr_ptr->getUserID().c_str(), pos_hr_ptr->getPositionCopy(), trade_info_ptr);
//         }

        void StockServerMgr::dealCommissionParentMoney(const StockTradeHrPtr& stock_trade_ptr, bool isXSHG)
        {
            YDouble exchange_trade_fee(stock_trade_ptr->getTradeCommissionFee());

            if (isXSHG)
                exchange_trade_fee += stock_trade_ptr->getTransferFee();

            if (stock_trade_ptr->getDirect() == AllTrade::DirectType::DIRECT_SELL)
                exchange_trade_fee += stock_trade_ptr->getStampFee();

            // ��Ϸ�Ӷ����ȡ
            SAccountPtr self_ptr = IManagerCenter::instance()->getAccountByID(stock_trade_ptr->getUserID().c_str());
            if (!self_ptr)
            {
                assert(0);
                return;
            }

            std::vector<SAccountPtr> acc_vec;
            SAccountPtr parent_ptr = IManagerCenter::instance()->getAccountByID(self_ptr->parent_id_);
            while (parent_ptr)
            {
                acc_vec.insert(acc_vec.begin(), parent_ptr);
                parent_ptr = IManagerCenter::instance()->getAccountByID(parent_ptr->parent_id_);
            }
            if (acc_vec.empty()) return;

            YDouble last_exchange_trade_fee(0), last_custom_trade_fee(0);
            YDouble cur_exchange_trade_fee(exchange_trade_fee), cur_custom_trade_fee(stock_trade_ptr->getInfoMatchFee());

            size_t acc_count = acc_vec.size();
            int cur_acc_iter(0);
            std::string source_user_id;

            SAgencyMoneyDetailInfoPtr agy_detail = std::make_shared<SAgencyMoneyDetailInfo>();
            for (auto iter = acc_vec.begin(); iter != acc_vec.end(); iter++)
            {
                cur_acc_iter++;
                if (cur_acc_iter >= acc_count)
                    source_user_id = stock_trade_ptr->getUserID();
                else
                    source_user_id = acc_vec.at(cur_acc_iter)->user_id_;

                if (cur_exchange_trade_fee == 0.0 && cur_custom_trade_fee == 0.0)
                    break;

                // Ӷ�����
                YDouble commrate(0), custom_commrate(0);

                last_exchange_trade_fee = cur_exchange_trade_fee;
                last_custom_trade_fee = cur_custom_trade_fee;

                if (cur_acc_iter != 1)
                {
                    SRiskInfoPtr risk_ptr = IManagerCenter::instance()->getRiskInfoByLoginName((*iter)->login_name_);

                    cur_exchange_trade_fee = last_exchange_trade_fee * risk_ptr->commissionrate_ / 1000;       // ��һ�εĽ��׷���*���ν��ױ���
                    cur_custom_trade_fee = last_custom_trade_fee * risk_ptr->custom_commissionrate_ / 1000;  // ��һ�εĴ�Ϸѷ���*���ν��ױ���

                    commrate = risk_ptr->commissionrate_;
                    custom_commrate = risk_ptr->custom_commissionrate_;
                }
                else
                {
                    commrate = 1000;
                    custom_commrate = 1000;
                }

                if (cur_exchange_trade_fee != 0.0)
                    OperationManager::COperationManager::instance()->agencyMoneyChange(createAgencyMoneyDetailInfo((*iter)->user_id_, source_user_id.c_str(), Agency_Money_Change_Type::AMCT_Exchange_Commission, cur_exchange_trade_fee, commrate, "����Ӷ��"));

                if (cur_custom_trade_fee != 0.0)
                    OperationManager::COperationManager::instance()->agencyMoneyChange(createAgencyMoneyDetailInfo((*iter)->user_id_, source_user_id.c_str(), Agency_Money_Change_Type::AMCT_InfoMatch_Commission, cur_custom_trade_fee, custom_commrate, "��Ϸ�Ӷ��"));
            }
        }

        AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr StockServerMgr::createAgencyMoneyDetailInfo(const UserIDType user_id, const UserIDType source_user_id, Agency_Money_Change_Type type, YDouble money, YDouble commission_rate, const RemarkTextType remark)
        {
            SAgencyMoneyDetailInfoPtr agy_detail = std::make_shared<SAgencyMoneyDetailInfo>();
            agy_detail->change_money_ = money;
            agy_detail->change_type_ = type;
//             strncpy_s(agy_detail->stream_, UtilityFun::createGUID().c_str(), sizeof(agy_detail->stream_) - 1);
            strncpy_s(agy_detail->user_id_, user_id, sizeof(agy_detail->user_id_) - 1);
            strncpy_s(agy_detail->date_time_, UtilityFun::getCurrentDateTime().c_str(), sizeof(agy_detail->date_time_) - 1);
            strncpy_s(agy_detail->date_, UtilityFun::getCurrentDate().c_str(), sizeof(agy_detail->date_) - 1);
            strncpy_s(agy_detail->remark_, remark, sizeof(agy_detail->remark_) - 1);
            agy_detail->commission_rate_ = commission_rate;
            strncpy_s(agy_detail->source_user_id_, source_user_id, sizeof(agy_detail->source_user_id_) - 1);
            return agy_detail;
        }

        void StockServerMgr::dealProfitParentMoney(const PositionHrPtr& pos_item, const StockTradeHrPtr& stock_trade_ptr)
        {
            // ��Ϸ�Ӷ����ȡ
            SAccountPtr self_ptr = IManagerCenter::instance()->getAccountByID(stock_trade_ptr->getUserID().c_str());
            if (!self_ptr)
            {
                assert(0);
                return;
            }

            std::vector<SAccountPtr> acc_vec;
            SAccountPtr parent_ptr = IManagerCenter::instance()->getAccountByID(self_ptr->parent_id_);
            while (parent_ptr)
            {
                acc_vec.insert(acc_vec.begin(), parent_ptr);
                parent_ptr = IManagerCenter::instance()->getAccountByID(parent_ptr->parent_id_);
            }
            if (acc_vec.empty()) return;

            // �����˻��۳��ֳɳ��
            YDouble profitMoney = -((pos_item->getPositionCost() + stock_trade_ptr->getPositionCost() - stock_trade_ptr->getTradePrice() * stock_trade_ptr->getTradeVol()) / pos_item->getPositionAllVol() - stock_trade_ptr->getTradePrice())*stock_trade_ptr->getTradeVol();
            if (profitMoney <= 0.0)
                return;

            profitMoney = profitMoney * TradeFeeManager::instance()->getProfitRate();
            ErrorCodeType err_code = IManagerCenter::instance()->moneyChange(stock_trade_ptr->getUserID().c_str(), MC_Profit, profitMoney, "ϵͳ�ֳ�");
            if (err_code != Err_Succeed)
                LOG4CXX_ERROR(logger, "�ֳ���ȡ�޸��ʽ�ʧ��!"LOG_NOVAR(stock_trade_ptr->getUserID())LOG_NOVAR(profitMoney)LOG_NOVAR(TradeFeeManager::instance()->getProfitRate()));

            // �����˻��۳��ֳɳ��
            YDouble cur_profitMoney(profitMoney), last_profitMoney(0);

            size_t acc_count = acc_vec.size();
            int cur_acc_iter(0);
            std::string source_user_id;

            SAgencyMoneyDetailInfoPtr agy_detail = std::make_shared<SAgencyMoneyDetailInfo>();
            for (auto iter = acc_vec.begin(); iter != acc_vec.end(); iter++)
            {
                cur_acc_iter++;
                if (cur_acc_iter >= acc_count)
                    source_user_id = stock_trade_ptr->getUserID();
                else
                    source_user_id = acc_vec.at(cur_acc_iter)->user_id_;

                if (cur_profitMoney == 0.0)
                    break;

                last_profitMoney = cur_profitMoney;
                YDouble procommrate(0);


                if (cur_acc_iter != 1)
                {
                    SRiskInfoPtr risk_ptr = IManagerCenter::instance()->getRiskInfoByUserID((*iter)->user_id_);
                    procommrate = risk_ptr->procommrate_;
                    cur_profitMoney = last_profitMoney * procommrate / 1000;       // ��һ�εĽ��׷���*���ν��ױ���
                }
                else
                    procommrate = TradeFeeManager::instance()->getProfitValue();

                if (cur_profitMoney != 0.0)
                    OperationManager::COperationManager::instance()->agencyMoneyChange(createAgencyMoneyDetailInfo((*iter)->user_id_, source_user_id.c_str(), Agency_Money_Change_Type::AMCT_Trade_Profit, cur_profitMoney, procommrate, "ӯ���ֳ�"));
            }

        }

    }
}