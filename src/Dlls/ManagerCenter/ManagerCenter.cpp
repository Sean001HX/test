#include "include/ManagerCenter/ManagerCenter.h"
#include "CommodityManager.h"
#include "UserManager.h"
#include "Application/BlackWhiteManager.h"
#include "define/struct_extern.h"
#include "Application/CustomStockManager.h"

namespace AllTrade{
    namespace NPMgrCenter {

        IManagerCenter::IManagerCenter()
            : m_contractmgr_center(new CommodityManager)
            , m_usermgr_center(new UserManager)
        {

        }

        IManagerCenter::~IManagerCenter()
        {
            BlackWhiteManager::unInstance();

            if (m_usermgr_center)
            {
                delete m_usermgr_center;
                m_usermgr_center = nullptr;
            }

            if (m_contractmgr_center)
            {
                delete m_contractmgr_center;
                m_usermgr_center = nullptr;
            }
        }

        void IManagerCenter::setMoneyCbk(const MoneyCbk& fun)
        {
            m_usermgr_center->setMoneyCbk(fun);
        }

#pragma region 账户管理
        ErrorCodeType IManagerCenter::canLogin(const LoginNameType loginname, const LoginPasswordType password)
        {
            return m_usermgr_center->canLogin(loginname, password);
        }
        
//         void IManagerCenter::setRootAccount(const RootAccountPtr& root_ptr)
//         {
//             m_usermgr_center->setRootAccount(root_ptr);
//         }

        RootAccountPtr IManagerCenter::getRootAccount() const
        {
            return m_usermgr_center->getRootAccount();
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> IManagerCenter::getAllParentsByID(const UserIDType user_id)
        {
            return m_usermgr_center->getAllParentsByID(user_id);
        }

        AllTrade::NPMgrCenter::SAccountPtr IManagerCenter::getAccountByID(const UserIDType user_id)
        {
            return m_usermgr_center->getAccountByID(user_id);
        }

        AllTrade::NPMgrCenter::SAccountPtr IManagerCenter::getAccountByLoginName(const LoginNameType loginname)
        {
            return m_usermgr_center->getAccountByLoginName(loginname);
        }

        AllTrade::NPMgrCenter::SAccountPtr IManagerCenter::getAccountByPopLink(const PopularizeLinkType poplink)
        {
            return m_usermgr_center->getAccountByPopLink(poplink);
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> IManagerCenter::getAllChildren(const UserIDType parent_id)
        {
            return m_usermgr_center->getAllChildren(parent_id);
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> IManagerCenter::getAllTradeAccByLoginName(const LoginNameType parent_loginname)
        {
            return m_usermgr_center->getAllTradeAccByLoginName(parent_loginname);
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> IManagerCenter::getAllUsingTradeAccByLoginName(const LoginNameType parent_loginname)
        {
            return m_usermgr_center->getAllUsingTradeAccByLoginName(parent_loginname);
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> IManagerCenter::getAllCheckingTradeAccByLoginName(const LoginNameType parent_loginname)
        {
            return m_usermgr_center->getAllCheckingTradeAccByLoginName(parent_loginname);
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> IManagerCenter::getAllAgencys(const UserIDType parent_id)
        {
            return m_usermgr_center->getAllAgencys(parent_id);
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> IManagerCenter::getAllAgencysByLoginName(const LoginNameType parent_loginname)
        {
            return m_usermgr_center->getAllAgencysByLoginName(parent_loginname);
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> IManagerCenter::getAllUsingAgencysByLoginName(const LoginNameType parent_loginname)
        {
            return m_usermgr_center->getAllUsingAgencysByLoginName(parent_loginname);
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> IManagerCenter::getAllCheckingAgencysByLoginName(const LoginNameType parent_loginname)
        {
            return m_usermgr_center->getAllCheckingAgencysByLoginName(parent_loginname);
        }

        std::vector<SAccountPtr> IManagerCenter::getAllMonits(const UserIDType parent_id)
        {
            return m_usermgr_center->getAllMonits(parent_id);
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> IManagerCenter::getAllTrades(const UserIDType parent_id)
        {
            return m_usermgr_center->getAllTrades(parent_id);
        }

        std::vector<AllTrade::NPMgrCenter::SAccountPtr> IManagerCenter::getAllFunderAccByLoginName(const LoginNameType loginname)
        {
            return m_usermgr_center->getAllFunderAccByLoginName(loginname);
        }

        std::vector<AllTrade::NPMgrCenter::ManagerAccountPtr> IManagerCenter::getManagersByLoginName(const LoginNameType loginname)
        {
            return m_usermgr_center->getManagersByLoginName(loginname);
        }


		AllTrade::NPMgrCenter::AgencyAccountPtr IManagerCenter::getAgencyByLoginName(const LoginNameType loginname)
		{
			return m_usermgr_center->getAgencyByLoginName(loginname);
		}


        AllTrade::ErrorCodeType IManagerCenter::addAccount(SAccountPtr child, SMoneyInfoPtr money, SRiskInfoPtr risk)
        {
            return m_usermgr_center->addAccount(child, money, risk);
        }

        AllTrade::ErrorCodeType IManagerCenter::updateAccount(const SAccountPtr& sacc)
        {
            return m_usermgr_center->updateAccount(sacc);
        }

		AllTrade::ErrorCodeType IManagerCenter::checkAccount(const UserIDType user_id, E_ACCOUNT_STATUS bcheck, const LoginNameType auditor_name)
        {
			return m_usermgr_center->checkAccount(user_id, bcheck, auditor_name);
        }

        AllTrade::ErrorCodeType IManagerCenter::updateRisk(const UserIDType user_id, SRiskInfoPtr sacc)
        {
            return m_usermgr_center->updateRisk(user_id, sacc);
        }

        AllTrade::NPMgrCenter::SMoneyInfoPtr IManagerCenter::getMoneyInfoByLoginName(const LoginNameType loginname)
        {
            return m_usermgr_center->getMoneyInfoByLoginName(loginname);
        }

        AllTrade::NPMgrCenter::SRiskInfoPtr IManagerCenter::getRiskInfoByLoginName(const LoginNameType loginname)
        {
            return m_usermgr_center->getRiskInfoByLoginName(loginname);
        }

        AllTrade::NPMgrCenter::SRiskInfoPtr IManagerCenter::getRiskInfoByUserID(const UserIDType user_id)
        {
            return m_usermgr_center->getRiskInfoByUserID(user_id);
        }

        AllTrade::ErrorCodeType IManagerCenter::changePositionCost(const UserIDType user_id, YDouble cost_money, int vol, DirectType direct)
        {
            return m_usermgr_center->changePositionCost(user_id, cost_money, vol, direct);
        }

//         AllTrade::ErrorCodeType IManagerCenter::outInMoney(const LoginNameType loginname, OIMM_Change_Type iotype, YDouble money, const RemarkTextType remark)
//         {
//             return m_usermgr_center->outInMoney(loginname, iotype, money, remark);
//         }

        AllTrade::ErrorCodeType IManagerCenter::moneyChange(const UserIDType user_id, Money_Change_Type money_change, YDouble money, const RemarkTextType remark)
        {
            return m_usermgr_center->moneyChange(user_id, money_change, money, remark);
        }

        AllTrade::ErrorCodeType IManagerCenter::applyMoney(const UserIDType user_id, YDouble money, AllTrade::OIMM_Change_Type money_type, SApplyMoneyPtr ptr)
        {
            return m_usermgr_center->applyMoney(user_id, money, money_type, ptr);
        }

        ErrorCodeType IManagerCenter::approvalApplyMoney(const AllTrade::UserIDType approval_user_id, const AllTrade::UserIDType apply_user_id, const ApplyMoneyIDType apply_money_id, E_APPLY_MONEY_STATUS apply_status, AllTrade::OIMM_Change_Type money_type)
        {
            return m_usermgr_center->approvalApplyMoney(approval_user_id, apply_user_id, apply_money_id, apply_status, money_type);
        }

        std::vector<AllTrade::NPMgrCenter::SApplyMoneyPtr> IManagerCenter::getApplyMoney(const UserIDType user_id, const DateType start_day, const DateType end_day, AllTrade::OIMM_Change_Type money_type)
        {
            return m_usermgr_center->getApplyMoney(user_id, start_day, end_day, money_type);
        }

        AllTrade::NPMgrCenter::SApplyMoneyPtr IManagerCenter::getApplyMoneyPtr(const AllTrade::ApplyMoneyIDType apply_money_id, AllTrade::OIMM_Change_Type type)
        {
            return m_usermgr_center->getApplyMoneyPtr(apply_money_id, type);
        }

        AllTrade::ErrorCodeType IManagerCenter::canOrder(const UserIDType user_id, YDouble highest_price)
        {
            return m_usermgr_center->canOrder(user_id, highest_price);
        }

        AllTrade::ErrorCodeType IManagerCenter::canTrade(const UserIDType user_id, YDouble highest_price)
        {
            return m_usermgr_center->canTrade(user_id, highest_price);
        }

		void IManagerCenter::triggerUserRiskControl(const PRemarkTextType text, const UserIDType user_id, RiskControlType rc_type, bool bTrigger)
        {
			return m_usermgr_center->triggerUserRiskControl(text, user_id, rc_type, bTrigger);
        }

        bool IManagerCenter::getUserIsInRiskControl(const UserIDType user_id, RiskControlType rc_type)
        {
            return m_usermgr_center->getUserIsInRiskControl(user_id, rc_type);
        }

        std::vector<AllTrade::NPMgrCenter::SMoneyDetailInfoPtr> IManagerCenter::getFundSerial(const UserIDType user_id, const DateType start_day, const DateType end_day)
        {
            return m_usermgr_center->getFundSerial(user_id, start_day, end_day);
        }

        AllTrade::ErrorCodeType IManagerCenter::changePassword(const UserIDType user_id, const LoginPasswordType old_pass, const LoginPasswordType new_pass)
        {
            return m_usermgr_center->changePassword(user_id, old_pass, new_pass);
        }

        AllTrade::ErrorCodeType IManagerCenter::deleteAccount(const UserIDType user_id)
        {
            return m_usermgr_center->deleteAccount(user_id);
        }

#pragma endregion

#pragma region 商品管理
        bool IManagerCenter::curCanOrder(CommodityTypeType commodity_type, const ExchangeIDType exchange_id, const ContractIDType contract_id) const
        {
            return m_contractmgr_center->curCanOrder(commodity_type, exchange_id, contract_id);
        }

        bool IManagerCenter::curCanTrade(CommodityTypeType commodity_type, const ExchangeIDType exchange_id, const ContractIDType contract_id) const
        {
            return m_contractmgr_center->curCanTrade(commodity_type, exchange_id, contract_id);
        }

        AllTrade::ErrorCodeType IManagerCenter::canTradeContract(CommodityTypeType commodity_type, const ExchangeIDType exchange_id, const ContractIDType contract_id) const
        {
            return BlackWhiteManager::instance()->canTradeContract(commodity_type, exchange_id, contract_id);
        }

        std::vector<SExchangePtr> IManagerCenter::getExchanges(CommodityTypeType commodity_type) const
        {
            return m_contractmgr_center->getExchanges(commodity_type);
        }

        AllTrade::NPMgrCenter::SExchangePtr IManagerCenter::getExchangeByID(CommodityTypeType commodity_type, const ExchangeIDType exchange_id) const
        {
            return m_contractmgr_center->getExchangeByID(commodity_type, exchange_id);
        }

        AllTrade::NPMgrCenter::SExchangePtr IManagerCenter::getExchangeByCode(CommodityTypeType commodity_type, const ExchangeCodeType exchange_code) const
        {
            return m_contractmgr_center->getExchangeByCode(commodity_type, exchange_code);
        }

        AllTrade::ErrorCodeType IManagerCenter::addExchange(const SExchangePtr& ex)
        {
            return m_contractmgr_center->addExchange(ex);
        }

        std::vector<SContractPtr> IManagerCenter::getContracts(const SExchangePtr& ex) const
        {
            return m_contractmgr_center->getContracts(ex);
        }

        std::vector<SContractPtr> IManagerCenter::getContracts(CommodityTypeType commodity_type, const ExchangeIDType exchange_id) const
        {
            return m_contractmgr_center->getContracts(commodity_type, exchange_id);
        }

        AllTrade::ErrorCodeType IManagerCenter::addContract(const SContractPtr& contract)
        {
            BlackWhiteManager::instance()->addStockBlackWhite(contract->contract_id_);
            return m_contractmgr_center->addContract(contract);
        }

        std::map<AllTrade::PContractIDType, bool> IManagerCenter::qryStockBlackWhiteStatus()
        {
            return BlackWhiteManager::instance()->getAllStockBlackWhiteStatus();
        }

        AllTrade::ErrorCodeType IManagerCenter::setStockBlackWhiteStatus(const ContractIDType contract_id, bool isBlack)
        {
            return BlackWhiteManager::instance()->updateStockBlackWhiteStatus(contract_id,  isBlack);
        }

        std::vector<AllTrade::NPMgrCenter::SContractPtr> IManagerCenter::getCustomStockContractsByUserID(/*const SExchangePtr& ex, */const UserIDType user_id) const
        {
            std::vector<AllTrade::NPMgrCenter::SContractPtr> rslt;
            std::vector<AllTrade::PContractIDType> rslt_id = CustomStockManager::instance()->getAllCustomStock(user_id);
            for (auto& item : rslt_id)
            {
                SContractPtr ptr = m_contractmgr_center->getStockContractByID(StockAreaType::STOCKAREA_TYPE_A, item.c_str());
                if (ptr)
                    rslt.push_back(ptr);
            }
            return rslt;
        }

        AllTrade::ErrorCodeType IManagerCenter::addCustomStockContractsByUserID(const SContractPtr& contract, const UserIDType user_id) const
        {
            return CustomStockManager::instance()->addCustomStock(user_id, contract->contract_id_);
        }

        AllTrade::ErrorCodeType IManagerCenter::delCustomStockContractsByUserID(const SContractPtr& contract, const UserIDType user_id) const
        {
            return CustomStockManager::instance()->removeCustomStock(user_id, contract->contract_id_);
        }

        AllTrade::NPMgrCenter::SContractPtr IManagerCenter::getStockContractByID(StockAreaType stock_area, const ContractIDType contract_id) const
        {
            return m_contractmgr_center->getStockContractByID(stock_area, contract_id);
        }

        AllTrade::NPMgrCenter::SContractPtr IManagerCenter::getStockContractByCode(StockAreaType stock_area, const ContractCodeType contract_code) const
        {
            return m_contractmgr_center->getStockContractByCode(stock_area, contract_code);
        }

#pragma endregion

    }
}