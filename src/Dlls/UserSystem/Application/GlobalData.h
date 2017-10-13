#pragma once
#include "utility/instance.h"
#include"define/struct_base.h"
#include"define/struct_declare.h"
#include"hx_mutex.h"
namespace AllTrade
{
	class GlobalData
		:public CommonTools::instance_unshared<GlobalData>
	{
	public:
		GlobalData();
		~GlobalData();
		bool Checkparams(UserInfoPtr& userInfo);

	};

}

