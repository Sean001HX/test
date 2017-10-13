/*
* Purpose: Ϊ�����ṩ��������
*/
#ifndef __UTILITY_FUN_H__
#define __UTILITY_FUN_H__

#include <string>

namespace UtilityFun{
    #define HX_DOUBLE_PRECISE           1e-8  //  double�����ݾ���
    // mixSpace: ��С�䶯��λ
    extern bool compareDouble(double left, double right, double mixSpace = HX_DOUBLE_PRECISE);

    // ��ȡ128λGUID,ASCII��ʾʱΪ32���ַ���4���ָ���
    extern std::string createGUID();

    // ��ȡ��ǰ����,��ʽ:YYYY-MM-DD
    extern std::string getCurrentDate();
    // ��ȡ��ǰʱ��,��ʽ:HH:MM:SS
    extern std::string getCurrentTime();
    // ��ȡ��ǰ����ʱ��,��ʽ:YYYY-MM-DD HH:MM:SS
    extern std::string getCurrentDateTime();
    // ��ȡ��ǰ����,��ʽ:YYYY-MM-DD
    extern std::string getAddDate(int days);
    extern std::string getAddDate(const std::string& d1, int days);
    // ��ȡ��������֮�����ʱ��������,������ȡ
    extern int getDateSpace(const std::string& d1, const std::string& d2);
    extern int getDateTimeSpace(const std::string& dt1, const std::string& dt2);

    extern const size_t get_cpu_count(void);

    //  �ж�ʵ���Ƿ����
    extern bool IsEqual(double left, double right);
    //  �������� ���� base > 0
    extern double Round(double src, double base);
    //  �ɷ�����
    extern bool CanBeDivided(double src, double base);

    //��ȡ��ǰ int date & int time
    extern void GetCurrentIntdateAndIntTime(int& date, int& time);

    extern int GetDaysOfMonth(int nYear, int nMonth);

    //�Ƚ�int date int timeʱ���¾�
    extern bool DateFirstNewerThanSecond(int date1, int time1, int date2, int time2);
    //��ȡʱ��
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