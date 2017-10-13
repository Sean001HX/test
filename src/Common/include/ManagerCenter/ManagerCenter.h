/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      ManagerCenter.h
Author:			XuYC
Version:
Date:
Description:    提供合约模块统一接口
*************************************************/

#ifndef __ICONTRACT_H__
#define __ICONTRACT_H__

#include <vector>
#include <map>
#include "utility/instance_shared_from_this.h"
#include "define/struct_declare.h"
#include "define/params_declare.h"
#include "define/ystruct_define.h"

#ifdef HX_IMGR_API_EXPORTS
#define HX_IMGR_API_API __declspec(dllexport)
#else
#define HX_IMGR_API_API __declspec(dllimport)
#endif

#ifdef _MSC_VER
#	pragma warning(push)
#   pragma warning(disable: 4251) 
// #	pragma warning(disable: 4275) // 非 DLL 接口类键“identifier”作为 DLL 接口类键“identifier”的基使用
#endif

namespace AllTrade{
    namespace NPMgrCenter{

        class CommodityManager;
        class UserManager;

        class HX_IMGR_API_API IManagerCenter : public CommonTools::instance_shared_from_this<IManagerCenter>
        {
            typedef std::function<void(const AllTrade::UserIDType user_id, const NPMgrCenter::SMoneyInfoPtr& money_ptr)>  MoneyCbk;

        public:
            IManagerCenter();
            ~IManagerCenter();

            // 注册资金回调通知
            void setMoneyCbk(const MoneyCbk& fun);

#pragma region 账户管理
            // 是否能登录
            ErrorCodeType canLogin(const LoginNameType loginname, const LoginPasswordType password);

            // 设置/获取根账户
//             void setRootAccount(const RootAccountPtr& root_ptr);
            RootAccountPtr getRootAccount() const;

            // 根据ID获取所有父级监管层账户(含越级)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllParentsByID(const UserIDType user_id);

            // 根据ID获取账户
            AllTrade::NPMgrCenter::SAccountPtr getAccountByID(const UserIDType user_id);
            AllTrade::NPMgrCenter::SAccountPtr getAccountByLoginName(const LoginNameType loginname);
            // 根据推广码找到账户
            AllTrade::NPMgrCenter::SAccountPtr getAccountByPopLink(const PopularizeLinkType poplink);

            // 获取指定帐户下的所有账户(含越级)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllChildren(const UserIDType parent_id);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllTradeAccByLoginName(const LoginNameType parent_loginname);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllUsingTradeAccByLoginName(const LoginNameType parent_loginname);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllCheckingTradeAccByLoginName(const LoginNameType parent_loginname);
            // 获取指定帐户下的所有机构账户(含越级)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllAgencys(const UserIDType parent_id);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllAgencysByLoginName(const LoginNameType parent_loginname);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllUsingAgencysByLoginName(const LoginNameType parent_loginname);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllCheckingAgencysByLoginName(const LoginNameType parent_loginname);
            // 获取指定帐户下的所有监管层账户(含越级)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllMonits(const UserIDType parent_id);
            // 获取指定帐户下的所有交易账户(含越级)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllTrades(const UserIDType parent_id);
            // 获取指定账户下的所有实盘账户(含越级)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllFunderAccByLoginName(const LoginNameType loginname);
            // 获取指定帐户下的所有管理账户(!!!不含越级)
            std::vector<AllTrade::NPMgrCenter::ManagerAccountPtr> getManagersByLoginName(const LoginNameType loginname);

			// 获取指定帐户下的所有机构账户(!!!不含越级)
			AllTrade::NPMgrCenter::AgencyAccountPtr getAgencyByLoginName(const LoginNameType loginname);

            // 新增账户
            ErrorCodeType addAccount(SAccountPtr child, SMoneyInfoPtr money, SRiskInfoPtr risk);
            // 更新账户
            ErrorCodeType updateAccount(const SAccountPtr& sacc);
            // 审核账户
			ErrorCodeType checkAccount(const UserIDType user_id, E_ACCOUNT_STATUS bcheck, const LoginNameType auditor_name = "");
            // 更新风控信息
            ErrorCodeType updateRisk(const UserIDType user_id, SRiskInfoPtr sacc);

            // 根据登录名获取资金信息
            AllTrade::NPMgrCenter::SMoneyInfoPtr getMoneyInfoByLoginName(const LoginNameType loginname);
            AllTrade::NPMgrCenter::SRiskInfoPtr getRiskInfoByLoginName(const LoginNameType loginname);
            AllTrade::NPMgrCenter::SRiskInfoPtr getRiskInfoByUserID(const UserIDType user_id);

            // 持仓成本变化
            ErrorCodeType changePositionCost(const UserIDType user_id, YDouble cost_money, int vol, DirectType direct);
            // 资金变动
            ErrorCodeType moneyChange(const UserIDType user_id, Money_Change_Type money_change, YDouble money, const RemarkTextType remark);
            // 申请融资资金
            ErrorCodeType applyMoney(const UserIDType user_id, YDouble money, AllTrade::OIMM_Change_Type money_type, SApplyMoneyPtr ptr=nullptr);
            // 审核申请融资金额
            ErrorCodeType approvalApplyMoney(const AllTrade::UserIDType approval_user_id, const AllTrade::UserIDType apply_user_id, const ApplyMoneyIDType apply_money_id, E_APPLY_MONEY_STATUS apply_status, AllTrade::OIMM_Change_Type money_type);
            // 查询融资资金
            std::vector<AllTrade::NPMgrCenter::SApplyMoneyPtr> getApplyMoney(const UserIDType user_id, const DateType start_day, const DateType end_day, AllTrade::OIMM_Change_Type money_type);
            AllTrade::NPMgrCenter::SApplyMoneyPtr getApplyMoneyPtr(const AllTrade::ApplyMoneyIDType apply_money_id, AllTrade::OIMM_Change_Type type);
            // 判断是否可以下单(资金相关)
            ErrorCodeType canOrder(const UserIDType user_id, YDouble highest_price);
            ErrorCodeType canTrade(const UserIDType user_id, YDouble highest_price);

            // 设置风控标志
			void triggerUserRiskControl(const PRemarkTextType text,const UserIDType user_id, RiskControlType rc_type, bool bTrigger);
            bool getUserIsInRiskControl(const UserIDType user_id, RiskControlType rc_type);

            // 设置资金流水
            std::vector<AllTrade::NPMgrCenter::SMoneyDetailInfoPtr> getFundSerial(const UserIDType user_id, const DateType start_day, const DateType end_day);

            // 修改密码
            ErrorCodeType changePassword(const UserIDType user_id, const LoginPasswordType old_pass, const LoginPasswordType new_pass);

            // 删除账户
            ErrorCodeType deleteAccount(const UserIDType user_id);

#pragma endregion

#pragma region 商品管理
            // 当前时间是否可提交委托
            bool curCanOrder(CommodityTypeType commodity_type, const ExchangeIDType exchange_id, const ContractIDType contract_id) const;
            // 当前时间是否可交易
            bool curCanTrade(CommodityTypeType commodity_type, const ExchangeIDType exchange_id, const ContractIDType contract_id) const;
            // 当前合约是否可交易
            ErrorCodeType canTradeContract(CommodityTypeType commodity_type, const ExchangeIDType exchange_id, const ContractIDType contract_id) const;

            // 获取交易所列表
            std::vector<SExchangePtr> getExchanges(CommodityTypeType commodity_type) const;
            SExchangePtr getExchangeByID(CommodityTypeType commodity_type, const ExchangeIDType exchange_id) const;
            // 上海 XSHG, 深圳 XSHE
            SExchangePtr getExchangeByCode(CommodityTypeType commodity_type, const ExchangeCodeType exchange_code) const;
            // 新增/更新交易所
            ErrorCodeType addExchange(const SExchangePtr& ex);

            // 获取交易所合约列表
            SContractPtr getStockContractByID(StockAreaType stock_area, const ContractIDType contract_id) const;
            SContractPtr getStockContractByCode(StockAreaType stock_area, const ContractCodeType contract_code) const;
            std::vector<SContractPtr> getContracts(const SExchangePtr& ex) const;
            std::vector<SContractPtr> getContracts(CommodityTypeType commodity_type, const ExchangeIDType exchange_id) const;
            // 新增/更新交易所合约
            ErrorCodeType addContract(const SContractPtr& contract);

            // 查询黑白名单列表
            std::map<AllTrade::PContractIDType, bool> qryStockBlackWhiteStatus();
            ErrorCodeType setStockBlackWhiteStatus(const ContractIDType contract_id, bool isBlack);

            // 获取自选股票
            std::vector<SContractPtr> getCustomStockContractsByUserID(/*const SExchangePtr& ex, */const UserIDType user_id) const;
            // 新增自选股票
            ErrorCodeType addCustomStockContractsByUserID(const SContractPtr& contract, const UserIDType user_id) const;
            // 删除自选股票
            ErrorCodeType delCustomStockContractsByUserID(const SContractPtr& contract, const UserIDType user_id) const;

#pragma endregion

        private:
            CommodityManager* m_contractmgr_center;
            UserManager*     m_usermgr_center;
        };
    }
}
#if defined(_MSC_VER)
#	pragma warning(pop)
#endif

#endif