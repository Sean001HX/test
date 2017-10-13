#include "ystruct_define.h"
#include "utility/utility_fun.h"

#include <iomanip>

YDouble::YDouble()
    :val_(0)
{

}

YDouble::YDouble(double val)
    : val_(val)
{

}

bool YDouble::operator>=(const YDouble &rhs) const
{
    return val_ > rhs.val_ || operator==(rhs);
}

bool YDouble::operator>=(double rhs) const
{
    return val_ > rhs || operator==(rhs);
}

bool YDouble::operator>(const YDouble &rhs) const
{
    return val_ > rhs.val_ && !(operator==(rhs));
}

bool YDouble::operator>(double rhs) const
{
    return val_ > rhs && !(operator==(rhs));
}

bool YDouble::operator<=(const YDouble &rhs) const
{
    return val_ < rhs.val_ || operator==(rhs);
}

bool YDouble::operator<=(double rhs) const
{
    return val_ < rhs || operator==(rhs);
}

bool YDouble::operator<(const YDouble &rhs) const
{
    return val_ < rhs.val_ && !(operator==(rhs));
}

bool YDouble::operator<(double rhs) const
{
    return val_ < rhs && !(operator==(rhs));
}

bool YDouble::operator==(const YDouble &rhs) const
{
    return UtilityFun::compareDouble(val_, rhs.val_);
}

bool YDouble::operator==(double val) const
{
    return UtilityFun::compareDouble(val_, val);
}

YDouble& YDouble::operator+=(const YDouble &rhs)
{
    val_ += rhs.val_;
    val_ = UtilityFun::Round(val_, 0.000001);
    return *this;
}

YDouble& YDouble::operator+=(double val)
{
    val_ += val;
    val_ = UtilityFun::Round(val_, 0.000001);
    return *this;
}

YDouble& YDouble::operator-=(const YDouble &rhs)
{
    val_ -= rhs.val_;
    val_ = UtilityFun::Round(val_, 0.000001);
    return *this;
}

YDouble& YDouble::operator-=(double val)
{
    val_ -= val;
    val_ = UtilityFun::Round(val_, 0.000001);
    return *this;
}

YDouble& YDouble::operator=(const YDouble &rhs)
{
    if (this != &rhs)
        val_ = UtilityFun::Round(rhs.val_, 0.000001);

    return *this;
}

YDouble& YDouble::operator=(double val)
{
    val_ = val;
    return *this;
}

YDouble::operator double() const
{
    return val_;
}

const YDouble operator+(const YDouble& lhs, const YDouble& rhs)
{
    return YDouble(lhs) += rhs;
}

const YDouble operator+(const YDouble& lhs, double rhs)
{
    return YDouble(lhs) += rhs;
}

const YDouble operator+(double lhs, const YDouble& rhs)
{
    return YDouble(lhs) += rhs;
}

const YDouble operator-(const YDouble& lhs, const YDouble& rhs)
{
    return YDouble(lhs) -= rhs;
}

const YDouble operator-(const YDouble& lhs, double rhs)
{
    return YDouble(lhs) -= rhs;
}

const YDouble operator-(double lhs, const YDouble& rhs)
{
    return YDouble(lhs) -= rhs;
}

std::ostream& operator<<(std::ostream& out, const YDouble& t)
{
    out << std::setiosflags(std::ios::fixed) << std::setprecision(8) << double(t);
    return out;
}
