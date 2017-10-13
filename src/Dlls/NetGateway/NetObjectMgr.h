#pragma once

//  �������Ӷ������
#ifndef NET_OBJECT_MGR_H
#define NET_OBJECT_MGR_H

#include "net_gateway_macros.h"
#include "NetObject.h"
#include "NetCommHandle.h"

//  ����֮ǰ�޸� MAX_NET_OBJECT_LIMIT ��ֵ �ɸı�����ģ������������������

namespace NetGateway
{
	namespace Server
	{
		class CNetObjectMgr
		{
		public:
			/*************************************************
			Function:       Instance()
			Description:    ��ȡCNetObjectMgr�ĵ�һʵ��
			Input:
			Output:
			Return:			CNetObjectMgr��ָ��
			*************************************************/
			static CNetObjectMgr *Instance();

			/*************************************************
			Function:       AllocNetObject()
			Description:   ����һ�����õ��������
			Input:
			    NetCommHandle *net_comm_handle�� ͨ�ŷ��ʵľ��
			    const char *peer_addrs��         �Զ�ip��ַ "xxx.xxx.xxx.xxx"
			Output:
			Return:		ʧ�ܷ��� NULL�� �ɹ�����ʵ��ָ��
			*************************************************/
			CNetObject *AllocNetObject(NetCommHandle *net_comm_handle, const char *peer_addr);

			/*************************************************
			Function:       CloseConnection()
			Description:    �ر�����
			Input:
			     int connectionID��        �������Ӷ����ID
			     NetCommHandle *netObject���������Ӷ����Handle
			Output:
			Return:
			*************************************************/
			void CloseConnection(int connectionID, NetCommHandle *netObject);
			
			/*************************************************
			Function:       Send()
			Description:    ��������
			Input:
			    int connectionID��          �������Ӷ����ID
			    NetCommHandle *netObject �� �������Ӷ����Handle
			    short netCommand :          �������ӵĹ�����
			    const void *buf :           �������ݻ������ֽ�
			    int bufLen :                �������ֽڳ���
			Output:
			Return:
			*************************************************/
			int Send(int connectionID, NetCommHandle *netObject, short netCommand, const void *buf, int bufLen);

			// ��ȡ�Է�IP
			virtual void GetPeerAddress(int connectionID, NetCommHandle *netObject, char *addressBuf, int bufLen);

			void CheckHeartBeat(unsigned nowTime);
		private:
			CNetObjectMgr();
			//  �������̬����
			CNetObject net_objects_[MAX_NET_OBJECT_LIMIT];

		private:
			long long Hash(NetCommHandle *net_comm_handle);
		};
	}
}



#endif  // NET_OBJECT_MGR_H

