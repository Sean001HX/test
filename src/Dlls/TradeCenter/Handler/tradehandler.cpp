#include <assert.h>
#include "tradehandler.h"
#include "define/struct_base.h"
#include "define/protocol_error.h"
#include "define/struct_extern.h"
#include "orderhandler.h"
#include "orderlistmanager.h"
#include "utility/utility_fun.h"
#include "include/OperationManager/OperationManager.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "TradeHandler");

namespace AllTrade {
    namespace NPTradeCenter {
        TradeBaseHandler::TradeBaseHandler(const TradeInfoPtr& trade_ptr, const UserIDType use_id)
            : m_trade_ptr(trade_ptr)
        {
            strncpy_s(m_user_id, use_id, sizeof(m_user_id) - 1);
        }

        const PTradeIDType TradeBaseHandler::getTradeID() const
        {
            return m_trade_ptr->trade_id_;
        }

        const PPositionIDType TradeBaseHandler::getPositionID() const
        {
            return m_trade_ptr->position_id_;
        }

        void TradeBaseHandler::setPositionID(const PositionIDType positionID)
        {
            strncpy_s(m_trade_ptr->position_id_, positionID, sizeof(m_trade_ptr->position_id_));
            ErrorCodeType err = serialize();
            assert(err == Err_Succeed);
        }

        const POrderIDType TradeBaseHandler::getOrderStream() const
        {
            return m_trade_ptr->order_stream_;
        }

        const AllTrade::PSystemIDType TradeBaseHandler::getOrderSystemID() const
        {
            return m_trade_ptr->system_order_id_;
        }

        const PUserIDType TradeBaseHandler::getUserID() const
        {
            return m_user_id;
        }

        const PExchangeIDType TradeBaseHandler::getExchangeID() const
        {
            return m_trade_ptr->exchange_id_;
        }

        const PContractIDType TradeBaseHandler::getContractID() const
        {
            return m_trade_ptr->contract_id_;
        }

        const PDateTimeType TradeBaseHandler::getGenerateDatetime() const
        {
            return m_trade_ptr->generate_datetime_;
        }

        int TradeBaseHandler::getTradeVol() const
        {
            return m_trade_ptr->volume_;
        }

        DirectType TradeBaseHandler::getDirect() const
        {
            return m_trade_ptr->direct_type_;
        }

        YDouble TradeBaseHandler::getCurrencyRate() const
        {
            return m_trade_ptr->currency_rate_;
        }

        const PCurrencyIDType TradeBaseHandler::getCurrencyID() const
        {
            return m_trade_ptr->currency_id_;
        }

        YDouble TradeBaseHandler::getTradePrice() const
        {
            return m_trade_ptr->trade_price_;
        }

        YDouble TradeBaseHandler::getCloseProfit() const
        {
            return m_trade_ptr->close_profit_;
        }

        AllTrade::OperatorTradeType TradeBaseHandler::getOperatorType() const
        {
            return m_trade_ptr->op_type_;
        }

//         YDouble TradeBaseHandler::getPositionCost() const
//         {
//             return m_trade_ptr->position_cost_;
//         }

//         YDouble TradeBaseHandler::getPositionAvePrice() const
//         {
//             return m_trade_ptr->position_ave_price_;
//         }

        bool TradeBaseHandler::isValid() const
        {
            return true;
        }

        AllTrade::CommodityTypeType TradeBaseHandler::getCommodityType() const
        {
            return m_trade_ptr->commodity_type_;
        }

        AllTrade::ErrorCodeType TradeBaseHandler::serialize()
        {
            if (!OperationManager::COperationManager::instance()->addTradeRecord(m_trade_ptr, m_user_id))
                return Err_Database;

            return Err_Succeed;
        }

        //////////////////////////////////////////////////////////////////////////
        StockTradeHandler::StockTradeHandler(const StockTradePtr& stock_trade_ptr, const UserIDType use_id)
            : TradeBaseHandler(stock_trade_ptr, use_id)
        {

        }

        AllTrade::NPTradeCenter::StockTradeInfo StockTradeHandler::getTradeInfo() const
        {
            readLock lock(m_mtx);
            StockTradePtr tmp = std::dynamic_pointer_cast<StockTradeInfo>(m_trade_ptr);
            assert(tmp);
            return *(tmp.get());
        }

        AllTrade::NPTradeCenter::TradeInfoPtr StockTradeHandler::getTradeInfoCopy() const
        {
            readLock lock(m_mtx);
            return std::make_shared<StockTradeInfo>(*std::dynamic_pointer_cast<StockTradeInfo>(m_trade_ptr).get());
        }

        YDouble StockTradeHandler::getPositionCost() const
        {
            readLock lock(m_mtx);
            StockTradePtr ptr = std::dynamic_pointer_cast<StockTradeInfo>(m_trade_ptr);
            return UtilityFun::Round(ptr->trade_fee_ + ptr->stamp_fee_ + ptr->transfer_fee_ + ptr->infomatch_fee_ + ptr->trade_price_ * ptr->volume_, 0.00001);
        }

        YDouble StockTradeHandler::getTradeCommissionFee() const
        {
            readLock lock(m_mtx);
            StockTradePtr ptr = std::dynamic_pointer_cast<StockTradeInfo>(m_trade_ptr);
            return ptr->trade_fee_;
        }

        YDouble StockTradeHandler::getStampFee() const
        {
            readLock lock(m_mtx);
            StockTradePtr ptr = std::dynamic_pointer_cast<StockTradeInfo>(m_trade_ptr);
            return ptr->stamp_fee_;
        }

        YDouble StockTradeHandler::getTransferFee() const
        {
            readLock lock(m_mtx);
            StockTradePtr ptr = std::dynamic_pointer_cast<StockTradeInfo>(m_trade_ptr);
            return ptr->transfer_fee_;
        }

        YDouble StockTradeHandler::getInfoMatchFee() const
        {
            readLock lock(m_mtx);
            StockTradePtr ptr = std::dynamic_pointer_cast<StockTradeInfo>(m_trade_ptr);
            return ptr->infomatch_fee_;
        }

        //////////////////////////////////////////////////////////////////////////
        ForeignFutureTradeHandler::ForeignFutureTradeHandler(const ForeignFutureTradePtr& ffuture_trade_ptr, const UserIDType use_id)
            : TradeBaseHandler(ffuture_trade_ptr, use_id)
        {

        }

        const PProductIDType ForeignFutureTradeHandler::getProductID() const
        {
            ForeignFutureTradePtr ffuture_trade_ptr = std::dynamic_pointer_cast<ForeignFutureTradeInfo>(m_trade_ptr);
            assert(ffuture_trade_ptr);
            return ffuture_trade_ptr->product_id_;
        }

        AllTrade::NPTradeCenter::ForeignFutureTradeInfo ForeignFutureTradeHandler::getTradeInfo() const
        {
            readLock lock(m_mtx);
            ForeignFutureTradePtr tmp = std::dynamic_pointer_cast<ForeignFutureTradeInfo>(m_trade_ptr);
            assert(tmp);
            return *(tmp.get());
        }

        AllTrade::NPTradeCenter::TradeInfoPtr ForeignFutureTradeHandler::getTradeInfoCopy() const
        {
            readLock lock(m_mtx);
            return std::make_shared<ForeignFutureTradeInfo>(*std::dynamic_pointer_cast<ForeignFutureTradeInfo>(m_trade_ptr).get());
        }

        //////////////////////////////////////////////////////////////////////////
        ChinaFutureTradeHandler::ChinaFutureTradeHandler(const ChinaFutureTradePtr& cfuture_trade_ptr, const UserIDType use_id)
            : TradeBaseHandler(cfuture_trade_ptr, use_id)
        {

        }

        const PProductIDType ChinaFutureTradeHandler::getProductID() const
        {
            ChinaFutureTradePtr cfuture_trade_ptr = std::dynamic_pointer_cast<ChinaFutureTradeInfo>(m_trade_ptr);
            assert(cfuture_trade_ptr);
            return cfuture_trade_ptr->product_id_;
        }

        const OffsetType ChinaFutureTradeHandler::getOffsetType() const
        {
            ChinaFutureTradePtr cfuture_trade_ptr = std::dynamic_pointer_cast<ChinaFutureTradeInfo>(m_trade_ptr);
            assert(cfuture_trade_ptr);
            return cfuture_trade_ptr->offset_type_;
        }

        AllTrade::NPTradeCenter::ChinaFutureTradeInfo ChinaFutureTradeHandler::getTradeInfo() const
        {
            readLock lock(m_mtx);
            ChinaFutureTradePtr tmp = std::dynamic_pointer_cast<ChinaFutureTradeInfo>(m_trade_ptr);
            assert(tmp);
            return *(tmp.get());
        }

        AllTrade::NPTradeCenter::TradeInfoPtr ChinaFutureTradeHandler::getTradeInfoCopy() const
        {
            readLock lock(m_mtx);
            return std::make_shared<ChinaFutureTradeInfo>(*std::dynamic_pointer_cast<ChinaFutureTradeInfo>(m_trade_ptr).get());
        }


		//////////////////////////////////////////////////////////////////////////
		MarginTradeHandler::MarginTradeHandler(const MarginTradeInfoPtr& margin_trade_ptr, const UserIDType use_id)
			: TradeBaseHandler(margin_trade_ptr, use_id)
		{

		}

		AllTrade::NPTradeCenter::MarginTradeInfo MarginTradeHandler::getTradeInfo() const
		{
			readLock lock(m_mtx);
			MarginTradeInfoPtr tmp = std::dynamic_pointer_cast<MarginTradeInfo>(m_trade_ptr);
			assert(tmp);
			return *(tmp.get());
		}

		AllTrade::NPTradeCenter::TradeInfoPtr MarginTradeHandler::getTradeInfoCopy() const
		{
			readLock lock(m_mtx);
			return std::make_shared<MarginTradeInfo>(*std::dynamic_pointer_cast<MarginTradeInfo>(m_trade_ptr).get());
		}

	}
}
