#ifndef VARTYHANDLER_H
#define VARTYHANDLER_H

#include <mutex>
#include <atomic>
#include <boost\noncopyable.hpp>
#include <boost\multi_index_container.hpp>
#include <boost\multi_index\mem_fun.hpp>
#include <boost\multi_index\ordered_index.hpp>
#include <boost\multi_index\global_fun.hpp>

#include "define/struct_base.h"
#include "define/struct_declare.h"
#include "define/params_declare.h"
#include "../Application/user_class_declare.h"
#include "utility/rwmutex.h"

namespace AllTrade {
    namespace NPMgrCenter
    {
        //////////////////////////////////////////////////////////////////////////
        // ���ڶ�����������ȫ�ֺ���
        const PContractNameType get_contract_name(const ContractHrPtr& pContract);
        const PContractIDType get_contract_guid(const ContractHrPtr& pContract);
        const PContractCodeType get_contract_code(const ContractHrPtr& pContract);

        class CProductHandler
            : public std::enable_shared_from_this<CProductHandler>
            , public boost::noncopyable
        {
            friend class ExchangeHandler;

        public:
            CProductHandler();
            CProductHandler(const SProductInfo& product_st);
            CProductHandler(const SProductInfo& product_st, const ExchangeHrPtr& parent);
            ~CProductHandler();

            // �ṹ(SProductInfo)��صĲ���
        public:
            // ����������������ID
            const PExchangeIDType getBelongExID() const;
            // ����Ʒ��ID
            const PProductIDType getProductID() const;
            // ��ȡƷ�ֵ�����
            std::string getProductName() const;
            // ��ȡƷ�ֵĴ���
            std::string getProductCode() const;
            // ��ǰʱ���Ƿ�ɽ���
            bool curCanTrade() const;
            // ָ��ʱ���Ƿ�ɽ���
            bool canTrade(const std::string& time) const;
            // ��ȡƷ�ֵ�Ĭ�Ͽ���������
            const Feest& getProductOpenFee() const;
            // ��ȡƷ�ֵ�Ĭ��ƽ��������
            const Feest& getProductCloseYestodayFee() const;
            // ��ȡƷ�ֵ�Ĭ��ƽ��������
            const Feest& getProductCloseTodayFee() const;
            // ��ȡƷ�ֵ�Ĭ�Ͻ��ױ�֤��
            const Feest& getProductMargin() const;
            // ��ȡƷ�ֵ�Ĭ�Ϻ�Լ����
            int getProductMultiple() const;
            // ��ȡƷ�ֵ�Ĭ����С�䶯��λ
            int getProductMinChUnit() const;

            // �Ͻ�����������
        protected:
            void setExchangeHandler(const ExchangeHrPtr& parent);
            void setBelongExID(ExchangeIDType belong_id);
            void setProductID(ProductIDType product_id);

            SProductPtr getProductStruct() const;
            void setProductStruct(SProductPtr pvp);

        public:
            void setProductName(const std::string& name);

            // Ʒ���к�Լ�Ĳ���
        public:
            // �Ƿ�Ϊ��Ʒ��;
            bool isEmpty();
            // ��ȡƷ���к�Լ������
            int getContractCount() const;

            // �첽
            // ����һ����Լ����
            // name: �½���Լ�����ƣ�����Ϊ��
            ContractHrPtr createContractHr(const ContractNameType name);

            // ��ȡָ�����(ID)�ĺ�Լ��������name: ��Լ������
            ContractHrPtr getContractHr(const ContractNameType name) const;
            ContractHrPtr getContractHrByID(const ContractIDType id) const;

            // �첽
            // ɾ��һ����Լ���󣻷���true, ɾ���ɹ�
            bool deleteContractHr(const ContractNameType name);
            bool deteteContractHrByID(ContractIDType did);

            // ��������
        public:
            //���������˻�����
            ExchangeHrPtr getParentExHandler()
            {
                return m_parent.lock();
            }

        protected:
            // ��Ʒ����Ϣ�����ݿ���ɾ��
            void remove(unsigned int db_ver);
            // �ӵ�ǰƷ�ֶ����Ƴ�һ���µ�Ʒ�ֶ���
            // ����ֵ�� �¸��Ƴɹ���Ʒ�ֶ���
            ProductHrPtr copy();

            void onAddContractHr(ContractHrPtr pvh);
            bool onDelContractHr(ContractHrPtr pvh);

            template<typename Tag, typename ParamType>
            ContractHrPtr getContractHr(const ParamType& param) const
            {
                readLock	rl(mtx_contract);

                auto& indexoftag = m_contracts.get<Tag>();
                auto fit = indexoftag.find(param);
                if (fit != indexoftag.end())
                    return *fit;

                return ContractHrPtr();
            }

        protected:
            // Ʒ���Ƿ��޸�
            bool isModified() const;

            // �����޸ı��λ
            void setCurPdModiFlag(bool flag = true);
            void setContractModiFlag(bool flag = true);
            // ��ȡ�޸ı��λ
            bool getCurPdModiFlag();
            bool getContractModiFlag();


        private:
            ///////////////////////////////////////////////
            struct ContractNameTag{};
            struct ContractCodeTag {};
            struct ContractIDTag{};
            typedef boost::multi_index::multi_index_container <
                ContractHrPtr,
                boost::multi_index::indexed_by<
                boost::multi_index::ordered_unique<boost::multi_index::tag<ContractNameTag>, boost::multi_index::global_fun<const ContractHrPtr&, const ContractNameType, get_contract_name> >,
                boost::multi_index::ordered_unique<boost::multi_index::tag<ContractCodeTag>, boost::multi_index::global_fun<const ContractHrPtr&, const ContractCodeType, get_contract_code> >,
                boost::multi_index::ordered_unique<boost::multi_index::tag<ContractIDTag>, boost::multi_index::global_fun<const ContractHrPtr&, const ContractIDType, get_contract_guid> >
                >
            > ContractSet;

            ContractSet         m_contracts;		// Ʒ��������Լ		
            mutable rwMutex     mtx_contract;

            SProductPtr         m_product_st_obj;	// �˻���Ӧ�����ݽṹ
            mutable rwMutex     m_mtx_sp;

            std::atomic<bool>   modified_cur_;		// ��ǰƷ�����޸�
            std::atomic<bool>   modified_contract_;	// ������Լ���޸�

            ExchangeHrWPtr m_parent;			// ����������������������ָ��
        };
    }	//! NPMgrCenter
}
#endif	// VARTYHANDLER_H

