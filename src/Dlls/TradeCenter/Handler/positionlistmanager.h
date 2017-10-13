/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      positionlistmanager.h
Author:			XuYC
Version:
Date:
Description:    提供持仓操作管理池, 统一持仓指针管理
*************************************************/

#include <boost\noncopyable.hpp>
#include <map>
#include <set>
#include <vector>
#include <mutex>

#include "utility/rwmutex.h"
#include "utility/instance_shared_from_this.h"
#include "../Application/trade_handler_declare.h"
#include "define/params_declare.h"
#include "define/struct_declare.h"

namespace AllTrade {
    namespace NPTradeCenter {

        // 持仓列表管理
        class PositionListManager
            : public CommonTools::instance_shared_from_this<PositionListManager>
            , public boost::noncopyable
        {
            // 持仓统计要素
            struct PositionKey
            {
                UserIDType      user_id_;
                ContractIDType  contract_id_;
                DirectType      direct_;

                PositionKey(const TradeHrPtr& trade_hr_ptr);
                PositionKey(const UserIDType user_id, const ContractIDType contract_id, DirectType direct);

                bool operator <(const PositionKey& rhs) const
                {
                    if (strcmp(user_id_, rhs.user_id_) < 0)
                        return true;

                    if (strcmp(user_id_, rhs.user_id_) == 0)
                    {
                        if (strcmp(contract_id_, rhs.contract_id_) < 0)
                            return true;

                        if (strcmp(contract_id_, rhs.contract_id_) == 0 && (int)direct_ < (int)rhs.direct_)
                            return true;
                    }

                    return false;
                }

                bool operator ==(const PositionKey& rhs) const
                {
                    return strcmp(user_id_, rhs.user_id_) == 0
                        && strcmp(contract_id_, rhs.contract_id_) == 0
                        && direct_ == rhs.direct_;
                }

            };

        public:
            PositionListManager();
            ~PositionListManager() {}

            // 新增成交消息,修改持仓信息,返回修改后的持仓指针
            PositionHrPtr changePosition(const TradeHrPtr& trade_hr_ptr);

            // 获取反向持仓指针
            const PositionHrPtr getReversePosition(const UserIDType user_id, const ContractIDType contract_id, DirectType direct) const;
            // 获取持仓指针
            const PositionHrPtr getPosition(const UserIDType user_id, const ContractIDType contract_id, DirectType direct) const;
            // 从队列中删除持仓
            void removePositionItem(const PositionHrPtr& pos_item);

            // 获取持仓
            std::vector<PositionHrPtr> getPositionHrsByContractIDs(const std::set<PContractIDType>& contract_ids) const;
            std::vector<PositionHrPtr> updatePositionQuoteByContractIDs(const std::map<PContractIDType, YDouble>& contract_id_last_quotes) const;
            std::vector<PositionHrPtr> getPositionHrsByUserID(const UserIDType user_id) const;

            // 获取创业板持仓
            std::vector<PositionHrPtr> getPositionHrsInSecondBoard(const UserIDType user_id) const;

            // 平指定用户所有持仓
            void closeAllYestodayPosition(CommodityTypeType commod_type, const UserIDType user_id) const;

        private:
            // 获取反向持仓指针
            const PositionHrPtr getReversePosition(PositionKey pos_key) const;

            // 根据成交获取持仓操作指针
            PositionHrPtr createPositionHr(const TradeHrPtr& trade_hr_ptr);

			// 融资持仓查询操作
			void handleGetMarginPosition();

        private:
            mutable rwMutex                         m_mtx_position;
            std::map<PositionKey, PositionHrPtr>    m_position_map;
        };

    }
}

