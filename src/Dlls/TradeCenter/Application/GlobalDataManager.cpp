#include <stdlib.h>
#include "GlobalDataManager.h"
#include "include/OperationManager/OperationManager.h"
#include "utility/utility_fun.h"
#include "define/struct_base.h"

#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx.hpp"
#include "C:/ng_tools/ng_header_for_log4cxx/ng_header_for_log4cxx_log_var.hpp"
NG_LOGGER(logger, "SettleManagerThread");

using namespace OperationManager;
using namespace AllTrade::NPMgrCenter;

namespace AllTrade {
    namespace NPTradeCenter {

        GlobalDataManager::GlobalDataManager()
        {
            m_global_data = COperationManager::instance()->getCurrentGlobalData();
        }

        GlobalDataManager::~GlobalDataManager()
        {

        }

        AllTrade::PShadowOrderIDType GlobalDataManager::getCurShadowOrderID_c()
        {
            int rslt_i = getCurShadowOrderID();

            SYSTEMTIME st = { 0 };
            GetLocalTime(&st);

            
            char rslt[20] = { 0 };
            srand((unsigned int)time(NULL) + (unsigned int)rslt_i);
            _snprintf_s(rslt, sizeof(rslt) - 1, "%04d%02d%02d%05d%03d", st.wYear, st.wMonth, st.wDay, rslt_i, (rand() % 999) + 1);
            return rslt;
        }

        int GlobalDataManager::getCurShadowOrderID()
        {
            writeLock lock(m_mtx_order);
            m_global_data->shadow_order_id_++;
            serialize();
            return m_global_data->shadow_order_id_;
        }

        AllTrade::PShadowOrderIDType GlobalDataManager::getCurShadowTradeID_c()
        {
            int rslt_i = getCurShadowTradeID();

            SYSTEMTIME st = { 0 };
            GetLocalTime(&st);

            char rslt[20] = { 0 };

            srand((unsigned int)time(NULL) + (unsigned int)rslt_i);
            _snprintf_s(rslt, sizeof(rslt) - 1, "%04d%02d%02d%05d%03d", st.wYear, st.wMonth, st.wDay, rslt_i, (rand() % 999) + 1);
            return rslt;
        }

        int GlobalDataManager::getCurShadowTradeID()
        {
            writeLock lock(m_mtx_trade);
            m_global_data->shadow_trade_id_++;
            serialize();
            return m_global_data->shadow_trade_id_;
        }

        void GlobalDataManager::settle()
        {
            m_global_data->shadow_order_id_ = 0;
            m_global_data->shadow_trade_id_ = 0;
            serialize();
        }

        void GlobalDataManager::serialize()
        {
            COperationManager::instance()->updateCurGlobalData(m_global_data);
        }

    }
}