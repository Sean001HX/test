//  ���ݿ������

#pragma once
#ifndef DB_OPERATION_H
#define DB_OPERATION_H

#include "trade_bussness/trade_bussness_struct_def.h"
#include <list>

using namespace TradeBussness;

class CDBOperation
{
public:
	//  return 0 ��ʾ�ɹ�, ��0 ��ʾʧ��
	static int GetAllUsers(std::list<UserInfo> &usersInfo);
};

#endif  // DB_OPERATION_H