#ifndef  TCAS_DEF_H
#define  TCAS_DEF_H

enum
{
	////////////////////////////////////////////////////API service��ص�����Э����///////////////////////////////////////////////////////
	NET_AS_BEGIN = 0x1000,

	NET_AS_LOGIN,					//api service��TC��¼
	NET_AS_PUSH_QUOTATION,			//api service��TC��������
	NET_AS_NET_STATUS,				//api service��TC��֪�Լ�������״̬
	NET_AS_REGISTER_QUOTATION,		//ע������
	NET_AS_UNREGISTER_QUOTATION,	//��ע������
	NET_AS_QUERY_QUOTATION,			//��ѯ����
	NET_AS_START_QUOTATION,			//��������
	NET_AS_PLACE_ORDER,				//�µ�
	NET_AS_PLACE_ORDER_RSP_STATUS,	//����״̬
	NET_AS_PLACE_ORDER_RSP_ORDER,   //������Ϣ
	NET_AS_PLACE_ORDER_RSP_TRADE,	//�ɽ���Ϣ
	NET_AS_CANCEL_ORDER,			//����
	NET_AS_QUERY_ORDER,				//�鵥
	NET_AS_QUERY_POSITION,			//��ֲ�
	NET_AS_NOTIFY_ASYNC_ORDER_RECORD,      //  ��ѯί�м�¼
	NET_AS_NOTIFY_ASYNC_TRADE_RECORD,      //  ��ѯ�ɽ���¼

	NET_AS_END = 0x1F00,
	////////////////////////////////////////////////////API service��ص�����Э����///////////////////////////////////////////////////////
};

#endif
