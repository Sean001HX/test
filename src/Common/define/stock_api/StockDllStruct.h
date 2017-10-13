#ifndef STOCK_DLL_STRUCT_H_
#define STOCK_DLL_STRUCT_H_

#include <string>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace StockDLL{

	typedef char IPString[16];
	typedef int IPPort;
	typedef char VersionString[8];
	typedef int DepCode;		//Ӫҵ������
	typedef char AccountNo[24];
	typedef char Password[24];
	typedef int OrderType;	//��������
	typedef char ExchangeID[2];
	typedef char OrderNo[24];
	typedef char ErrMsg[64];
	typedef char TimeType[9];

	enum OrderTypeType{
		OrderTypeBuy,				//����
		OrderTypeSell,				//����
		OrderTypeFinancingBuy,		//��������
		OrderTypeFinancingSell,		//��ȯ����
		OrderTypeBuyReturnBond,		//��ȯ��ȯ
		OrderTypeSellReturnMoney,	//��ȯ����
		OrderTypeBondReturnBond,	//��ȯ��ȯ
		OrderTypeError
	};
	typedef int PriceType;	//�۸�����
	enum PriceTypeType{
		PriceTypeLimit,		//�޼�
		PriceTypeMarket_1,	//(�м�ί��)���ڶԷ����ż۸�
		PriceTypeMarket_2,	//(�м�ί��)���ڱ������ż۸�
		PriceTypeMarket_3,	//(�м�ί��)���ڼ�ʱ�ɽ�ʣ�೷��
		PriceTypeMarket_4,	//(�м�ί��)�Ϻ��嵵����ʣ�� �����嵵����ʣ�� 
		PriceTypeMarket_5,	//(�м�ί��)����ȫ��ɽ�����
		PriceTypeMarket_6,	//(�м�ί��)�Ϻ��嵵����ת�޼�
		PriceTypeErr		//����
	};
	typedef char HolderCode[24];	//�ɶ�����
	typedef char StockCode[10];		//��Ʊ����
	typedef float Price;			//��Ʊ�۸�
	typedef int Quantity;			//ί������
	typedef char OrderRef[64];		//order ref
	typedef char OrderId[12];	//ϵͳί��ID
	typedef char StockName[24];

	typedef int OrderStatus;
	enum OrderStatusType{
		OrderStatusReceived,		//�ѱ�
		OrderStatusCanceled,		//�ѳ�
		OrderStatusPartTraded,		//���ֳɽ�
		OrderStatusAllTraded,		//�ѳ�
		OrderStatusOther			//������Ŀǰֻ���Գ��ѱ����ѳ����ѳ�
	};


	//////////////////////����ṹ��/////////////////
	//��ʵ�̵�¼����
	struct LogonInfo{
		IPString ip;
		IPPort port;
		VersionString version;
		DepCode depCode;
		AccountNo accountNo;		//��¼�˺�
		AccountNo tradeAccount;		//�����˺�  һ�����¼�˺���ͬ
		Password loginPassword;		//��¼����
		Password txPassword;		//ͨѶ����

		LogonInfo()
		{
			memset(this, 0, sizeof(LogonInfo));
		}
	};

	//�µ�
	struct OrderInfo{
		OrderType orderType;
		PriceType priceType;
		Price price;
		Quantity quantity;
		HolderCode holderCode;	//TC���ù�ע
		StockCode stockCode;	
		OrderRef orderRef;
		int exchange;	//0��֤�� 1�Ϻ�

		OrderInfo()
		{
			memset(this, 0, sizeof(OrderInfo));
		}
	};

	//����
    struct CancelOrderInfo{
        ExchangeID exchangeID;	//1�Ϻ�, 0��֤��(����֤ȯ��ͨ�˻���֤��2)
        OrderNo orderNo;
        StockCode stockCode;

        CancelOrderInfo()
        {
            memset(this, 0, sizeof(CancelOrderInfo));
        }
    };

	//////////////////���ؽṹ��///////////////////

	//
	struct DLLLogon
	{
		AccountNo accountNo;
		bool isSuccess;
		ErrMsg errMsg;
	};

	struct DLLMoneyInfo
	{
		int currency_;		//0 CNY
		double remainder_;	//�ʽ����
		double available_;	//�����ʽ�
		double freeze_;		//�����ʽ�
		double withdraw_;	//��ȡ�ʽ�
		double all_;		//���ʲ�
		double worth_;		//������ֵ
		//δд��������ݣ������������Ϣ
		DLLMoneyInfo()
		{
			memset(this, 0, sizeof(*this));
		}

		//test
		void show()
		{
			std::cout << std::setiosflags(std::ios::fixed) << std::setprecision(8);
			std::cout << currency_ << " " << remainder_ << " " << available_ << " " << freeze_ << " " << withdraw_ << " ";
			std::cout << all_ << " " << worth_ << std::endl;
		}
	};

	//ί����Ϣ����
	struct DLLOrderInfo
	{
		TimeType orderTime_;
		StockCode securityCode_;
		StockName securityName_;
		OrderType direction_;
		OrderStatus status_;
		float orderPrice_;
		int orderVolume_;			//ʵ�̷���Ϊdouble
		OrderId orderNo_;		//SysOrderId
		float tradePrice_;
		double tradeVolume_;
		PriceType priceType_;
		HolderCode holderCode_;
		OrderRef orderRef_;

		bool flag_;					//��־λ��TC���ù�ע


		DLLOrderInfo()
		{
			memset(this, 0, sizeof(*this));
			flag_ = true;
		}

		//test
		void show()
		{
			std::cout << orderTime_ << "\t" << securityCode_ << "\t" << securityName_ << "\t" << direction_ << "\t" << status_ << "\t";
			std::cout << orderPrice_ << "\t" << orderVolume_ << "\t" << orderNo_ << "\t" << tradePrice_ << "\t" << tradeVolume_ << "\t";
			std::cout << priceType_ << "\t" << holderCode_ << std::endl;
		}
	};

	struct DLLPositionInfo{
		StockCode securityCode_;
		StockName securityName_;
		int positionVolume_;
		int canBeSellVolume_;
		float costPrice_;
		float currentPrice_;
		double lastWorth_;
		double profitLoss_;
		float percentRate_;  //ӯ���� e.g. -1.023
		HolderCode holderCode_;

		DLLPositionInfo(){
			memset(this, 0, sizeof(*this));
		}

		//test
		void show()
		{
			std::cout << securityCode_ << "\t" << securityName_ << "\t" << positionVolume_ << "\t" << canBeSellVolume_ << "\t" << costPrice_ << "\t";
			std::cout << currentPrice_ << "\t" << lastWorth_ << "\t" << profitLoss_ << "\t" << percentRate_ << "\t" << holderCode_ << std::endl;
		}
	};

	// �ɽ���Ϣ����
	struct DLLTradeInfo{
		TimeType tradeTime_;
		StockCode securityCode_;
		StockName securityName_;
		OrderType direction_;
		float tradePrice_;
		int tradeVolume_;	//�ɽ�����
		double turnOver_;		//�ɽ���
		OrderId tradeNo_;
		OrderId orderNo_;	//sysOrderId
		HolderCode holderCode_;

		DLLTradeInfo(){
			memset(this, 0, sizeof(*this));
		}

		//test
		void show()
		{
			std::cout << tradeTime_ << "\t" << securityCode_ << "\t" << securityName_ << "\t" << direction_ << "\t" << tradePrice_ << "\t";
			std::cout << tradeVolume_ << "\t" << turnOver_ << "\t" << tradeNo_ << "\t" << orderNo_ << "\t" << holderCode_ << std::endl;
		}
	};

	//������������
    struct DLLOrderCancal
    {
        StockCode stockCode_;
        OrderId orderNo_;
        bool isSuccess_;
        ErrMsg errMsg_;
    };

	//�µ���������
	struct DLLOrderInsert
	{
        StockCode stockCode_;
        OrderRef orderRef_;
		OrderId orderNo_;
		bool isSuccess_;
		ErrMsg errMsg_;
	};


	//ʵ��״̬������Ϣ
	struct RealNetStatus
	{
		bool isConnect_;
		ErrMsg errMsg_;
	};

	//api��¼��TC�Ľṹ�壬Ŀǰֻ�ж��˻�������¼����
	struct LoginToTc
	{
		AccountNo loginName_;
		Password password_;
	};

}// StockDLL



#endif //STOCK_DLL_STRUCT_H_