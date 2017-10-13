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
	typedef int DepCode;		//营业部代码
	typedef char AccountNo[24];
	typedef char Password[24];
	typedef int OrderType;	//买卖类型
	typedef char ExchangeID[2];
	typedef char OrderNo[24];
	typedef char ErrMsg[64];
	typedef char TimeType[9];

	enum OrderTypeType{
		OrderTypeBuy,				//买入
		OrderTypeSell,				//卖出
		OrderTypeFinancingBuy,		//融资买入
		OrderTypeFinancingSell,		//融券卖出
		OrderTypeBuyReturnBond,		//买券还券
		OrderTypeSellReturnMoney,	//卖券还款
		OrderTypeBondReturnBond,	//现券还券
		OrderTypeError
	};
	typedef int PriceType;	//价格类型
	enum PriceTypeType{
		PriceTypeLimit,		//限价
		PriceTypeMarket_1,	//(市价委托)深圳对方最优价格
		PriceTypeMarket_2,	//(市价委托)深圳本方最优价格
		PriceTypeMarket_3,	//(市价委托)深圳即时成交剩余撤销
		PriceTypeMarket_4,	//(市价委托)上海五档即成剩撤 深圳五档即成剩撤 
		PriceTypeMarket_5,	//(市价委托)深圳全额成交或撤销
		PriceTypeMarket_6,	//(市价委托)上海五档即成转限价
		PriceTypeErr		//错误
	};
	typedef char HolderCode[24];	//股东代码
	typedef char StockCode[10];		//股票代码
	typedef float Price;			//股票价格
	typedef int Quantity;			//委托数量
	typedef char OrderRef[64];		//order ref
	typedef char OrderId[12];	//系统委托ID
	typedef char StockName[24];

	typedef int OrderStatus;
	enum OrderStatusType{
		OrderStatusReceived,		//已报
		OrderStatusCanceled,		//已撤
		OrderStatusPartTraded,		//部分成交
		OrderStatusAllTraded,		//已成
		OrderStatusOther			//其他，目前只测试出已报，已撤，已成
	};


	//////////////////////请求结构体/////////////////
	//向实盘登录请求
	struct LogonInfo{
		IPString ip;
		IPPort port;
		VersionString version;
		DepCode depCode;
		AccountNo accountNo;		//登录账号
		AccountNo tradeAccount;		//交易账号  一般与登录账号相同
		Password loginPassword;		//登录密码
		Password txPassword;		//通讯密码

		LogonInfo()
		{
			memset(this, 0, sizeof(LogonInfo));
		}
	};

	//下单
	struct OrderInfo{
		OrderType orderType;
		PriceType priceType;
		Price price;
		Quantity quantity;
		HolderCode holderCode;	//TC不用关注
		StockCode stockCode;	
		OrderRef orderRef;
		int exchange;	//0深证； 1上海

		OrderInfo()
		{
			memset(this, 0, sizeof(OrderInfo));
		}
	};

	//撤单
    struct CancelOrderInfo{
        ExchangeID exchangeID;	//1上海, 0深证，(招商证券普通账户深证是2)
        OrderNo orderNo;
        StockCode stockCode;

        CancelOrderInfo()
        {
            memset(this, 0, sizeof(CancelOrderInfo));
        }
    };

	//////////////////返回结构体///////////////////

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
		double remainder_;	//资金余额
		double available_;	//可用资金
		double freeze_;		//冻结资金
		double withdraw_;	//可取资金
		double all_;		//总资产
		double worth_;		//最新市值
		//未写入操作数据，句柄，保留信息
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

	//委托信息返回
	struct DLLOrderInfo
	{
		TimeType orderTime_;
		StockCode securityCode_;
		StockName securityName_;
		OrderType direction_;
		OrderStatus status_;
		float orderPrice_;
		int orderVolume_;			//实盘返回为double
		OrderId orderNo_;		//SysOrderId
		float tradePrice_;
		double tradeVolume_;
		PriceType priceType_;
		HolderCode holderCode_;
		OrderRef orderRef_;

		bool flag_;					//标志位，TC不用关注


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
		float percentRate_;  //盈亏比 e.g. -1.023
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

	// 成交信息返回
	struct DLLTradeInfo{
		TimeType tradeTime_;
		StockCode securityCode_;
		StockName securityName_;
		OrderType direction_;
		float tradePrice_;
		int tradeVolume_;	//成交数量
		double turnOver_;		//成交额
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

	//撤单动作返回
    struct DLLOrderCancal
    {
        StockCode stockCode_;
        OrderId orderNo_;
        bool isSuccess_;
        ErrMsg errMsg_;
    };

	//下单动作返回
	struct DLLOrderInsert
	{
        StockCode stockCode_;
        OrderRef orderRef_;
		OrderId orderNo_;
		bool isSuccess_;
		ErrMsg errMsg_;
	};


	//实盘状态更新信息
	struct RealNetStatus
	{
		bool isConnect_;
		ErrMsg errMsg_;
	};

	//api登录到TC的结构体，目前只判断账户名（登录名）
	struct LoginToTc
	{
		AccountNo loginName_;
		Password password_;
	};

}// StockDLL



#endif //STOCK_DLL_STRUCT_H_