/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      stockservermgr.h
Author:			XuYC
Version:
Date:
Description:    提供股票交易操作接口
*************************************************/
#ifndef __STOCK_TRADE_MGR_H__
#define __STOCK_TRADE_MGR_H__

#include "utility/instance_shared_from_this.h"
#include "servermgrbase.h"
#include "utility/rwmutex.h"

namespace AllTrade{
    namespace NPTradeCenter {
        class StockServerMgr
            : public CommonTools::instance_shared_from_this<StockServerMgr>
            , public ServerMgrBase
        {
        public:
            StockServerMgr();
            ~StockServerMgr();

            void updateQuote(const QuoteInfoPtr& quote_ptr, const NPMgrCenter::SExchangeCPtr& exchange_ptr, const NPMgrCenter::SContractCPtr& contract_ptr) override;

            void dealTradeMsg(const TradeInfoPtr& trade_info_ptr, const UserIDType use_id) override;

        private:
            // 处理机构佣金
            void dealCommissionParentMoney(const StockTradeHrPtr& stock_trade_ptr, bool isXSHG);
            AllTrade::NPMgrCenter::SAgencyMoneyDetailInfoPtr createAgencyMoneyDetailInfo(const UserIDType user_id, const UserIDType source_user_id, Agency_Money_Change_Type type, YDouble money, YDouble commission_rate, const RemarkTextType remark);

            // 处理机构分成
            void dealProfitParentMoney(const PositionHrPtr& pos_item, const StockTradeHrPtr& stock_trade_ptr);

//         private:
//             rwMutex     m_mtx;// 防止持仓成本未来得及修改就计算分成数据
        };
    }
}
#endif