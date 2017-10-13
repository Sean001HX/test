/*
* 为降低DLL与上层软件之间的耦合度以及DLL中各个子系统之间的耦合度，模块中各部分之间的交互均采用"Command"模式。
* 定义任务调度命令接口类及具体类。
*/

#ifndef  QNAC_COMMAND_H_
#define  QNAC_COMMAND_H_

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
# pragma once
#endif

#include <boost/shared_ptr.hpp>
#include "ThisPtrHolder.h"
#include "exception.h"

namespace CommonTools
{
	//////////////////////////////////////////////////////////////////////////
	class ICommandBase;
	typedef boost::shared_ptr<ICommandBase>	CommandPtr;

	class ICommandBase
	{
	public:
		virtual ~ICommandBase() {}

		virtual void execute(void) = 0;
		virtual void lockSelf(CommandPtr cp) = 0;
		virtual void unlockSelf() = 0;
		virtual CommandPtr getCommandThisPtr() = 0;
	};

	class MemFunHandlerBase
	{
	public:
		virtual ~MemFunHandlerBase() {}
		virtual void execute(void) = 0;
	};

	template<class ObjPtr, typename FunPtr>
	class MemFunHandler : public MemFunHandlerBase
	{
	public:
		MemFunHandler(ObjPtr op, FunPtr fp) : m_pObj(op), m_pFun(fp) {}

		~MemFunHandler() {}

	public:
		void execute(void) { (m_pObj.get()->*m_pFun)(); }

	private:
		ObjPtr	m_pObj;
		FunPtr	m_pFun;
	};

	template<class ObjPtr, typename FunPtr, typename ParamType>
	class MemFunHandler1 : public MemFunHandlerBase
	{
	public:
		MemFunHandler1(ObjPtr op, FunPtr fp, ParamType pt) : m_pObj(op), m_pFun(fp), m_Param(pt) {}

		~MemFunHandler1() {}

	public:
		void execute(void) { (m_pObj.get()->*m_pFun)(m_Param); }

	private:
		ObjPtr		m_pObj;
		FunPtr		m_pFun;
		typename std::remove_reference<ParamType>::type	m_Param;
	};

	template<class ObjPtr, typename FunPtr, typename ParamType, typename ParamType2>
	class MemFunHandler2 : public MemFunHandlerBase
	{
	public:
		MemFunHandler2(ObjPtr op, FunPtr fp, ParamType pt, ParamType2 pt2) 
			: m_pObj(op), m_pFun(fp), m_Param(pt), m_Param2(pt2)
		{
		}

		~MemFunHandler2() {}

	public:
		void execute(void) { (m_pObj.get()->*m_pFun)(m_Param, m_Param2); }

	private:
		ObjPtr		m_pObj;
		FunPtr		m_pFun;
		typename std::remove_reference<ParamType>::type		m_Param;
		typename std::remove_reference<ParamType2>::type	m_Param2;
	};

	template<class ObjPtr, typename FunPtr, typename ParamType, typename ParamType2, typename ParamType3>
	class MemFunHandler3 : public MemFunHandlerBase
	{
	public:
		MemFunHandler3(ObjPtr op, FunPtr fp, ParamType pt, ParamType2 pt2, ParamType3 pt3) 
			: m_pObj(op), m_pFun(fp), m_Param(pt), m_Param2(pt2), m_Param3(pt3)
		{
		}

		~MemFunHandler3() {}

	public:
		void execute(void) { (m_pObj.get()->*m_pFun)(m_Param, m_Param2, m_Param3); }

	private:
		ObjPtr		m_pObj;
		FunPtr		m_pFun;
		typename std::remove_reference<ParamType>::type		m_Param;
		typename std::remove_reference<ParamType2>::type	m_Param2;
		typename std::remove_reference<ParamType3>::type	m_Param3;
	};

	template
		<
			class ObjPtr,
				typename FunPtr,
				typename ParamType,
				typename ParamType2,
				typename ParamType3,
				typename ParamType4
		>
	class MemFunHandler4 : public MemFunHandlerBase
	{
	public:
		MemFunHandler4(ObjPtr op, FunPtr fp, ParamType pt, ParamType2 pt2, ParamType3 pt3, ParamType4 pt4) 
			: m_pObj(op), m_pFun(fp), m_Param(pt), m_Param2(pt2), m_Param3(pt3), m_Param4(pt4)
		{
		}

		~MemFunHandler4() {}

	public:
		void execute(void) { (m_pObj.get()->*m_pFun)(m_Param, m_Param2, m_Param3, m_Param4); }

	private:
		ObjPtr		m_pObj;
		FunPtr		m_pFun;
		typename std::remove_reference<ParamType>::type		m_Param;
		typename std::remove_reference<ParamType2>::type	m_Param2;
		typename std::remove_reference<ParamType3>::type	m_Param3;
		typename std::remove_reference<ParamType4>::type	m_Param4;
	};

	template
		<
			class ObjPtr,
				typename FunPtr,
				typename ParamType,
				typename ParamType2,
				typename ParamType3,
				typename ParamType4,
				typename ParamType5
		>
	class MemFunHandler5 : public MemFunHandlerBase
	{
	public:
		MemFunHandler5(ObjPtr op, FunPtr fp, ParamType pt, ParamType2 pt2, ParamType3 pt3, ParamType4 pt4,
			ParamType5 pt5) 
			: m_pObj(op), m_pFun(fp), m_Param(pt), m_Param2(pt2), m_Param3(pt3), m_Param4(pt4), m_Param5(pt5)
		{
		}
		~MemFunHandler5() {}

	public:
		void execute(void) { (m_pObj.get()->*m_pFun)(m_Param, m_Param2, m_Param3, m_Param4, m_Param5); }

	private:
		ObjPtr		m_pObj;
		FunPtr		m_pFun;
		typename std::remove_reference<ParamType>::type		m_Param;
		typename std::remove_reference<ParamType2>::type	m_Param2;
		typename std::remove_reference<ParamType3>::type	m_Param3;
		typename std::remove_reference<ParamType4>::type	m_Param4;
		typename std::remove_reference<ParamType5>::type	m_Param5;
	};

	template
		<
			class ObjPtr,
				typename FunPtr,
				typename ParamType,
				typename ParamType2,
				typename ParamType3,
				typename ParamType4,
				typename ParamType5,
				typename ParamType6
		>
	class MemFunHandler6 : public MemFunHandlerBase
	{
	public:
		MemFunHandler6(ObjPtr op, FunPtr fp, ParamType pt, ParamType2 pt2, ParamType3 pt3, ParamType4 pt4,
			ParamType5 pt5, ParamType6 pt6) 
			: m_pObj(op), m_pFun(fp), m_Param(pt), m_Param2(pt2), m_Param3(pt3), m_Param4(pt4), m_Param5(pt5)
			, m_Param6(pt6)
		{
		}
		~MemFunHandler6() {}

	public:
		void execute(void) { (m_pObj.get()->*m_pFun)(m_Param, m_Param2, m_Param3, m_Param4, m_Param5, m_Param6); }

	private:
		ObjPtr		m_pObj;
		FunPtr		m_pFun;
		typename std::remove_reference<ParamType>::type		m_Param;
		typename std::remove_reference<ParamType2>::type	m_Param2;
		typename std::remove_reference<ParamType3>::type	m_Param3;
		typename std::remove_reference<ParamType4>::type	m_Param4;
		typename std::remove_reference<ParamType5>::type	m_Param5;
		typename std::remove_reference<ParamType6>::type	m_Param6;
	};

    template
        <
            class ObjPtr,
                typename FunPtr,
                typename ParamType,
                typename ParamType2,
                typename ParamType3,
                typename ParamType4,
                typename ParamType5,
                typename ParamType6,
                typename ParamType7
        >
    class MemFunHandler7 : public MemFunHandlerBase
    {
    public:
        MemFunHandler7(ObjPtr op, FunPtr fp, ParamType pt, ParamType2 pt2, ParamType3 pt3, ParamType4 pt4,
            ParamType5 pt5, ParamType6 pt6, ParamType7 pt7) 
            : m_pObj(op), m_pFun(fp), m_Param(pt), m_Param2(pt2), m_Param3(pt3), m_Param4(pt4), m_Param5(pt5)
            , m_Param6(pt6), m_Param7(pt7)
        {
        }
        ~MemFunHandler7() {}

    public:
        void execute(void) { (m_pObj.get()->*m_pFun)(m_Param, m_Param2, m_Param3, m_Param4, m_Param5, m_Param6, m_Param7); }

    private:
        ObjPtr		m_pObj;
        FunPtr		m_pFun;
        typename std::remove_reference<ParamType>::type		m_Param;
        typename std::remove_reference<ParamType2>::type	m_Param2;
        typename std::remove_reference<ParamType3>::type	m_Param3;
        typename std::remove_reference<ParamType4>::type	m_Param4;
        typename std::remove_reference<ParamType5>::type	m_Param5;
        typename std::remove_reference<ParamType6>::type	m_Param6;
        typename std::remove_reference<ParamType7>::type	m_Param7;
    };


	class GeneralTaskCmd : public ICommandBase, private ThisPtrHolder<GeneralTaskCmd>
	{
	public:
		typedef boost::shared_ptr<GeneralTaskCmd>		PtrType;

	private:
		GeneralTaskCmd() : m_pMFH(0) {}

		template<class ObjPtr, class FunPtr>
		GeneralTaskCmd(ObjPtr op, FunPtr fp) : m_pMFH(new MemFunHandler<ObjPtr, FunPtr>(op, fp))
		{
		}

	public:
		~GeneralTaskCmd()
		{
			if ( m_pMFH != NULL )
				delete m_pMFH;
		}

		template<typename PointerToObj, typename PointerToMemFn>
		static PtrType create( PointerToObj op, PointerToMemFn fp ) 
		{
			PtrType  pThis( new GeneralTaskCmd( op, fp ) );
			if (!pThis)
				throw NullPointerException("Null task command obj!");
			pThis->setThisPtr( pThis );
			return pThis;
		}

		void execute(void)
		{
			if ( m_pMFH != NULL )
				m_pMFH->execute();
		}

		void lockSelf( CommandPtr cp )
		{
			assert( !m_pSelf );
			assert( cp.get() == this );

			m_pSelf = boost::static_pointer_cast<GeneralTaskCmd>(cp);		
		}

		void unlockSelf()
		{
			assert( m_pSelf );
			m_pSelf.reset();
		}

		CommandPtr getCommandThisPtr() {
			return getThisPtr();
		}

	private:
		MemFunHandlerBase*	m_pMFH;
		PtrType				m_pSelf;
	};

	class GeneralTaskCmd1 : public ICommandBase, private ThisPtrHolder<GeneralTaskCmd1>//, public SmallObject_CC<>
	{
	public:
		typedef boost::shared_ptr<GeneralTaskCmd1>		PtrType;

	private:
		GeneralTaskCmd1() : m_pMFH(0) {}

		template<class ObjPtr, class FunPtr, class PT>
		GeneralTaskCmd1(ObjPtr op, FunPtr fp, PT pt):m_pMFH(new MemFunHandler1<ObjPtr, FunPtr, PT>(op, fp, pt))
		{
		}

	public:
		~GeneralTaskCmd1()
		{
			if ( m_pMFH != NULL )
				delete m_pMFH;
		}

		template<typename PointerToObj, typename PointerToMemFn, typename ParamType>
		static PtrType create( PointerToObj op, PointerToMemFn fp, ParamType pt ) 
		{
			PtrType  pThis( new GeneralTaskCmd1( op, fp, pt ) );
			if (!pThis)
				throw NullPointerException("Null task command obj!");
			pThis->setThisPtr( pThis );
			return pThis;
		}

		void execute(void)
		{
			if ( m_pMFH != NULL )
				m_pMFH->execute();
		}

		void lockSelf( CommandPtr cp )
		{
			assert( !m_pSelf );
			assert( cp.get() == this );

			m_pSelf = boost::static_pointer_cast<GeneralTaskCmd1>(cp);
		}

		void unlockSelf()
		{
			assert( m_pSelf );
			m_pSelf.reset();
		}

		CommandPtr getCommandThisPtr() {
			return getThisPtr();
		}

	private:
		MemFunHandlerBase*	m_pMFH;
		PtrType				m_pSelf;
	};

	class GeneralTaskCmd2 : public ICommandBase, private ThisPtrHolder<GeneralTaskCmd2>//, public SmallObject_CC<>
	{
	public:
		typedef boost::shared_ptr<GeneralTaskCmd2>		PtrType;

	private:
		GeneralTaskCmd2() : m_pMFH(0) {}

		template<class ObjPtr, class FunPtr, class PT1, class PT2>
		GeneralTaskCmd2(ObjPtr op, FunPtr fp, PT1 pt1, PT2 pt2)
			: m_pMFH(new MemFunHandler2<ObjPtr, FunPtr, PT1, PT2>(op, fp, pt1, pt2))
		{
		}

	public:
		~GeneralTaskCmd2()
		{
			if ( m_pMFH != NULL )
				delete m_pMFH;
		}

		template<typename PointerToObj, typename PointerToMemFn, typename ParamType1, typename ParamType2>
		static PtrType create( PointerToObj op, PointerToMemFn fp, ParamType1 pt1, ParamType2 pt2 ) 
		{
			PtrType  pThis( new GeneralTaskCmd2( op, fp, pt1, pt2 ) );
			if (!pThis)
				throw NullPointerException("Null task command obj!");
			pThis->setThisPtr( pThis );
			return pThis;
		}

		void execute(void)
		{
			if ( m_pMFH != NULL )
				m_pMFH->execute();
		}

		void lockSelf( CommandPtr cp )
		{
			assert( !m_pSelf );
			assert( cp.get() == this );

			m_pSelf = boost::static_pointer_cast<GeneralTaskCmd2>(cp);
		}

		void unlockSelf()
		{
			assert( m_pSelf );
			m_pSelf.reset();
		}

		CommandPtr getCommandThisPtr() {
			return getThisPtr();
		}

	private:
		MemFunHandlerBase*	m_pMFH;
		PtrType				m_pSelf;
	};

	class GeneralTaskCmd3 : public ICommandBase, private ThisPtrHolder<GeneralTaskCmd3>//, public SmallObject_CC<>
	{
	public:
		typedef boost::shared_ptr<GeneralTaskCmd3>		PtrType;

	private:
		GeneralTaskCmd3() : m_pMFH(0) {}

		template<class ObjPtr, class FunPtr, class PT1, class PT2, class PT3>
		GeneralTaskCmd3(ObjPtr op, FunPtr fp, PT1 pt1, PT2 pt2, PT3 pt3)
			: m_pMFH(new MemFunHandler3<ObjPtr, FunPtr, PT1, PT2, PT3>(op, fp, pt1, pt2, pt3))
		{
		}

	public:
		~GeneralTaskCmd3()
		{
			if ( m_pMFH != NULL )
				delete m_pMFH;
		}

		template<typename PointerToObj, typename PointerToMemFn, typename ParamType1, typename ParamType2, typename ParamType3>
		static PtrType create( PointerToObj op, PointerToMemFn fp, ParamType1 pt1, ParamType2 pt2, ParamType3 pt3 ) 
		{
			PtrType  pThis( new GeneralTaskCmd3( op, fp, pt1, pt2, pt3 ) );
			if (!pThis)
				throw NullPointerException("Null task command obj!");
			pThis->setThisPtr( pThis );
			return pThis;
		}

		void execute(void)
		{
			if ( m_pMFH != NULL )
				m_pMFH->execute();
		}

		void lockSelf( CommandPtr cp )
		{
			assert( !m_pSelf );
			assert( cp.get() == this );

			m_pSelf = boost::static_pointer_cast<GeneralTaskCmd3>(cp);
		}

		void unlockSelf()
		{
			assert( m_pSelf );
			m_pSelf.reset();
		}

		CommandPtr getCommandThisPtr() {
			return getThisPtr();
		}

	private:
		MemFunHandlerBase*	m_pMFH;
		PtrType				m_pSelf;
	};

	class GeneralTaskCmd4 : public ICommandBase, private ThisPtrHolder<GeneralTaskCmd4>//, public SmallObject_CC<>
	{
	public:
		typedef boost::shared_ptr<GeneralTaskCmd4>		PtrType;

	private:
		GeneralTaskCmd4() : m_pMFH(0) {}

		template<class ObjPtr, class FunPtr, class PT1, class PT2, class PT3, class PT4>
		GeneralTaskCmd4(ObjPtr op, FunPtr fp, PT1 pt1, PT2 pt2, PT3 pt3, PT4 pt4)
			: m_pMFH(new MemFunHandler4<ObjPtr, FunPtr, PT1, PT2, PT3, PT4>(op, fp, pt1, pt2, pt3, pt4))
		{
		}

	public:
		~GeneralTaskCmd4()
		{
			if ( m_pMFH != NULL )
				delete m_pMFH;
		}

		template<typename PointerToObj, typename PointerToMemFn, typename ParamType1, typename ParamType2, typename ParamType3, typename ParamType4>
		static PtrType create( PointerToObj op, PointerToMemFn fp, ParamType1 pt1, ParamType2 pt2, ParamType3 pt3, ParamType4 pt4 ) 
		{
			PtrType  pThis( new GeneralTaskCmd4( op, fp, pt1, pt2, pt3, pt4 ) );
			if (!pThis)
				throw NullPointerException("Null task command obj!");
			pThis->setThisPtr( pThis );
			return pThis;
		}

		void execute(void)
		{
			if ( m_pMFH != NULL )
				m_pMFH->execute();
		}

		void lockSelf( CommandPtr cp )
		{
			assert( !m_pSelf );
			assert( cp.get() == this );

			m_pSelf = boost::static_pointer_cast<GeneralTaskCmd4>(cp);
		}

		void unlockSelf()
		{
			assert( m_pSelf );
			m_pSelf.reset();
		}

		CommandPtr getCommandThisPtr() {
			return getThisPtr();
		}

	private:
		MemFunHandlerBase*	m_pMFH;
		PtrType				m_pSelf;
	};

	class GeneralTaskCmd5 : public ICommandBase, private ThisPtrHolder<GeneralTaskCmd5>//, public SmallObject_CC<>
	{
	public:
		typedef boost::shared_ptr<GeneralTaskCmd5>		PtrType;

	private:
		GeneralTaskCmd5() : m_pMFH(0) {}

		template<class ObjPtr, class FunPtr, class PT1, class PT2, class PT3, class PT4, class PT5>
		GeneralTaskCmd5(ObjPtr op, FunPtr fp, PT1 pt1, PT2 pt2, PT3 pt3, PT4 pt4, PT5 pt5)
			: m_pMFH(new MemFunHandler5<ObjPtr, FunPtr, PT1, PT2, PT3, PT4, PT5>(op, fp, pt1, pt2, pt3, pt4, pt5))
		{
		}

	public:
		~GeneralTaskCmd5()
		{
			if ( m_pMFH != NULL )
				delete m_pMFH;
		}

		template
			<
			typename PointerToObj,
			typename PointerToMemFn,
			typename ParamType1,
			typename ParamType2,
			typename ParamType3,
			typename ParamType4,
			typename ParamType5
			>
			static PtrType create( PointerToObj op, PointerToMemFn fp, ParamType1 pt1, ParamType2 pt2, 
			ParamType3 pt3, ParamType4 pt4, ParamType5 pt5 ) 
		{
			PtrType  pThis( new GeneralTaskCmd5( op, fp, pt1, pt2, pt3, pt4, pt5 ) );
			if (!pThis)
				throw NullPointerException("Null task command obj!");
			pThis->setThisPtr( pThis );
			return pThis;
		}

		void execute(void)
		{
			if ( m_pMFH != NULL )
				m_pMFH->execute();
		}

		void lockSelf( CommandPtr cp )
		{
			assert( !m_pSelf );
			assert( cp.get() == this );

			m_pSelf = boost::static_pointer_cast<GeneralTaskCmd5>(cp);
		}

		void unlockSelf()
		{
			assert( m_pSelf );
			m_pSelf.reset();
		}

		CommandPtr getCommandThisPtr() {
			return getThisPtr();
		}

	private:
		MemFunHandlerBase*	m_pMFH;
		PtrType				m_pSelf;
	};

	class GeneralTaskCmd6 : public ICommandBase, private ThisPtrHolder<GeneralTaskCmd6>//, public SmallObject_CC<>
	{
	public:
		typedef boost::shared_ptr<GeneralTaskCmd6>		PtrType;

	private:
		GeneralTaskCmd6() : m_pMFH(0) {}

		template<class ObjPtr, class FunPtr, class PT1, class PT2, class PT3, class PT4, class PT5, class PT6>
		GeneralTaskCmd6(ObjPtr op, FunPtr fp, PT1 pt1, PT2 pt2, PT3 pt3, PT4 pt4, PT5 pt5, PT6 pt6)
			: m_pMFH(new MemFunHandler6<ObjPtr, FunPtr, PT1, PT2, PT3, PT4, PT5, PT6>(op, fp, pt1, pt2, pt3, pt4, pt5, pt6))
		{
		}

	public:
		~GeneralTaskCmd6()
		{
			if ( m_pMFH != NULL )
				delete m_pMFH;
		}

		template
			<
			typename PointerToObj,
			typename PointerToMemFn,
			typename ParamType1,
			typename ParamType2,
			typename ParamType3,
			typename ParamType4,
			typename ParamType5,
			typename ParamType6
			>
			static PtrType create( PointerToObj op, PointerToMemFn fp, ParamType1 pt1, ParamType2 pt2, 
			ParamType3 pt3, ParamType4 pt4, ParamType5 pt5, ParamType6 pt6 ) 
		{
			PtrType  pThis( new GeneralTaskCmd6( op, fp, pt1, pt2, pt3, pt4, pt5, pt6 ) );
			if (!pThis)
				throw NullPointerException("Null task command obj!");
			pThis->setThisPtr( pThis );
			return pThis;
		}

		void execute(void)
		{
			if ( m_pMFH != NULL )
				m_pMFH->execute();
		}

		void lockSelf( CommandPtr cp )
		{
			assert( !m_pSelf );
			assert( cp.get() == this );

			m_pSelf = boost::static_pointer_cast<GeneralTaskCmd6>(cp);
		}

		void unlockSelf()
		{
			assert( m_pSelf );
			m_pSelf.reset();
		}

		CommandPtr getCommandThisPtr() {
			return getThisPtr();
		}

	private:
		MemFunHandlerBase*	m_pMFH;
		PtrType				m_pSelf;
	};

    class GeneralTaskCmd7 : public ICommandBase, private ThisPtrHolder<GeneralTaskCmd7>
    {
    public:
        typedef boost::shared_ptr<GeneralTaskCmd7>		PtrType;

    private:
        GeneralTaskCmd7() : m_pMFH(0) {}

        template<class ObjPtr, class FunPtr, class PT1, class PT2, class PT3, class PT4, class PT5, class PT6, class PT7>
        GeneralTaskCmd7(ObjPtr op, FunPtr fp, PT1 pt1, PT2 pt2, PT3 pt3, PT4 pt4, PT5 pt5, PT6 pt6, PT7 pt7)
            : m_pMFH(new MemFunHandler7<ObjPtr, FunPtr, PT1, PT2, PT3, PT4, PT5, PT6>(op, fp, pt1, pt2, pt3, pt4, pt5, pt6, pt7))
        {
        }

    public:
        ~GeneralTaskCmd7()
        {
            if ( m_pMFH != NULL )
                delete m_pMFH;
        }

        template
            <
            typename PointerToObj,
            typename PointerToMemFn,
            typename ParamType1,
            typename ParamType2,
            typename ParamType3,
            typename ParamType4,
            typename ParamType5,
            typename ParamType6,
            typename ParamType7
            >
            static PtrType create( PointerToObj op, PointerToMemFn fp, ParamType1 pt1, ParamType2 pt2, 
            ParamType3 pt3, ParamType4 pt4, ParamType5 pt5, ParamType6 pt6, ParamType7 pt7 ) 
        {
            PtrType  pThis( new GeneralTaskCmd7( op, fp, pt1, pt2, pt3, pt4, pt5, pt6, pt7 ) );
            if (!pThis)
                throw NullPointerException("Null task command obj!");
            pThis->setThisPtr( pThis );
            return pThis;
        }

        void execute(void)
        {
            if ( m_pMFH != NULL )
                m_pMFH->execute();
        }

        void lockSelf( CommandPtr cp )
        {
            assert( !m_pSelf );
            assert( cp.get() == this );

            m_pSelf = boost::static_pointer_cast<GeneralTaskCmd7>(cp);
        }

        void unlockSelf()
        {
            assert( m_pSelf );
            m_pSelf.reset();
        }

        CommandPtr getCommandThisPtr() {
            return getThisPtr();
        }

    private:
        MemFunHandlerBase*	m_pMFH;
        PtrType				m_pSelf;
    };

} // namespace XYCTOOLS

#endif	// QNAC_COMMAND_H_
