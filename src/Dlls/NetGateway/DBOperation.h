//  数据库操作类

#pragma once
#ifndef DB_OPERATION_H
#define DB_OPERATION_H

#include "trade_bussness/trade_bussness_struct_def.h"
#include <list>

using namespace TradeBussness;

class CDBOperation
{
public:
	//  return 0 表示成功, 非0 表示失败
	static int GetAllUsers(std::list<UserInfo> &usersInfo);
};

#endif  // DB_OPERATION_H