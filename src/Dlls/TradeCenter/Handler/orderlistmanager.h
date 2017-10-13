/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      orderlistmanager.h
Author:			XuYC
Version:
Date:
Description:    �ṩί�в��������, ͳһί��ָ�����
                ί�е��������ڼ�Ϊ��������,����洢����ί��/ί��״̬�ı�/�ɽ���Ϣ
*************************************************/

#include <boost\noncopyable.hpp>
#include <vector>
#include <map>
#include <mutex>
#include <atomic>
#include <boost\multi_index_container.hpp>
#include <boost\multi_index\mem_fun.hpp>
#include <boost\multi_index\ordered_index.hpp>
#include <boost\multi_index\global_fun.hpp>

#include "utility/rwmutex.h"
#include "utility/instance_shared_from_this.h"
#include "../Application/trade_handler_declare.h"
#include "define/params_declare.h"
#include "define/struct_declare.h"

namespace AllTrade {
    namespace NPTradeCenter {

        //////////////////////////////////////////////////////////////////////////
        // ���ڶ�����������ȫ�ֺ���
        const POrderStreamType get_order_stream(const OrderHrPtr& order_hr_ptr);
        const POrderRefType get_order_ref(const OrderHrPtr& order_hr_ptr);
        YDouble get_order_price(const OrderHrPtr& order_hr_ptr);
        const PDateTimeType get_order_createtime(const OrderHrPtr& order_hr_ptr);
        const PUserIDType get_order_user_id(const OrderHrPtr& order_hr_ptr);

        // ί�ж��й���
        class OrderListManager
            : public CommonTools::instance_shared_from_this<OrderListManager>
            , public boost::noncopyable
        {
#pragma region ������
        private:
            // ����Լ���еĶ���������
            class OrderContractIndex
            {
            public:
                OrderContractIndex() {}
                ~OrderContractIndex() {}

                void addToList(const OrderHrPtr& order_ptr);
                void removefromList(const OrderHrPtr& order_ptr);

                // ����OrderStream��ȡ��Ӧί��
                OrderHrPtr getOrderHrPtrByOrderStream(const OrderStreamType order_stream) const;
                // ����OrderStream��ȡ��Ӧί��
                OrderHrPtr getOrderHrPtrByOrderRef(const OrderRefType order_ref) const;
                // ��ȡ�ú�Լ�µ�ָ������ί�ж���,���۸�����
                std::vector<OrderHrPtr> getOrderHrPtrByDirect(DirectType direct) const;
                // ��ȡ�ú�Լ�µ�����ί�ж���,�Ȱ�������������,�ٰ��۸�����
                std::vector<OrderHrPtr> getOrderHrPtrByDirect() const;

            private:
                template<typename Tag, typename ParamType>
                OrderHrPtr getBuyOrderHrPtr(const ParamType param) const
                {
                    readLock    rl(mtx_buy_order);

                    auto& indexoftag = m_buy_orders.get<Tag>();
                    auto fit = indexoftag.find(param);
                    if (fit != indexoftag.end())
                        return *fit;

                    return OrderHrPtr();
                }

                template<typename Tag, typename ParamType>
                OrderHrPtr getSellOrderHrPtr(const ParamType param) const
                {
                    readLock    rl(mtx_sell_order);

                    auto& indexoftag = m_sell_orders.get<Tag>();
                    auto fit = indexoftag.find(param);
                    if (fit != indexoftag.end())
                        return *fit;

                    return OrderHrPtr();
                }

            private:
                ///////////////////////////////////////////////
                struct OrderStreamTag {};
                struct OrderRefTag {};
                struct OrdePriceTag {};
                typedef boost::multi_index::multi_index_container <
                    OrderHrPtr,
                    boost::multi_index::indexed_by<
                    boost::multi_index::ordered_unique<boost::multi_index::tag<OrderStreamTag>, boost::multi_index::global_fun<const OrderHrPtr&, const POrderStreamType, get_order_stream> >,
                    boost::multi_index::ordered_unique<boost::multi_index::tag<OrderRefTag>, boost::multi_index::global_fun<const OrderHrPtr&, const POrderRefType, get_order_ref> >,
                    boost::multi_index::ordered_non_unique<boost::multi_index::tag<OrdePriceTag>, boost::multi_index::global_fun<const OrderHrPtr&, YDouble, get_order_price> >
                    >
                > OrderContractSet;

            private:
                mutable rwMutex         mtx_buy_order;
                OrderContractSet        m_buy_orders;   // ����ί��

                mutable rwMutex         mtx_sell_order;
                OrderContractSet        m_sell_orders;  // ������ί��
            };

            // ����Լ���е��˻�����������
            class OrderContractUserIndex
            {
            public:
                OrderContractUserIndex() {}
                ~OrderContractUserIndex() {}

                void addToList(const OrderHrPtr& order_ptr);
                void removefromList(const OrderHrPtr& order_ptr);

                std::vector<PUserIDType> getAllUsers() const;

            private:
                mutable rwMutex                 mtx_user_mtx;
                // �û�id, ί�е���
                std::map<PUserIDType, int>      m_users;
            };

            // ���û����еĶ���������
            class OrderUserIndex
            {
            public:
                OrderUserIndex() {}
                ~OrderUserIndex() {}

                void addToList(const OrderHrPtr& order_ptr);
                void removefromList(const OrderHrPtr& order_ptr);

                // ����OrderStream��ȡ��Ӧί��
                OrderHrPtr getOrderHrPtrByOrderStream(const OrderStreamType order_stream) const;
                // ��ȡ���û��µ�ί�ж���,��ʱ������
                std::vector<OrderHrPtr> getOrderHrPtrByCreateTime() const;

            private:
                template<typename Tag, typename ParamType>
                OrderHrPtr getOrderHrPtr(const ParamType param) const
                {
                    readLock    rl(mtx_order);

                    auto& indexoftag = m_orders.get<Tag>();
                    auto fit = indexoftag.find(param);
                    if (fit != indexoftag.end())
                        return *fit;

                    return OrderHrPtr();
                }

            private:
                ///////////////////////////////////////////////
                struct OrderStreamTag {};
                struct OrderCreateTimeTag {};
                typedef boost::multi_index::multi_index_container <
                    OrderHrPtr,
                    boost::multi_index::indexed_by<
                    boost::multi_index::ordered_unique<boost::multi_index::tag<OrderStreamTag>, boost::multi_index::global_fun<const OrderHrPtr&, const POrderStreamType, get_order_stream> >,
                    boost::multi_index::ordered_non_unique<boost::multi_index::tag<OrderCreateTimeTag>, boost::multi_index::global_fun<const OrderHrPtr&, const PDateTimeType, get_order_createtime> >
                    >
                > OrderUserSet;

            private:
                mutable rwMutex         mtx_order;
                OrderUserSet            m_orders;
            };
#pragma endregion

        public:
            OrderListManager();
            ~OrderListManager();

        public:
            // �����µ�ί�в���
            OrderHrPtr createOrderHr(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online);

            // ����ContractID��ȡ��Ӧί��
            OrderHrPtr getOrderHrPtrByContractID(const ContractIDType contract_id, const OrderStreamType order_stream) const;
            // ����ContractID��order_ref��ȡ��Ӧί��
            OrderHrPtr getOrderHrPtrByContractIDAndRef(const ContractIDType contract_id, const OrderRefType order_ref) const;
            // ����UserID��ȡ��Ӧί��
            OrderHrPtr getOrderHrPtrByUserID(const UserIDType use_id, const OrderStreamType order_stream) const;

            // ���ݺ�ԼID��ȡ���ж�Ӧί��
            std::vector<OrderHrPtr> getOrderHrListByContractID(const ContractIDType contract_id, DirectType direct) const;
            std::vector<OrderHrPtr> getOrderHrListByContractID(const ContractIDType contract_id) const;
            // �����û�ID��ȡ���ж�Ӧί��
            std::vector<OrderHrPtr> getOrderHrListByUserID(const UserIDType user_id) const;
            // ���ݺ�ԼID��ȡ�����иóֲֵ��û�
            std::vector<PUserIDType> getUserListByContractID(const ContractIDType contract_id) const;

            // �����û�ID��������ί��
            void closeAllOrders(CommodityTypeType commod_type, const UserIDType user_id) const;

        public:
            void addToList(const OrderHrPtr& order_ptr);
            void removefromList(const OrderHrPtr& order_ptr);

		private:
			// ��ȡ��ȯί����Ϣ
			void getMarginOrderInfo();

        private:
            std::map<PContractIDType, OrderContractIndex>       m_contract_orders;
            std::map<PUserIDType, OrderUserIndex>               m_user_orders;
            std::map<PContractIDType, OrderContractUserIndex>   m_order_users;
            mutable rwMutex                                     m_mtx_order;

        private:
            enum { E_OrderList_Cur_Ver = 1, };

        };

    }
}

