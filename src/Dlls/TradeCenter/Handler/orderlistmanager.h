/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      orderlistmanager.h
Author:			XuYC
Version:
Date:
Description:    提供委托操作管理池, 统一委托指针管理
                委托的生命周期即为交易周期,无需存储撤单委托/委托状态改变/成交信息
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
        // 用于多索引容器的全局函数
        const POrderStreamType get_order_stream(const OrderHrPtr& order_hr_ptr);
        const POrderRefType get_order_ref(const OrderHrPtr& order_hr_ptr);
        YDouble get_order_price(const OrderHrPtr& order_hr_ptr);
        const PDateTimeType get_order_createtime(const OrderHrPtr& order_hr_ptr);
        const PUserIDType get_order_user_id(const OrderHrPtr& order_hr_ptr);

        // 委托队列管理
        class OrderListManager
            : public CommonTools::instance_shared_from_this<OrderListManager>
            , public boost::noncopyable
        {
#pragma region 多索引
        private:
            // 按合约进行的多索引排序
            class OrderContractIndex
            {
            public:
                OrderContractIndex() {}
                ~OrderContractIndex() {}

                void addToList(const OrderHrPtr& order_ptr);
                void removefromList(const OrderHrPtr& order_ptr);

                // 根据OrderStream获取对应委托
                OrderHrPtr getOrderHrPtrByOrderStream(const OrderStreamType order_stream) const;
                // 根据OrderStream获取对应委托
                OrderHrPtr getOrderHrPtrByOrderRef(const OrderRefType order_ref) const;
                // 获取该合约下的指定方向委托队列,按价格排序
                std::vector<OrderHrPtr> getOrderHrPtrByDirect(DirectType direct) const;
                // 获取该合约下的所有委托队列,先按买卖方向排序,再按价格排序
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
                OrderContractSet        m_buy_orders;   // 买方向委托

                mutable rwMutex         mtx_sell_order;
                OrderContractSet        m_sell_orders;  // 卖方向委托
            };

            // 按合约进行的账户多索引排序
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
                // 用户id, 委托单数
                std::map<PUserIDType, int>      m_users;
            };

            // 按用户进行的多索引排序
            class OrderUserIndex
            {
            public:
                OrderUserIndex() {}
                ~OrderUserIndex() {}

                void addToList(const OrderHrPtr& order_ptr);
                void removefromList(const OrderHrPtr& order_ptr);

                // 根据OrderStream获取对应委托
                OrderHrPtr getOrderHrPtrByOrderStream(const OrderStreamType order_stream) const;
                // 获取该用户下的委托队列,按时间排序
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
            // 创建下单委托操作
            OrderHrPtr createOrderHr(const OrderInfoPtr& order_ptr, const UserIDType use_id, const NPMgrCenter::SOnlineAccountPtr& user_online);

            // 根据ContractID获取对应委托
            OrderHrPtr getOrderHrPtrByContractID(const ContractIDType contract_id, const OrderStreamType order_stream) const;
            // 根据ContractID与order_ref获取对应委托
            OrderHrPtr getOrderHrPtrByContractIDAndRef(const ContractIDType contract_id, const OrderRefType order_ref) const;
            // 根据UserID获取对应委托
            OrderHrPtr getOrderHrPtrByUserID(const UserIDType use_id, const OrderStreamType order_stream) const;

            // 根据合约ID获取所有对应委托
            std::vector<OrderHrPtr> getOrderHrListByContractID(const ContractIDType contract_id, DirectType direct) const;
            std::vector<OrderHrPtr> getOrderHrListByContractID(const ContractIDType contract_id) const;
            // 根据用户ID获取所有对应委托
            std::vector<OrderHrPtr> getOrderHrListByUserID(const UserIDType user_id) const;
            // 根据合约ID获取所有有该持仓的用户
            std::vector<PUserIDType> getUserListByContractID(const ContractIDType contract_id) const;

            // 根据用户ID撤销所有委托
            void closeAllOrders(CommodityTypeType commod_type, const UserIDType user_id) const;

        public:
            void addToList(const OrderHrPtr& order_ptr);
            void removefromList(const OrderHrPtr& order_ptr);

		private:
			// 获取融券委托信息
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

