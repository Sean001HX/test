#include "asm_mutex.h"

namespace AllTrade {
    namespace NPTradeCenter {

        namespace StockApiManager
        {
            CHxMutex::CHxMutex()
            {
                InitializeCriticalSection(&critical_section_);
            }
            CHxMutex::~CHxMutex()
            {
                DeleteCriticalSection(&critical_section_);
            }
            void CHxMutex::Lock()
            {
                EnterCriticalSection(&critical_section_);
            }
            void CHxMutex::Unlock()
            {
                LeaveCriticalSection(&critical_section_);
            }

            bool CHxMutex::TryLock()
            {
                return TryEnterCriticalSection(&critical_section_);
            }

            CHxMutexGuard::CHxMutexGuard(CHxMutex *mutex /*= 0*/) : mutex_(mutex)
            {
                if (mutex_)
                    mutex_->Lock();
            }

            CHxMutexGuard::~CHxMutexGuard()
            {
                if (mutex_)
                    mutex_->Unlock();
            }
        }
    }
}