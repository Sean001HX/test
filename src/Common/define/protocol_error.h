#ifndef __PROTOCOL_ERROR_H__
#define __PROTOCOL_ERROR_H__

#include "params_declare.h"

namespace AllTrade {
    ///////////////////////////////////////////////////////////////////////////
    //请求提交成功
    const ErrorCodeType Err_Pending                             = -2;
    //未知错误
    const ErrorCodeType Err_Unknown								= -1;
    //成功
    const ErrorCodeType Err_Succeed								= 0;

    ///////////////////////////////////////////////////////////////////////////
    //登录版本不允许
    const ErrorCodeType Err_Login_Version						= 1;
    //登录类型不允许
    const ErrorCodeType Err_Login_Type							= 2;
    //CA登录方式错误
    const ErrorCodeType Err_Login_Ca							= 3;
    //请修改密码登录
    const ErrorCodeType Err_Login_ForcePwd						= 4;
    //登录身份不允许
    const ErrorCodeType Err_Login_Identity						= 5;
    //登录名不存在
    const ErrorCodeType Err_Login_LoginNo						= 6;
    //登录密码错
    const ErrorCodeType Err_Login_Password						= 7;
    //禁止登录
    const ErrorCodeType Err_Login_Forbidden						= 8;
    //登陆数超限
    const ErrorCodeType Err_Login_Count							= 9;
    //第三方认证失败
    const ErrorCodeType Err_Otp									= 10;
    //未连接或者网络错误
    const ErrorCodeType Err_Network_Disconnected				= 11;
    //应答中不包含有效数据
    const ErrorCodeType Err_No_Valid_Data   					= 12;
    //未登陆成功，没有操作权限
    const ErrorCodeType Err_Not_Login   					    = 13;
    //没有权限操作该用户
    const ErrorCodeType Err_No_Such_Client_Rights		        = 14;
    //没有本操作的权限
    const ErrorCodeType Err_No_Oper_Rights		                = 15;
    //初始化数据出错1
    const ErrorCodeType Err_Init_FAIL1		                    = 16;
    //初始化数据出错2
    const ErrorCodeType Err_Init_FAIL2		                    = 17;
    //初始化数据出错3
    const ErrorCodeType Err_Init_FAIL3		                    = 18;
    //未成功初始化
    const ErrorCodeType Err_Init_Unsuccess	                    = 19;
    //认证码已过期
    const ErrorCodeType Err_Cert_Expired	                    = 20;
    //用户已经登录，请断开后再登陆
    const ErrorCodeType Err_User_Has_Logged                     = 21;
    //发送频率过高，请稍后再试
    const ErrorCodeType Err_Req_Too_Much                        = 22;
    //数据查询不完整，请稍后再试
    const ErrorCodeType Err_Qry_Incomplete                      = 23;
	//应用程序ID与认证码不符
	const ErrorCodeType Err_Cert_APPID						    = 24;
	//被强制退出。
	const ErrorCodeType Err_Force_Logout					    = 25;
	//登录名太短
	const ErrorCodeType Err_LoginName_TooShort                  = 26;
	//请求的参数错误
	const ErrorCodeType Err_Req_Parameter                       = 27;
	//


    ///////////////////////////////////////////////////////////////////////////
    //查询合约失败 无此品种
    const ErrorCodeType Err_Contract_Qry						= 101;
	//查询持仓没有返回结束，无法进行下一次查询
	const ErrorCodeType Err_Hold_QryNoEnd						= 102;
	//查询计算参数没有返回结束，无法进行下一次查询
	const ErrorCodeType Err_CountRent_QryNoEnd					= 103;

    ///////////////////////////////////////////////////////////////////////////
    //下单无此合约
    const ErrorCodeType Err_Order_Contract						= 201;
    //上手不存在
    const ErrorCodeType Err_Order_Upper							= 202;
    //此状态不能撤单
    const ErrorCodeType Err_Order_State							= 203;
    //合约禁止交易
    const ErrorCodeType Err_Contract_NoTrade					= 204;
    //合约不在交易时间段
    const ErrorCodeType Err_Contract_ErrTime                    = 205;
    //合约禁止开仓
    const ErrorCodeType Err_Contract_NoOpen						= 206;
    //委托超出最大下单量
    const ErrorCodeType Err_MaxOrderVol							= 207;
    //持仓超出最大数量
    const ErrorCodeType Err_MaxHoldVol							= 208;
    //客户禁止交易
    const ErrorCodeType Err_Client_NoTrade						= 209;
    //客户禁止开仓
    const ErrorCodeType Err_Client_NoOpen						= 210;
    //下单资金不足
    const ErrorCodeType Err_Money_NotEnough						= 211;
    //LME未准备就绪
    const ErrorCodeType Err_LME_Check							= 212;
    //已删除报单不能转移
    const ErrorCodeType Err_CanNotMove_DeletedOrder				= 213;
    //强平单不能撤销
    const ErrorCodeType Err_CanNotDelete_RiskOrder				= 214;
    //客户号不存在
    const ErrorCodeType Err_Order_ClientNoExist					= 215;
    //订单号不正确
    const ErrorCodeType Err_OrderID_InCorrect                   = 216;
	//录入成交数量不合法
	const ErrorCodeType Error_MatchInput_Vol					= 217;
	//录入成交找不到委托
	const ErrorCodeType Error_Order_NoExist						= 218;
	//强平单不能修改
	const ErrorCodeType Error_CanNotModify_RiskOrder			= 219;
	//平仓方式错误
	const ErrorCodeType Error_CoverMode							= 220;
    //下单不在交易时间
    const ErrorCodeType Err_Order_Trade_Time                    = 221;
    //下单委托参数有误
    const ErrorCodeType Err_Order_Param_Error                   = 222;
    //撤单委托参数有误
    const ErrorCodeType Err_CancelOrder_Param_Error             = 223;
    //撤单委托排队超时
    const ErrorCodeType Err_CancelOrder_TimeOut                 = 224;
    //撤单委托对象处于无法撤单状态
    const ErrorCodeType Err_CancelOrder_Cannot_Cancel           = 225;
    //委托状态不允许成交
    const ErrorCodeType Err_OrderStatus_Cannot_Trade            = 226;
    //委托手数大于可平仓手数
    const ErrorCodeType Err_MaxCanCloseVol                      = 227;
    //无法获取行情信息
    const ErrorCodeType Err_No_QuoteInfo                        = 228;

    ///////////////////////////////////////////////////////////////////////////
    //数据库操作错误
    const ErrorCodeType Err_Database							= 301;


    //-----服务器处理错误码
    //登录时服务器版本错误
    const ErrorCodeType	Err_Login_VersionErr				    = 401;		
    //登录时上手号错误                                            
    const ErrorCodeType	Err_Login_UpNOErr					    = 402;		
    //登录时上手客户号错误			                              
    const ErrorCodeType	Err_Login_UpUserErr					    = 403;			
    //交易数据包转换错误                                          
    const ErrorCodeType	Err_Trade_Trans						    = 404;		
    //交易数据包发送错误                                          
    const ErrorCodeType	Err_Trade_Send						    = 405;	
    //上手网关未就绪                                              
    const ErrorCodeType	Err_Trade_APINoReady				    = 406;		
    //上手网关撤单失败                                            
    const ErrorCodeType	Err_Trade_APIFail					    = 407;		
    //系统正在进行强制初始化                                      
    const ErrorCodeType	Err_Trade_Initing					    = 408;		
    //被上手拒绝                                                  
    const ErrorCodeType	Err_Trade_RejectByUpper				    = 409;	
    //市场或品种不许交易                                          
    const ErrorCodeType	Err_Trade_TransWNOFind				    = 410;		
    //报单类型不被支持                                            
    const ErrorCodeType	Err_Trade_InvalidOrderType			    = 411;		
    //价格错误                                                    
    const ErrorCodeType	Err_Trade_PriceErr					    = 412;		
    //报单类型错误                                                
    const ErrorCodeType	Err_Trade_UnknownOrderType			    = 413;		
    //合约错误                                                    
    const ErrorCodeType	Err_Trade_UnknownContract			    = 414;		
    //交易所未就绪                                                
    const ErrorCodeType	Err_Trade_ServerUnConnect			    = 415;		
    //报单不存在
    const ErrorCodeType	Err_Trade_UnknownOrder				    = 416;		
    //报单状态不允许                                              
    const ErrorCodeType	Err_Trade_InvalidState				    = 417;		
    //交易所不支持改单                                            
    const ErrorCodeType	Err_Trade_AmendDisabled				    = 418;		
    //数量不合法                                                  
    const ErrorCodeType	Err_Trade_InvalidVolume				    = 419;		
    //此类型不许修改                                              
    const ErrorCodeType	Err_Trade_InvalidAmendOrderType		    = 420;		
    //账户和用户不匹配                                            
    const ErrorCodeType	Err_Trade_UnknownAccount			    = 421;		
    //错误的方向，买卖不明                                        
    const ErrorCodeType	Err_Trade_ErrDirect					    = 422;		
    //不支持的商品类型                                            
    const ErrorCodeType	Err_Trade_InvalidCommodityType		    = 423;		
    //非法的报单模式                                              
    const ErrorCodeType	Err_Trade_InvalidMode				    = 424;
	//	港交所保单操作类型错误.
	const ErrorCodeType	Err_Trade_InvalidOperType				= 425;

    //前置机返回的错误码
    //版本号不符合前置机要求
    const ErrorCodeType    Err_Frnt_Version                     = 501;
    //身份错误, 前置不允许前置登录
    const ErrorCodeType    Err_Frnt_Identity                    = 502;
    //发送给服务器失败
    const ErrorCodeType    Err_Frnt_SendServer                  = 503;
    //不被支持的命令
    const ErrorCodeType    Err_Frnt_CMDNotAllow                 = 504;
    //客户没有权限
    const ErrorCodeType  Err_Frnt_NORight                       = 505;
    //系统号错误
    const ErrorCodeType    Err_Frnt_SysNOErr                    = 506;
    //未登录无权限
    const ErrorCodeType  Err_Frnt_NOLogin                       = 508;
    //前置登录客户数超限
    const ErrorCodeType  Err_Frnt_ClientFull                    = 509;
    //前置不允许该类型客户登陆
    const ErrorCodeType  Err_Frnt_IsNotClient                   = 510;
    //前置没有准备好
    const ErrorCodeType  Err_Frnt_NoReady                       = 511;
	//前置没所需数据
	const ErrorCodeType  Err_Frnt_NoData				        = 512;
	//客户应用没有授权
	const ErrorCodeType  Err_Frnt_APPNotAllow			        = 513;

    //认证错误信息
    //认证码错误
    const ErrorCodeType  Err_Cert_Incorrect                     = 600;
    //日志文件初始化失败
    const ErrorCodeType  Err_Open_Log_Init_Failed               = 601;
    //日志文件打开失败
    const ErrorCodeType  Err_Open_Log_Failed                    = 602;
	//用户无此权限
	const ErrorCodeType  Error_No_SuchRights			        = 603;
	//委托方式错误
	const ErrorCodeType  Error_No_SuchOrderWay			        = 604;
	//开平标志错误
	const ErrorCodeType  Error_No_SuchOffset			        = 605;


	///////////////////////////////////////////////////////////////////////////
	//动态令牌时间同步失败
	const ErrorCodeType Error_Otp_SyncTime				        = 700;


	//////////////////////////////////////////////////////////////////////////
	//出金入金操作金额错误
	const ErrorCodeType Error_CashOper_Value			        = 800;
	//出金入金审核序列号错误
	const ErrorCodeType Error_CashCheck_SerialID		        = 810;
	//出金入金审核无资金信息
	const ErrorCodeType Error_CashCheck_NoMoneyInfo	            = 811;
	//出金入金审核资金不足
	const ErrorCodeType Error_CashCheck_MoneyNotEnough	        = 812;

    //////////////////////////////////////////////////////////////////////////
    // 用户已存在
    const ErrorCodeType Error_User_Exist                        = 900;
    // 用户不存在
    const ErrorCodeType Error_User_Unexist                      = 901;
    // 用户父级不存在
    const ErrorCodeType Error_User_Parent_Unexist               = 902;
    // 用户创建者不存在
    const ErrorCodeType Error_User_Creator_Unexist              = 903;
    // 用户资金帐户者不存在
    const ErrorCodeType Error_User_Funder_Unexist               = 904;
    // 交易所不存在
    const ErrorCodeType Error_Exchange_Unexist                  = 905;
    // 交易所已存在
    const ErrorCodeType Error_Exchange_Exist                    = 906;
	// 角色已存在
	const ErrorCodeType Error_Role_Exist						= 907;
	// 账户已经绑定角色关系
	const ErrorCodeType Error_RoleUser_Exist					= 908;
	// 角色和业务功能存在关系
	const ErrorCodeType Error_RoleFunctions_Exist				= 909;
    // 融资审核对象不存在
    const ErrorCodeType Error_ApplyMoney_Unexist                = 910;
	// 账户和功能存在关系
	const ErrorCodeType Error_UserAndFunction_Exist				= 911;
    // 新增账户超出账户允许的最大下设层级
    const ErrorCodeType Error_MaxAllowLevel_Over                = 912;
    // 新增账户超出账户允许的最大下设个数
    const ErrorCodeType Error_MaxAllowNum_Over                  = 913;
    // 用户当前状态不允许该操作
    const ErrorCodeType Error_User_Status_Unallow               = 914;
    // 子账户含有持仓
    const ErrorCodeType Error_User_HasPosition                  = 915;
    // 用户已在其他端口登录
    const ErrorCodeType Error_User_Other_Login                  = 916;
    // 用户属性超出权限
    const ErrorCodeType Error_User_Over_PropRights              = 917;
    // 删除帐户含有绑定对象
    const ErrorCodeType Error_User_Delete_HasBind               = 918;
    // 父级账户设置不正确
    const ErrorCodeType Error_User_Parent_Reset                 = 919;
    // 子账户含有资金
    const ErrorCodeType Error_User_HasMoney                     = 920;


    // 账户处于强平,禁止开仓
    const ErrorCodeType Error_User_NoOpen_Force                 = 1001;
    // 账户处于限仓,禁止开仓
    const ErrorCodeType Error_User_NoOpen_Limit                 = 1002;
    // 超过同一股票持仓比例限定,禁止开仓
    const ErrorCodeType Error_User_NoOpen_SameStock             = 1003;
    // 超过创业板持仓比例限定,禁止开仓
    const ErrorCodeType Error_User_NoOpen_Second_Board          = 1004;
    // 禁止买入亏损企业股
    const ErrorCodeType Error_User_NoOpen_LossCorp_Buy          = 1005;
    // 禁止卖出亏损企业股
    const ErrorCodeType Error_User_NoOpen_LossCorp_Sell         = 1006;
    // 禁止交易亏损企业股
    const ErrorCodeType Error_User_NoOpen_LossCorp_Trade        = 1007;
    // 禁止买入涨停股
    const ErrorCodeType Error_User_NoOpen_RiseStop_Buy          = 1008;
    // 禁止卖出涨停股
    const ErrorCodeType Error_User_NoOpen_RiseStop_Sell         = 1009;
    // 禁止交易涨停股
    const ErrorCodeType Error_User_NoOpen_RiseStop_Trade        = 1010;
    // 禁止买入跌停股
    const ErrorCodeType Error_User_NoOpen_FallStop_Buy          = 1011;
    // 禁止卖出跌停股
    const ErrorCodeType Error_User_NoOpen_FallStop_Sell         = 1012;
    // 禁止交易跌停股
    const ErrorCodeType Error_User_NoOpen_FallStop_Trade        = 1013;
    // 禁止买入新股
    const ErrorCodeType Error_User_NoOpen_New_Buy               = 1014;
    // 禁止卖出新股
    const ErrorCodeType Error_User_NoOpen_New_Sell              = 1015;
    // 禁止交易新股
    const ErrorCodeType Error_User_NoOpen_New_Trade             = 1016;
    // 涨停股无法买入
    const ErrorCodeType Error_User_NoOpen_RiseStop              = 1017;
    // 跌停股无法买出
    const ErrorCodeType Error_User_NoClose_FallStop             = 1018;
    // 该委托会导致进入强平线,禁止开仓
    const ErrorCodeType Error_User_Will_NoOpen_Force            = 1019;
    // 该委托会导致进入限仓线,禁止开仓
    const ErrorCodeType Error_User_Will_NoOpen_Limit            = 1020;
}

#endif
