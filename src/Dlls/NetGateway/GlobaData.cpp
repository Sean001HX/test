
#include "stdafx.h"
#include "GlobaData.h"

namespace NetGateway
{
	namespace Server
	{
		////////////////////////////////////////////////////////
		CGlobaData * CGlobaData::Instance()
		{
			static CGlobaData _inst;
			return &_inst;
		}
		///////////////////////////////////////////////////////////////
		void CGlobaData::SetNetCallback(CNetCallback *netCallback)
		{
			netCallback_ = netCallback;
		}
		/////////////////////////////////////////////////////////////
		CNetCallback * CGlobaData::Callback()
		{
			return netCallback_;
		}

		////////////////////////////////////////////////////////
		CGlobaData::CGlobaData()
		{

		}
	}
	

}