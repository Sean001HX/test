#ifndef DTAPIH
#define DTAPIH

namespace datayes {

#ifdef __linux__
#define DTAPICALL
#define DTAPIDLLCALL
#else
#define DTAPICALL	__cdecl
#define DTAPIDLLCALL __cdecl
#endif

#define DTAPIMETHOD(type) virtual type DTAPICALL
#define DTAPIMETHODIMPL(type) type DTAPICALL

extern "C" int DTAPIDLLCALL DllInterlockedIncrement(volatile int*);
extern "C" int DTAPIDLLCALL DllInterlockedDecrement(volatile int*);

class RefCounted {
public:
	DTAPIMETHOD(void) AddRef() = 0;
	DTAPIMETHOD(int) ReleaseRef() = 0;
};

template<class Base>
class RefCountedImplT: public Base {
public:
	RefCountedImplT() :
			m_RefCount(0) {
	}

	virtual ~RefCountedImplT() {
	}

	DTAPIMETHOD(void) AddRef() {
		DllInterlockedIncrement(&m_RefCount);
	}

	DTAPIMETHOD(int) ReleaseRef() {
		int ret = DllInterlockedDecrement(&m_RefCount);
		if (ret == 0) {
			delete this;
		}
		return ret;
	}

protected:
	volatile int m_RefCount;
};

typedef RefCountedImplT<RefCounted> RefCountedImpl;

template<class T>
class RefCountedPtrT {
public:
	typedef T ClassType;

	RefCountedPtrT() :
			m_RefObj(0) {
	}

	~RefCountedPtrT() {
		if (m_RefObj != 0) {
			m_RefObj->ReleaseRef();
			m_RefObj = 0;
		}
	}

	explicit RefCountedPtrT(T* p) :
			m_RefObj(p) {
		if (m_RefObj != 0) {
			m_RefObj->AddRef();
		}
	}

	RefCountedPtrT(const RefCountedPtrT<T>& right) :
			m_RefObj(right.m_RefObj) {
		if (m_RefObj != 0) {
			m_RefObj->AddRef();
		}
	}

	RefCountedPtrT<T>& operator =(const RefCountedPtrT<T>& right) {
		RefCountedPtrT<T>(right).Swap(*this);
		return *this;
	}

	bool operator ==(const RefCountedPtrT<T>& right) const {
		return m_RefObj == right.m_RefObj;
	}

	void CreateInstance() {
		T* obj = new T();
		Reset(obj);
	}

	// add ref and return ptr
	T* Duplicate() {
		if (m_RefObj != 0) {
			m_RefObj->AddRef();
		}

		return m_RefObj;
	}

	RefCountedPtrT<T>& Swap(RefCountedPtrT<T>& a) {
		T* tmp = a.m_RefObj;
		a.m_RefObj = m_RefObj;
		m_RefObj = tmp;
		return *this;
	}

	T& operator *() {
		return *m_RefObj;
	}

	const T& operator *() const {
		return *m_RefObj;
	}

	T* operator ->() {
		return m_RefObj;
	}

	const T* operator ->() const {
		return m_RefObj;
	}

	bool operator <(const RefCountedPtrT<T>& right) const {
		return m_RefObj < right.m_RefObj;
	}

	T* Get() {
		return (T*)m_RefObj;
	}

	const T* Get() const {
		return m_RefObj;
	}

	void Reset(T* p = 0) {
		RefCountedPtrT<T> a(p);
		Swap(a);
	}

	bool IsNull() const {
		return m_RefObj == 0;
	}

private:
	T* m_RefObj;
};

typedef RefCountedPtrT<RefCounted> RefCountedPtr;

template<class T>
inline RefCountedPtrT<T> PtrFromReturn(T* ret) {
	RefCountedPtrT<T> retPtr(ret);
	if (ret != 0) {
		ret->ReleaseRef();
	}
	return retPtr;
}

} // DTAPI

#endif
