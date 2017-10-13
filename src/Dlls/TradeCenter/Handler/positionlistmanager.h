/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      positionlistmanager.h
Author:			XuYC
Version:
Date:
Description:    �ṩ�ֲֲ��������, ͳһ�ֲ�ָ�����
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

        // �ֲ��б����
        class PositionListManager
            : public CommonTools::instance_shared_from_this<PositionListManager>
            , public boost::noncopyable
        {
            // �ֲ�ͳ��Ҫ��
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

            // �����ɽ���Ϣ,�޸ĳֲ���Ϣ,�����޸ĺ�ĳֲ�ָ��
            PositionHrPtr changePosition(const TradeHrPtr& trade_hr_ptr);

            // ��ȡ����ֲ�ָ��
            const PositionHrPtr getReversePosition(const UserIDType user_id, const ContractIDType contract_id, DirectType direct) const;
            // ��ȡ�ֲ�ָ��
            const PositionHrPtr getPosition(const UserIDType user_id, const ContractIDType contract_id, DirectType direct) const;
            // �Ӷ�����ɾ���ֲ�
            void removePositionItem(const PositionHrPtr& pos_item);

            // ��ȡ�ֲ�
            std::vector<PositionHrPtr> getPositionHrsByContractIDs(const std::set<PContractIDType>& contract_ids) const;
            std::vector<PositionHrPtr> updatePositionQuoteByContractIDs(const std::map<PContractIDType, YDouble>& contract_id_last_quotes) const;
            std::vector<PositionHrPtr> getPositionHrsByUserID(const UserIDType user_id) const;

            // ��ȡ��ҵ��ֲ�
            std::vector<PositionHrPtr> getPositionHrsInSecondBoard(const UserIDType user_id) const;

            // ƽָ���û����гֲ�
            void closeAllYestodayPosition(CommodityTypeType commod_type, const UserIDType user_id) const;

        private:
            // ��ȡ����ֲ�ָ��
            const PositionHrPtr getReversePosition(PositionKey pos_key) const;

            // ���ݳɽ���ȡ�ֲֲ���ָ��
            PositionHrPtr createPositionHr(const TradeHrPtr& trade_hr_ptr);

			// ���ʳֲֲ�ѯ����
			void handleGetMarginPosition();

        private:
            mutable rwMutex                         m_mtx_position;
            std::map<PositionKey, PositionHrPtr>    m_position_map;
        };

    }
}

