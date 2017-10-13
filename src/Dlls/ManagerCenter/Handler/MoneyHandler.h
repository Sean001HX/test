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
            // �ֲ��ܳɱ�(�ۼ�)
            YDouble getPositionCost() const;
            // ������������(�ۼ�,������,ӡ��...)
            YDouble getTradingFee() const;
            // ����ȡ���
            YDouble getCanExtract() const;
            // �ύί��ʱ�Ķ����ʽ�
            YDouble getOrderFreeze() const;
            // �û���֤��
            YDouble getDeposit() const;
            // ����/�����ʽ�
            YDouble getPriorityFund() const;
            // ��ȡ���ʽ�
            YDouble getTotal() const;
            // ��ȡ�����ʽ�
            YDouble getCanUse() const;

        public:
            // �ֲֳɱ��仯
            ErrorCodeType changePositionCost(YDouble ave_money, int vol, DirectType direct);

            // �ʽ�ı�
            // MC_Trade_Openʱ,moneyΪ�����ʽ�-�ɽ���
            ErrorCodeType moneyChange(Money_Change_Type money_change, YDouble money, const RemarkTextType remark);

            // ��������
        public:
            SMoneyInfoPtr getMoneyPtrCopy() const{
                readLock lock(m_mtx_sp);
                return std::make_shared<SMoneyInfo>(*m_money_st_obj.get());
            }

            //���������˻�����
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
            SMoneyInfoPtr       m_money_st_obj;	    // �ʽ��Ӧ�����ݽṹ
            mutable rwMutex     m_mtx_sp;

            AccountHrWPtr       m_parent;			// ����������������������ָ��
        };
    }	//! NPMgrCenter
}
#endif	// VARTYHANDLER_H

