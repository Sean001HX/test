#ifndef EXCHANGEHANDLER_H
#define EXCHANGEHANDLER_H

#include <map>
#include <mutex>
#include <atomic>
#include <boost\noncopyable.hpp>

#include "define/struct_extern.h"
#include "define/struct_declare.h"
#include "define/params_declare.h"
#include "../Application/user_class_declare.h"
#include "utility/rwmutex.h"
#include "SortIndex.h"

namespace AllTrade {
    namespace NPMgrCenter {

        class ExchangeBaseHandler
            : public std::enable_shared_from_this<ExchangeBaseHandler>
            , public boost::noncopyable
        {
        public:
            ExchangeBaseHandler();
            ExchangeBaseHandler(const SExchangePtr& exchange_ptr);
            ~ExchangeBaseHandler();

            // �ṹ(SAccountBase)��صĲ���
        public:
            // ���ؽ�����ID
            const PExchangeIDType getExchangeID() const;
            // ��ȡ������������
            const PExchangeNameType getExchangeName() const;
            // ��ȡ�������Ĵ���
            const PExchangeCodeType getExchangeCode() const;
            // ��ǰʱ���Ƿ���ύί��
            bool curCanOrder() const;
            // ��ǰʱ���Ƿ�ɽ���
            bool curCanTrade() const;
            // ָ��ʱ���Ƿ�ɽ���
            bool canTrade(const TimeType time) const;
            // ��ȡ������֤��
            YDouble getDGCT() const;

            // ��ȡ������Ľ�����ָ��
            // ע: ��ָ�벢���ڲ��ṹ��ָ��,�����ڲ��ṹ��ָ������,����޷�ֱ���޸��ڲ�����
            virtual SExchangePtr getCopyExchange() const = 0;
            // ��ȡ�����������к�Լ
            virtual std::vector<ContractHrPtr> getContractHrs() const = 0;
            // ����һ����Լ
            virtual ErrorCodeType addContract(const SContractPtr& contract_ptr) = 0;

        public:
            // ���ý���������
            void setExchangeName(const ExchangeNameType name);
            // �Ƿ�Ϊ�ս�����;
            virtual bool isEmpty() const = 0;

            // ���л�
            virtual ErrorCodeType serialize();
            virtual ErrorCodeType unserialize() = 0;

        protected:
            ContractHrPtr createContractHr(const SContractPtr& contract_ptr);
            // ����������Ϣ�����ݿ���ɾ��
            void remove(unsigned int db_ver);

        protected:
            // �������Ƿ��޸�
            bool isModified() const;
            // ����/��ȡ�޸ı��λ
            void resetCurExModiFlag(bool flag = true);
            bool getCurExModiFlag();


        protected:
            SExchangePtr        m_exchange_st_obj;	// �˻���Ӧ�����ݽṹ
            mutable rwMutex     m_mtx_sp;

            std::atomic<bool>   m_modified_cur;	    // ��ǰ���������޸�
        };

        class StockExchangeHandler : public ExchangeBaseHandler
        {
        public:
            StockExchangeHandler();
            StockExchangeHandler(const SExchangePtr& exchange_ptr);
            ~StockExchangeHandler();

            // ��ȡ������Ľ�����ָ��
            // ע: ��ָ�벢���ڲ��ṹ��ָ��,�����ڲ��ṹ��ָ������,����޷�ֱ���޸��ڲ�����
            SExchangePtr getCopyExchange() const override;
            // ��ȡ�����������к�Լ
            std::vector<ContractHrPtr> getContractHrs() const override;
            // ����һ����Լ
            ErrorCodeType addContract(const SContractPtr& contract_ptr) override;
            // ��ȡ��Լͨ��ID
            SContractPtr getStockContractByID(StockAreaType stock_area, const ContractIDType contract_id) const;
            SContractPtr getStockContractByCode(StockAreaType stock_area, const ContractCodeType contract_code) const;

        public:
            // �Ƿ�Ϊ��
            bool isEmpty() const override;
            // ��ȡ���к�Լ����
            int getContractCount() const;
            // ɾ��һ����Լ
            ErrorCodeType delContract(StockAreaType stock_area, const ContractIDType contract_id);
            // �����л�
            ErrorCodeType unserialize() override;

        private:
            std::map<StockAreaType, ContractIndex>  m_contracts;		// ������������Լ,���������, A/B...		
            mutable rwMutex		                    m_mtx_contract;

            std::atomic<bool>                       m_modified_contract;  // ������Լ���޸�
       };

    }	//! NPMgrCenter
}
#endif	// EXCHANGEHANDLER_H

