/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      ystruct_define.h
Author:			XuYC
Version:
Date:
Description:    提供自定义通用数据结构,注意:该结构体为基础结构体,重载操作符时需要考虑效率,避免临时对象的多次创建
*************************************************/

#ifndef __YSTRUCT_DEFINE_H__
#define __YSTRUCT_DEFINE_H__

#include <ostream>

//////////////////////////////////////////////////////////////////////////
// 通用数据结构体
struct YDouble
{
    YDouble();
    YDouble(double val);

    bool operator >= (const YDouble &rhs) const;
    bool operator >= (double rhs) const;
    bool operator > (const YDouble &rhs) const;
    bool operator > (double rhs) const;

    bool operator <= (const YDouble &rhs) const;
    bool operator <= (double rhs) const;
    bool operator < (const YDouble &rhs) const;
    bool operator < (double rhs) const;

    bool operator == (const YDouble &rhs) const;
    bool operator == (double val) const;

    YDouble& operator += (const YDouble &rhs);
    YDouble& operator += (double val);

    YDouble& operator -= (const YDouble &rhs);
    YDouble& operator -= (double val);

    YDouble& operator = (const YDouble &rhs);
    YDouble& operator = (double val);

    operator double() const;

private:
    double val_;
};
const YDouble operator+(const YDouble& lhs, const YDouble& rhs);
const YDouble operator+(const YDouble& lhs, double rhs);
const YDouble operator+(double lhs, const YDouble& rhs);

const YDouble operator-(const YDouble& lhs, const YDouble& rhs);
const YDouble operator-(const YDouble& lhs, double rhs);
const YDouble operator-(double lhs, const YDouble& rhs);

std::ostream& operator << (std::ostream& cout, const YDouble& t);

#endif