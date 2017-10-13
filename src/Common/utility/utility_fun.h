/*
* Purpose: 为程序提供公共函数
*/
#ifndef __UTILITY_FUN_H__
#define __UTILITY_FUN_H__

#include <string>

namespace UtilityFun{
    #define HX_DOUBLE_PRECISE           1e-8  //  double型数据精度
    // mixSpace: 最小变动单位
    extern bool compareDouble(double left, double right, double mixSpace = HX_DOUBLE_PRECISE);

    // 获取128位GUID,ASCII表示时为32个字符加4个分隔符
    extern std::string createGUID();

    // 获取当前日期,格式:YYYY-MM-DD
    extern std::string getCurrentDate();
    // 获取当前时间,格式:HH:MM:SS
    extern std::string getCurrentTime();
    // 获取当前日期时间,格式:YYYY-MM-DD HH:MM:SS
    extern std::string getCurrentDateTime();
    // 获取当前日期,格式:YYYY-MM-DD
    extern std::string getAddDate(int days);
    extern std::string getAddDate(const std::string& d1, int days);
    // 获取两个日期之间相差时间间隔天数,余数不取
    extern int getDateSpace(const std::string& d1, const std::string& d2);
    extern int getDateTimeSpace(const std::string& dt1, const std::string& dt2);

    extern const size_t get_cpu_count(void);

    //  判断实数是否相等
    extern bool IsEqual(double left, double right);
    //  四舍五入 其中 base > 0
    extern double Round(double src, double base);
    //  成否被整除
    extern bool CanBeDivided(double src, double base);

    //获取当前 int date & int time
    extern void GetCurrentIntdateAndIntTime(int& date, int& time);

    extern int GetDaysOfMonth(int nYear, int nMonth);

    //比较int date int time时间新旧
    extern bool DateFirstNewerThanSecond(int date1, int time1, int date2, int time2);
    //获取时间
    extern int GetPreWorkDay(int dt);
    extern void GetPreWorkDayToSelf(int& outYear, int& outMon, int& outDay);
    extern void GetPreWorkDay(int year, int mon, int day, int& outYear, int& outMonth, int& outDay);
    extern void GetPreDay(int year, int month, int day, int& outYear, int& outMonth, int& outDay);
    extern void GetPreDayToSelf(int& outYear, int& outMonth, int& outDay);
    extern bool isLeapYear(int year);
    extern int GetDaysOfYear(int year);
    extern int GetDayOfWeek(int y, int m, int d);
    extern int GetDayOfWeek(int date);
    extern int GetNextWorkDay(int dt);
    extern void GetNextWorkDay(int year, int mon, int day, int& outYear, int& outMonth, int& outDay);
    extern void GetNextDay(int year, int mon, int day, int& outYear, int& outMonth, int& outDay);
    extern void GetNextDayToSelf(int& outYear, int& outMonth, int& outDay);
    extern void GetNextWorkDayToSelf(int& outYear, int& outMonth, int& outDay);
}

#endif