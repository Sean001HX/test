#ifndef CONTRACTHANDLER_H
#define CONTRACTHANDLER_H

#include <mutex>
#include <atomic>
#include <boost\noncopyable.hpp>

#include "define/struct_base.h"
#include "define/struct_declare.h"
#include "utility/rwmutex.h"
#include "define/params_declare.h"
#include "../Application/user_class_declare.h"

namespace AllTrade {
    namespace NPMgrCenter {

        class ContractBaseHandler
            : public std::enable_shared_from_this<ContractBaseHandler>
            , public boost::noncopyable
        {
        public:
            ContractBaseHandler();
            ContractBaseHandler(const SContractPtr& contract_st);
            ~ContractBaseHandler();

            // �ṹ(SContractInfo)��صĲ���
        public:
            // ����������������ID
            PExchangeIDType getBelongExID() const;
            // ���غ�ԼID
            PContractIDType getContractID() const;
            // ��ȡ��Լ������
            PContractNameType getContractName() const;
            // ��ȡ��Լ�Ĵ���
            PContractCodeType getContractCode() const;
            // ��ǰʱ���Ƿ�ɽ���
            bool curCanTrade() const;
            // ָ��ʱ���Ƿ�ɽ���
            bool canTrade(const TimeType time) const;
            // ��ȡ��Լ�Ŀ���������
            const Feest& getContractOpenFee() const;
            // ��ȡ��Լ��ƽ��������
//             const Feest& getContractCloseYestodayFee() const;
            // ��ȡ��Լ��ƽ��������
//             const Feest& getContractCloseTodayFee() const;
            // ��ȡ��Լ�Ľ��ױ�֤��
            const Feest& getContractMargin() const;
            // ��ȡ��Լ�ĺ�Լ����
            int getContractMultiple() const;
            // ��ȡ��Լ����С�䶯��λ
            YDouble getContractMinChUnit() const;

            // ��ȡ������ĺ�Լָ��
            // ע: ��ָ�벢���ڲ��ṹ��ָ��,�����ڲ��ṹ��ָ������,����޷�ֱ���޸��ڲ�����
            virtual SContractPtr getCopyContract() const = 0;
            
            // ��ȡ��Ʊ�������,����/��ҵ��...
            virtual StockPlateAreaType getContractPlateArea() const = 0;
        public:
            // ���л�
            ErrorCodeType serialize();

        protected:
            // ����Լ��Ϣ�����ݿ���ɾ��
//             void remove(unsigned int db_ver);
            // �ӵ�ǰ��Լ�����Ƴ�һ���µĺ�Լ����
            // ����ֵ�� �¸��Ƴɹ��ĺ�Լ����
//             virtual ContractHrPtr copy() = 0;

        protected:
            // ��Լ�Ƿ��޸�
            bool isModified() const;

            // �����޸ı��λ
            void setCurContractModiFlag(bool flag = true);
            // ��ȡ�޸ı��λ
            bool getCurContractModiFlag();

        protected:
            SContractPtr		m_contract_st_obj;	// �˻���Ӧ�����ݽṹ
            mutable rwMutex		m_mtx_sp;

            std::atomic<bool>	m_modified_cur;		// ��ǰ��Լ���޸�
        };

        class StockContractHandler : public ContractBaseHandler
        {
        public:
            StockContractHandler();
            StockContractHandler(const SContractPtr& contract_st);
            ~StockContractHandler();

            // ��ȡ��������
            AllTrade::StockAreaType getStockArea();
            // ��ȡ������ĺ�Լָ��
            SContractPtr getCopyContract() const override;
            // ��ȡ��Ʊ�������,����/��ҵ��...
            StockPlateAreaType getContractPlateArea() const override;

        public:
            //���������˻�����
            StockExchangeHrPtr getParentExHandler()
            {
                return m_parent.lock();
            }

        private:
            StockExchangeHrWPtr m_parent;
        };
    }	//! NPMgrCenter
}
#endif	// CONTRACTHANDLER_H

