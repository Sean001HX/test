/*************************************************
Copyright (C), 2017, HX Tech Co., Ltd.
File name:      ystruct_define.h
Author:			XuYC
Version:
Date:
Description:    �ṩ�Զ���ͨ�����ݽṹ,ע��:�ýṹ��Ϊ�����ṹ��,���ز�����ʱ��Ҫ����Ч��,������ʱ����Ķ�δ���
*************************************************/

#ifndef __YSTRUCT_DEFINE_H__
#define __YSTRUCT_DEFINE_H__

#include <ostream>

//////////////////////////////////////////////////////////////////////////
// ͨ�����ݽṹ��
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