#include <boost\uuid\uuid.hpp>
#include <boost\uuid\uuid_io.hpp>
#include <boost\uuid\random_generator.hpp>  // for  boost::uuids

#include "utility_fun.h"
#include <time.h>
#include <windows.h>

namespace UtilityFun{

    bool IsEqual(double left, double right)
    {
        double delta = left - right;
        if (delta > -HX_DOUBLE_PRECISE && delta < HX_DOUBLE_PRECISE)
            return true;

        return false;
    }

    double Round(double src, double base)
    {
        if (base > -HX_DOUBLE_PRECISE && base < HX_DOUBLE_PRECISE)
            return src;
        if (src == 0)
            return 0.0;
        if (src > 0)
            return ((long long)((src + base / 2) / base)) * base;
        else
            return ((long long)((src - base / 2) / base)) * base;
    }

    bool CanBeDivided(double src, double base)
    {
        if (base > -HX_DOUBLE_PRECISE && base < HX_DOUBLE_PRECISE)
            return false;

        double theta = src / base;
        double delta = theta - (long long)(theta);
        if ((delta > -HX_DOUBLE_PRECISE && delta < HX_DOUBLE_PRECISE) || (delta - 1 > -HX_DOUBLE_PRECISE) || (delta + 1 < HX_DOUBLE_PRECISE))
            return true;

        return false;
    }

    void GetCurrentIntdateAndIntTime(int& date, int& time)
    {
        SYSTEMTIME st = { 0 };
        GetLocalTime(&st);

        date = st.wYear * 10000 + st.wMonth * 100 + st.wDay;
        time = st.wHour * 10000 + st.wMinute * 100 + st.wSecond;
    }

    int GetDaysOfMonth(int nYear, int nMonth)
    {
        if (nMonth < 1 || nMonth > 12)
        {
            return -1;
        }

        if (nMonth == 2 && isLeapYear(nYear))
            return 29;

        static int month[12];
        month[1] = 31;
        month[2] = 28;
        month[3] = 31;
        month[4] = 30;
        month[5] = 31;
        month[6] = 30;
        month[7] = 31;
        month[8] = 31;
        month[9] = 30;
        month[10] = 31;
        month[11] = 30;
        month[12] = 31;

        return month[nMonth];
    }

    bool isLeapYear(int year)
    {
        if ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0))
        {
            return true;
        }

        return false;
    }

    int GetDaysOfYear(int year)
    {
        return isLeapYear(year) ? 366 : 365;
    }

    bool DateFirstNewerThanSecond(int date1, int time1, int date2, int time2)
    {
        if (date1 > date2 || (date1 == date2 && time1 > time2))
            return true;

        return false;
    }

    //´«ÈëÊý¾Ý±ØÐëºÏ·¨
    void GetPreDay(int year, int month, int day, int& outYear, int& outMonth, int& outDay)
    {
        if (day > 1)
        {
            outYear = year;
            outMonth = month;
            outDay = day - 1;
            return;
        }

        if (month > 1)
        {
            outYear = year;
            outMonth = month - 1;
            outDay = GetDaysOfMonth(outYear, outMonth);
            return;
        }

        outYear = year - 1;
        outMonth = 12;
        outDay = GetDaysOfMonth(outYear, outMonth);
        return;
    }

    void GetPreDayToSelf(int& outYear, int& outMonth, int& outDay)
    {
        if (outDay > 1)
        {
            outDay -= 1;
            return;
        }

        if (outMonth > 1)
        {
            outMonth -= 1;
            outDay = GetDaysOfMonth(outYear, outMonth);
            return;
        }

        outYear -= 1;
        outMonth = 12;
        outDay = GetDaysOfMonth(outYear, outMonth);
        return;
    }

    int GetPreWorkDay(int dt)
    {
        int year = dt / 10000;

        int day = dt % 100;
        int mon = (dt % 10000) / 100;
        GetPreWorkDayToSelf(year, mon, day);
        return year * 10000 + mon * 100 + day;
    }

    void GetPreWorkDay(int year, int mon, int day, int& outYear, int& outMonth, int& outDay)
    {
        GetPreDay(year, mon, day, outYear, outMonth, outDay);
        int dayOfWeek = GetDayOfWeek(outYear, outMonth, outDay);
        if (dayOfWeek < 6)
        {
            return;
        }

        for (int i = 5; i < dayOfWeek; ++i)
        {
            GetPreDayToSelf(outYear, outMonth, outDay);
        }
    }

    void GetPreWorkDayToSelf(int& outYear, int& outMon, int& outDay)
    {
        GetPreDayToSelf(outYear, outMon, outDay);
        int dayOfWeek = GetDayOfWeek(outYear, outMon, outDay);
        if (dayOfWeek < 6)
        {
            return;
        }

        for (int i = 5; i < dayOfWeek; ++i)
        {
            GetPreDayToSelf(outYear, outMon, outDay);
        }
    }

    int GetDayOfWeek(int year, int mon, int day)
    {
        // »ùÄ·À­¶ûÉ­¹«Ê½ 0=ÐÇÆÚÌì 
        int m = mon;
        int d = day;
        int y = year;
        if (m == 1){ m = 13; y--; }

        if (m == 2) { m = 14; y--; }

        if ((y < 1752) || ((y == 1752) && (m < 9)) || ((y == 1752) && (m == 9) && (d < 3))) //ÅÐ¶ÏÊÇ·ñÔÚ1752Äê9ÔÂ3ÈÕÖ®Ç°
            return (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 + 5) % 7; //1752Äê9ÔÂ3ÈÕÖ®Ç°µÄ¹«Ê½

        return 1 + (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7; //1752Äê9ÔÂ3ÈÕÖ®ºóµÄ¹«Ê½
    }

    int GetDayOfWeek(int date)
    {
        int year = date / 10000;
        int day = date % 100;
        int mon = (date % 10000) / 100;
        return GetDayOfWeek(year, mon, day);
    }

    int GetNextWorkDay(int dt)
    {
        int year = dt / 10000;

        int day = dt % 100;
        int mon = (dt % 10000) / 100;
        GetNextWorkDayToSelf(year, mon, day);
        return year * 10000 + mon * 100 + day;
    }

    void GetNextWorkDay(int year, int mon, int day, int& outYear, int& outMonth, int& outDay)
    {
        GetNextDay(year, mon, day, outYear, outMonth, outDay);
        int dayOfWeek = GetDayOfWeek(outYear, outMonth, outDay);
        if (dayOfWeek > 5)
        {
            return;
        }

        for (int i = 5; i < dayOfWeek; ++i)
        {
            GetNextDayToSelf(outYear, outMonth, outDay);
        }
    }

    void GetNextDay(int year, int mon, int day, int& outYear, int& outMonth, int& outDay)
    {
        if (day < GetDaysOfMonth(year, mon))
        {
            outYear = year;
            outMonth = mon;
            outDay = day + 1;
            return;
        }

        outDay = 1;
        if (mon < 12)
        {
            outYear = year;
            outMonth = mon + 1;
            return;
        }

        outYear = year + 1;
        outMonth = 1;
        return;
    }

    void GetNextDayToSelf(int& outYear, int& outMonth, int& outDay)
    {
        if (outDay < GetDaysOfMonth(outYear, outMonth))
        {
            outDay += 1;
            return;
        }

        outDay = 1;
        if (outMonth < 12)
        {
            outMonth += 1;
            return;
        }

        outYear += 1;
        outMonth = 1;
        return;
    }

    void GetNextWorkDayToSelf(int& outYear, int& outMonth, int& outDay)
    {
        GetNextDayToSelf(outYear, outMonth, outDay);
        int dayOfWeek = GetDayOfWeek(outYear, outMonth, outDay);
        if (dayOfWeek < 6)
        {
            return;
        }

        for (int i = dayOfWeek; i <= 7; ++i)
        {
            GetNextDayToSelf(outYear, outMonth, outDay);
        }
    }

    bool compareDouble(double left, double right, double mixSpace /*= HX_DOUBLE_PRECISE*/)
    {
        double delta = left - right;
        if (delta > -mixSpace && delta < mixSpace)
            return true;

        return false;
    }

    std::string createGUID()
    {
        // 存在warning C4996
        boost::uuids::random_generator gen;
        boost::uuids::uuid guid(gen());
        return boost::uuids::to_string(guid);
    }

    std::string getCurrentDate()
    {
        SYSTEMTIME st = { 0 };
        GetLocalTime(&st);
        char szBuffer[40] = { 0 };
        _snprintf_s(szBuffer, sizeof(szBuffer) - 1, "%04d-%02d-%02d", st.wYear, st.wMonth, st.wDay);
        return szBuffer;
    }

    std::string getCurrentTime()
    {
        SYSTEMTIME st = { 0 };
        GetLocalTime(&st);
        char szBuffer[40] = { 0 };
        _snprintf_s(szBuffer, sizeof(szBuffer) - 1, "%02d:%02d:%02d", st.wHour, st.wMinute, st.wSecond);
        return szBuffer;
    }

    std::string getCurrentDateTime()
    {
        return getCurrentDate() + " " + getCurrentTime();
    }

    std::string getAddDate(int days)
    {
        char szBuffer[40] = { 0 };
        time_t ltime;

        struct tm   tmcur;

        time(&ltime);
        ltime = ltime + days * 60 * 60 * 24;
        localtime_s(&tmcur, &ltime);
        _snprintf_s(szBuffer, sizeof(szBuffer) - 1, "%04d-%02d-%02d", tmcur.tm_year + 1900, tmcur.tm_mon + 1, tmcur.tm_mday);
        return szBuffer;
    }

    std::string getAddDate(const std::string& d1, int days)
    {
        if (d1.empty())
            return "0000-00-00";

        struct tm tm1;
        int i = sscanf_s(d1.c_str(), "%04d-%02d-%02d",
            &(tm1.tm_year),
            &(tm1.tm_mon),
            &(tm1.tm_mday));

        tm1.tm_year -= 1900;
        tm1.tm_mon--;
        tm1.tm_hour = 0;
        tm1.tm_min = 0;
        tm1.tm_sec = 0;
        tm1.tm_isdst = -1;

        time_t ltime;
        ltime = mktime(&tm1);
        ltime = ltime + days * 60 * 60 * 24;

        struct tm   tmcur;
        localtime_s(&tmcur, &ltime);
        char szBuffer[40] = { 0 };
        _snprintf_s(szBuffer, sizeof(szBuffer) - 1, "%04d-%02d-%02d", tmcur.tm_year + 1900, tmcur.tm_mon + 1, tmcur.tm_mday);

        return szBuffer;
    }

    int getDateSpace(const std::string& d1, const std::string& d2)
    {
        if (d1.empty() || d2.empty())
            return -1;

        struct tm tm1, tm2;
        sscanf_s(d1.c_str(), "%04d-%02d-%02d",
            &(tm1.tm_year),
            &(tm1.tm_mon),
            &(tm1.tm_mday));

        tm1.tm_year -= 1900;
        tm1.tm_mon--;
        tm1.tm_hour = 0;
        tm1.tm_min = 0;
        tm1.tm_sec = 0;
        tm1.tm_isdst = -1;

        sscanf_s(d2.c_str(), "%04d-%02d-%02d",
            &(tm2.tm_year),
            &(tm2.tm_mon),
            &(tm2.tm_mday));

        tm2.tm_year -= 1900;
        tm2.tm_mon--;
        tm2.tm_hour = 0;
        tm2.tm_min = 0;
        tm2.tm_sec = 0;
        tm2.tm_isdst = -1;

        time_t time_day1 = mktime(&tm1);
        time_t time_day2 = mktime(&tm2);

        int value = abs(time_day1 - time_day2);
        int  day = value / (60 * 60 * 24);
        return day;
    }

    int getDateTimeSpace(const std::string& dt1, const std::string& dt2)
    {
        if (dt1.empty() || dt2.empty())
            return -1;

        struct tm tm1, tm2;
        sscanf_s(dt1.c_str(), "%04d-%02d-%02d %2d:%2d:%2d",
            &(tm1.tm_year),
            &(tm1.tm_mon),
            &(tm1.tm_mday),
            &(tm1.tm_hour),
            &(tm1.tm_min),
            &(tm1.tm_sec));

        tm1.tm_year -= 1900;
        tm1.tm_mon--;
        tm1.tm_isdst = -1;

        sscanf_s(dt2.c_str(), "%04d-%02d-%02d %2d:%2d:%2d",
            &(tm2.tm_year),
            &(tm2.tm_mon),
            &(tm2.tm_mday),
            &(tm2.tm_hour),
            &(tm2.tm_min),
            &(tm2.tm_sec));

        tm2.tm_year -= 1900;
        tm2.tm_mon--;
        tm2.tm_isdst = -1;

        time_t time_day1 = mktime(&tm1);
        time_t time_day2 = mktime(&tm2);

        long long value = abs(time_day1 - time_day2);
        int day = value / (60 * 60 * 24);
        return day;
    }

    const size_t get_cpu_count(void)
    {
        //may return 0 when not able to detect
        //return std::thread::hardware_concurrency();
#ifdef WIN32 
        SYSTEM_INFO sysinfo;
        GetSystemInfo(&sysinfo);
        return sysinfo.dwNumberOfProcessors;
#elif MACOS 
        int nm[2];
        size_t len = 4;
        uint32_t count;

        nm[0] = CTL_HW; nm[1] = HW_AVAILCPU;
        sysctl(nm, 2, &count, &len, NULL, 0);

        if (count < 1) {
            nm[1] = HW_NCPU;
            sysctl(nm, 2, &count, &len, NULL, 0);
            if (count < 1) { count = 1; }
        }
        return count;
#else 
        return sysconf(_SC_NPROCESSORS_ONLN);
#endif 
    }

}
