#include <assert.h>
#include "TradeFeeManager.h"
#include "define/struct_extern.h"
#include "define/protocol_error.h"
#include "include/OperationManager/OperationManager.h"
#include "utility/utility_fun.h"

namespace AllTrade{
    namespace NPTradeCenter {
        TradeFeeManager::TradeFeeManager()
            : m_is_modify(true)
        {
            if (unserialize() != Err_Succeed)
            {
                m_TradeFee = std::make_shared<TradeFee>();
            }
        }

        TradeFeeManager::~TradeFeeManager()
        {

        }

        YDouble TradeFeeManager::getOpenFee(YDouble money, int vol, bool isXSHG)
        {
            if (isXSHG)
                return getTradeCommissionFee(money) + getTransferFee(vol) + getInfoMatchFee(money);
            else
                return getTradeCommissionFee(money) + getInfoMatchFee(money);
        }

        YDouble TradeFeeManager::getSpecifyOpenFee(YDouble comm_rate, YDouble money, int vol, bool isXSHG)
        {
            if (isXSHG)
                return getSpecifyTradeCommissionFee(comm_rate, money) + getTransferFee(vol) + getInfoMatchFee(money);
            else
                return getSpecifyTradeCommissionFee(comm_rate, money) + getInfoMatchFee(money);
        }

        YDouble TradeFeeManager::getCloseFee(YDouble money, int vol, bool isXSHG)
        {
            if (isXSHG)
                return getTradeCommissionFee(money) + getTransferFee(vol) + getInfoMatchFee(money) + getStampDutyFee(money);
            else
                return getTradeCommissionFee(money) + getInfoMatchFee(money) + getStampDutyFee(money);
        }

        YDouble TradeFeeManager::getSpecifyCloseFee(YDouble comm_rate, YDouble money, int vol, bool isXSHG)
        {
            if (isXSHG)
                return getSpecifyTradeCommissionFee(comm_rate, money) + getTransferFee(vol) + getInfoMatchFee(money) + getStampDutyFee(money);
            else
                return getSpecifyTradeCommissionFee(comm_rate, money) + getInfoMatchFee(money) + getStampDutyFee(money);
        }

        YDouble TradeFeeManager::getSpecifyTradeCommissionFee(YDouble comm_rate, YDouble money) const
        {
            readLock lock(m_mtx);
            YDouble rslt = comm_rate * 0.001 * money;
            if (rslt < m_TradeFee->min_trade_commission_)
                return m_TradeFee->min_trade_commission_;

            return UtilityFun::Round(rslt, 0.00001);
        }

        YDouble TradeFeeManager::getTradeCommissionFee(YDouble money) const
        {
            readLock lock(m_mtx);
            YDouble rslt = m_TradeFee->trade_commission_ * 0.001 * money;
            if (rslt < m_TradeFee->min_trade_commission_)
                return m_TradeFee->min_trade_commission_;

            return UtilityFun::Round(rslt, 0.00001);
        }

        YDouble TradeFeeManager::getTradeCommissionValue() const
        {
            readLock lock(m_mtx);
            return m_TradeFee->trade_commission_;
        }

        void TradeFeeManager::setTradeCommissionValue(YDouble money)
        {
            writeLock lock(m_mtx);
            m_TradeFee->trade_commission_ = money;
            m_is_modify = true;
        }

        YDouble TradeFeeManager::getMinTradeCommissionValue() const
        {
            readLock lock(m_mtx);
            return m_TradeFee->min_trade_commission_;
        }

        void TradeFeeManager::setMinTradeCommissionValue(YDouble money)
        {
            writeLock lock(m_mtx);
            m_TradeFee->min_trade_commission_ = money;
            m_is_modify = true;
        }

        YDouble TradeFeeManager::getStampDutyFee(YDouble money) const
        {
            readLock lock(m_mtx);
            return UtilityFun::Round(m_TradeFee->stamp_duty_ * 0.001 * money, 0.00001);
        }

        YDouble TradeFeeManager::getStampDutyValue() const
        {
            readLock lock(m_mtx);
            return m_TradeFee->stamp_duty_;
        }

        void TradeFeeManager::setStampDutyValue(YDouble money)
        {
            writeLock lock(m_mtx);
            m_TradeFee->stamp_duty_ = money;
            m_is_modify = true;
        }

        YDouble TradeFeeManager::getTransferFee(int vol) const
        {
            if (vol == 0)
                return 0.0;

            if (vol / 1000 == 0)
                vol = 1000;

            readLock lock(m_mtx);
            return m_TradeFee->transfer_ * 0.001 * vol;
        }

        YDouble TradeFeeManager::getTransferValue() const
        {
            readLock lock(m_mtx);
            return m_TradeFee->transfer_;
        }

        void TradeFeeManager::setTransferValue(YDouble money)
        {
            writeLock lock(m_mtx);
            m_TradeFee->transfer_ = money;
            m_is_modify = true;
        }

        YDouble TradeFeeManager::getInfoMatchFee(YDouble money) const
        {
            readLock lock(m_mtx);
            return UtilityFun::Round(m_TradeFee->info_match_ * 0.001 * money, 0.00001);
        }

        YDouble TradeFeeManager::getInfoMatchValue() const
        {
            readLock lock(m_mtx);
            return m_TradeFee->info_match_;
        }

        void TradeFeeManager::setInfoMatchValue(YDouble money)
        {
            writeLock lock(m_mtx);
            m_TradeFee->info_match_ = money;
            m_is_modify = true;
        }

        YDouble TradeFeeManager::getProfitRate() const
        {
            readLock lock(m_mtx);
            return m_TradeFee->user_profit_rate_ * 0.001;
        }

        YDouble TradeFeeManager::getProfitValue() const
        {
            readLock lock(m_mtx);
            return m_TradeFee->user_profit_rate_;
        }

        void TradeFeeManager::setProfitRate(YDouble rate)
        {
            writeLock lock(m_mtx);
            m_TradeFee->user_profit_rate_ = rate;
            m_is_modify = true;
        }

        AllTrade::NPTradeCenter::TradeFeePtr TradeFeeManager::getFeeSetPtrCopy() const
        {
            readLock lock(m_mtx);
            return std::make_shared<TradeFee>(*m_TradeFee.get());
        }

        AllTrade::ErrorCodeType TradeFeeManager::setFeeSetPtr(const AllTrade::NPTradeCenter::TradeFeePtr& ptr)
        {
            {
                writeLock lock(m_mtx);
                m_TradeFee = std::make_shared<TradeFee>(*ptr.get());
                m_is_modify = true;
            }
            return serialize();
        }

        AllTrade::ErrorCodeType TradeFeeManager::serialize()
        {
            writeLock lock(m_mtx);
            if (!m_is_modify)
                return Err_Succeed;

            m_is_modify = false;
            if (OperationManager::COperationManager::instance()->updateTradeFee(m_TradeFee))
                return Err_Succeed;

            return Err_Database;
        }

        AllTrade::ErrorCodeType TradeFeeManager::unserialize()
        {
            writeLock lock(m_mtx);

            if (!OperationManager::COperationManager::instance()->getTradeFee(m_TradeFee))
                return Err_Database;

            m_is_modify = false;
            return Err_Succeed;
        }

    }
}