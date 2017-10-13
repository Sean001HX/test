/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      ManagerCenter.h
Author:			XuYC
Version:
Date:
Description:    �ṩ��Լģ��ͳһ�ӿ�
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
// #	pragma warning(disable: 4275) // �� DLL �ӿ������identifier����Ϊ DLL �ӿ������identifier���Ļ�ʹ��
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

            // ע���ʽ�ص�֪ͨ
            void setMoneyCbk(const MoneyCbk& fun);

#pragma region �˻�����
            // �Ƿ��ܵ�¼
            ErrorCodeType canLogin(const LoginNameType loginname, const LoginPasswordType password);

            // ����/��ȡ���˻�
//             void setRootAccount(const RootAccountPtr& root_ptr);
            RootAccountPtr getRootAccount() const;

            // ����ID��ȡ���и�����ܲ��˻�(��Խ��)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllParentsByID(const UserIDType user_id);

            // ����ID��ȡ�˻�
            AllTrade::NPMgrCenter::SAccountPtr getAccountByID(const UserIDType user_id);
            AllTrade::NPMgrCenter::SAccountPtr getAccountByLoginName(const LoginNameType loginname);
            // �����ƹ����ҵ��˻�
            AllTrade::NPMgrCenter::SAccountPtr getAccountByPopLink(const PopularizeLinkType poplink);

            // ��ȡָ���ʻ��µ������˻�(��Խ��)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllChildren(const UserIDType parent_id);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllTradeAccByLoginName(const LoginNameType parent_loginname);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllUsingTradeAccByLoginName(const LoginNameType parent_loginname);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllCheckingTradeAccByLoginName(const LoginNameType parent_loginname);
            // ��ȡָ���ʻ��µ����л����˻�(��Խ��)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllAgencys(const UserIDType parent_id);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllAgencysByLoginName(const LoginNameType parent_loginname);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllUsingAgencysByLoginName(const LoginNameType parent_loginname);
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllCheckingAgencysByLoginName(const LoginNameType parent_loginname);
            // ��ȡָ���ʻ��µ����м�ܲ��˻�(��Խ��)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllMonits(const UserIDType parent_id);
            // ��ȡָ���ʻ��µ����н����˻�(��Խ��)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllTrades(const UserIDType parent_id);
            // ��ȡָ���˻��µ�����ʵ���˻�(��Խ��)
            std::vector<AllTrade::NPMgrCenter::SAccountPtr> getAllFunderAccByLoginName(const LoginNameType loginname);
            // ��ȡָ���ʻ��µ����й����˻�(!!!����Խ��)
            std::vector<AllTrade::NPMgrCenter::ManagerAccountPtr> getManagersByLoginName(const LoginNameType loginname);

			// ��ȡָ���ʻ��µ����л����˻�(!!!����Խ��)
			AllTrade::NPMgrCenter::AgencyAccountPtr getAgencyByLoginName(const LoginNameType loginname);

            // �����˻�
            ErrorCodeType addAccount(SAccountPtr child, SMoneyInfoPtr money, SRiskInfoPtr risk);
            // �����˻�
            ErrorCodeType updateAccount(const SAccountPtr& sacc);
            // ����˻�
			ErrorCodeType checkAccount(const UserIDType user_id, E_ACCOUNT_STATUS bcheck, const LoginNameType auditor_name = "");
            // ���·����Ϣ
            ErrorCodeType updateRisk(const UserIDType user_id, SRiskInfoPtr sacc);

            // ���ݵ�¼����ȡ�ʽ���Ϣ
            AllTrade::NPMgrCenter::SMoneyInfoPtr getMoneyInfoByLoginName(const LoginNameType loginname);
            AllTrade::NPMgrCenter::SRiskInfoPtr getRiskInfoByLoginName(const LoginNameType loginname);
            AllTrade::NPMgrCenter::SRiskInfoPtr getRiskInfoByUserID(const UserIDType user_id);

            // �ֲֳɱ��仯
            ErrorCodeType changePositionCost(const UserIDType user_id, YDouble cost_money, int vol, DirectType direct);
            // �ʽ�䶯
            ErrorCodeType moneyChange(const UserIDType user_id, Money_Change_Type money_change, YDouble money, const RemarkTextType remark);
            // ���������ʽ�
            ErrorCodeType applyMoney(const UserIDType user_id, YDouble money, AllTrade::OIMM_Change_Type money_type, SApplyMoneyPtr ptr=nullptr);
            // ����������ʽ��
            ErrorCodeType approvalApplyMoney(const AllTrade::UserIDType approval_user_id, const AllTrade::UserIDType apply_user_id, const ApplyMoneyIDType apply_money_id, E_APPLY_MONEY_STATUS apply_status, AllTrade::OIMM_Change_Type money_type);
            // ��ѯ�����ʽ�
            std::vector<AllTrade::NPMgrCenter::SApplyMoneyPtr> getApplyMoney(const UserIDType user_id, const DateType start_day, const DateType end_day, AllTrade::OIMM_Change_Type money_type);
            AllTrade::NPMgrCenter::SApplyMoneyPtr getApplyMoneyPtr(const AllTrade::ApplyMoneyIDType apply_money_id, AllTrade::OIMM_Change_Type type);
            // �ж��Ƿ�����µ�(�ʽ����)
            ErrorCodeType canOrder(const UserIDType user_id, YDouble highest_price);
            ErrorCodeType canTrade(const UserIDType user_id, YDouble highest_price);

            // ���÷�ر�־
			void triggerUserRiskControl(const PRemarkTextType text,const UserIDType user_id, RiskControlType rc_type, bool bTrigger);
            bool getUserIsInRiskControl(const UserIDType user_id, RiskControlType rc_type);

            // �����ʽ���ˮ
            std::vector<AllTrade::NPMgrCenter::SMoneyDetailInfoPtr> getFundSerial(const UserIDType user_id, const DateType start_day, const DateType end_day);

            // �޸�����
            ErrorCodeType changePassword(const UserIDType user_id, const LoginPasswordType old_pass, const LoginPasswordType new_pass);

            // ɾ���˻�
            ErrorCodeType deleteAccount(const UserIDType user_id);

#pragma endregion

#pragma region ��Ʒ����
            // ��ǰʱ���Ƿ���ύί��
            bool curCanOrder(CommodityTypeType commodity_type, const ExchangeIDType exchange_id, const ContractIDType contract_id) const;
            // ��ǰʱ���Ƿ�ɽ���
            bool curCanTrade(CommodityTypeType commodity_type, const ExchangeIDType exchange_id, const ContractIDType contract_id) const;
            // ��ǰ��Լ�Ƿ�ɽ���
            ErrorCodeType canTradeContract(CommodityTypeType commodity_type, const ExchangeIDType exchange_id, const ContractIDType contract_id) const;

            // ��ȡ�������б�
            std::vector<SExchangePtr> getExchanges(CommodityTypeType commodity_type) const;
            SExchangePtr getExchangeByID(CommodityTypeType commodity_type, const ExchangeIDType exchange_id) const;
            // �Ϻ� XSHG, ���� XSHE
            SExchangePtr getExchangeByCode(CommodityTypeType commodity_type, const ExchangeCodeType exchange_code) const;
            // ����/���½�����
            ErrorCodeType addExchange(const SExchangePtr& ex);

            // ��ȡ��������Լ�б�
            SContractPtr getStockContractByID(StockAreaType stock_area, const ContractIDType contract_id) const;
            SContractPtr getStockContractByCode(StockAreaType stock_area, const ContractCodeType contract_code) const;
            std::vector<SContractPtr> getContracts(const SExchangePtr& ex) const;
            std::vector<SContractPtr> getContracts(CommodityTypeType commodity_type, const ExchangeIDType exchange_id) const;
            // ����/���½�������Լ
            ErrorCodeType addContract(const SContractPtr& contract);

            // ��ѯ�ڰ������б�
            std::map<AllTrade::PContractIDType, bool> qryStockBlackWhiteStatus();
            ErrorCodeType setStockBlackWhiteStatus(const ContractIDType contract_id, bool isBlack);

            // ��ȡ��ѡ��Ʊ
            std::vector<SContractPtr> getCustomStockContractsByUserID(/*const SExchangePtr& ex, */const UserIDType user_id) const;
            // ������ѡ��Ʊ
            ErrorCodeType addCustomStockContractsByUserID(const SContractPtr& contract, const UserIDType user_id) const;
            // ɾ����ѡ��Ʊ
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