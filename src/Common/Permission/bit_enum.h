/*************************************************
Copyright (C), 2017, CCONLY
File name:      bit_enum.h
Author:			XuYC
Version:
Date:
Description:    提供统一的位处理操作,最大处理64位数据
                注: 当max大于等于32时,采用ulonglong;否则采用longlong
                #define _LONGLONG	long long
                #define _ULONGLONG	unsigned long long
                #define _LLONG_MAX	0x7fffffffffffffff
                #define _ULLONG_MAX	0xffffffffffffffff

使用方法:
enum class BitFlags
{
    False=0,
    True,
    FileNotFound,
    Write,
    Read,
    MaxVal
};

template<>
struct EnumTraits<BitFlags>
{
static const BitFlags max = BitFlags::MaxVal;
};

EnumClassBitset<BitFlags, static_cast<typename std::underlying_type<BitFlags>::type>(EnumTraits<BitFlags>::max)> f;
f.set(BitFlags::False);
f.set(BitFlags::True);
f.set(BitFlags::Write);
f.set(BitFlags::FileNotFound);
std::cout << "Is False? " << f.hasPermissions(BitFlags::False) << "\n";
std::cout << "Is True? " << f.hasPermissions(BitFlags::True) << "\n";
std::cout << "Is FileNotFound? " << f.hasPermissions(BitFlags::FileNotFound) << "\n";
std::cout << "Is Write? " << f.hasPermissions(BitFlags::Write) << "\n";
std::cout << "Is Read? " << f.hasPermissions(BitFlags::Read) << "\n";

*************************************************/

#include <bitset>
#include <type_traits>

template<typename T, size_t _Bits>
class EnumClassBitset
{
private:
    std::bitset<_Bits> c;

    typename std::underlying_type<T>::type get_value(T v) const
    {
        return static_cast<typename std::underlying_type<T>::type>(v);
    }

public:
    EnumClassBitset() : c()
    {

    }

    bool hasPermissions(T pos) const
    {
        return c.test(get_value(pos));
    }

    EnumClassBitset& reset(T pos)
    {
        c.reset(get_value(pos));
        return *this;
    }

    EnumClassBitset& set(T pos)
    {
        c.flip(get_value(pos));
        return *this;
    }
};
