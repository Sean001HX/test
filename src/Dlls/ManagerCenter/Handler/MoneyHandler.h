#ifndef MONEYHANDLER_H
#define MONEYHANDLER_H

#include <mutex>
#include <atomic>
#include <boost\noncopyable.hpp>

#include "define/struct_base.h"
#include "define/struct_declare.h"
#include "define/params_declare.h"
#include "../Application/user_class_declare.h"
#include "utility/rwmutex.h"

namespace AllTrade {
    namespace NPMgrCenter {

        class CMoneyHandler
            : public std::enable_shared_from_this<CMoneyHandler>
            , public boost::noncopyable
        {
            friend class CAccountBaseHandler;

        public:
            CMoneyHandler();
            CMoneyHandler(const SMoneyInfoPtr& money_st);
            CMoneyHandler(const AccountHrPtr& parent);
            ~CMoneyHandler();

        public:
            // 持仓总成本(累计)
            YDouble getPositionCost() const;
            // 交易总手续费(累计,含过户,印花...)
            YDouble getTradingFee() const;
            // 可提取金额
            YDouble getCanExtract() const;
            // 提交委托时的冻结资金
            YDouble getOrderFreeze() const;
            // 用户保证金
            YDouble getDeposit() const;
            // 配资/优先资金
            YDouble getPriorityFund() const;
            // 获取总资金
            YDouble getTotal() const;
            // 获取可用资金
            YDouble getCanUse() const;

        public:
            // 持仓成本变化
            ErrorCodeType changePositionCost(YDouble ave_money, int vol, DirectType direct);

            // 资金改变
            // MC_Trade_Open时,money为冻结资金-成交价
            ErrorCodeType moneyChange(Money_Change_Type money_change, YDouble money, const RemarkTextType remark);

            // 其他操作
        public:
            SMoneyInfoPtr getMoneyPtrCopy() const{
                readLock lock(m_mtx_sp);
                return std::make_shared<SMoneyInfo>(*m_money_st_obj.get());
            }

            //返回所属账户对象
            AccountHrPtr getParentAccHandler() const
            {
                return m_parent.lock();
            }

        protected:
            void setParent(AccountHrPtr parent);

        private:
            ErrorCodeType serializeDetail(const SMoneyDetailInfoPtr& money_change);
            ErrorCodeType serialize();
            ErrorCodeType unserialize();

        private:
            SMoneyInfoPtr       m_money_st_obj;	    // 资金对应的数据结构
            mutable rwMutex     m_mtx_sp;

            AccountHrWPtr       m_parent;			// 所属交易所操作对象（弱）指针
        };
    }	//! NPMgrCenter
}
#endif	// VARTYHANDLER_H

