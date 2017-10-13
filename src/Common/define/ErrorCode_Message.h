#ifndef ERRORCOD_EMESSAGE_H
#define ERRORCOD_EMESSAGE_H

#include<QString>
#include "../../Common/define/protocol_error.h"
using namespace AllTrade;

QString getRtnErrorInfo(int errCode)
{
	switch (static_cast<ErrorCodeType>(errCode))
	{
	case Err_Pending:
		return QStringLiteral("已挂起");
	case Err_Unknown:
		return QStringLiteral("未知错误");
	case Err_Succeed:
		return QStringLiteral("成功");

///////////////////////////////////////////////////////////////////////////
	case Err_Login_Version:
		return QStringLiteral("登录版本不允许");
	case Err_Login_Type:
		return QStringLiteral("登录类型不允许");
	case Err_Login_Ca:
		return QStringLiteral("CA登录方式错误");
	case Err_Login_ForcePwd:
		return QStringLiteral("请修改密码登录");
	case Err_Login_Identity:
		return QStringLiteral("登录身份不允许");
	case Err_Login_LoginNo:
		return QStringLiteral("登录名不存在");
	case Err_Login_Password:
		return QStringLiteral("登录密码错");
	case Err_Login_Forbidden:
		return QStringLiteral("禁止登录");
	case Err_Login_Count:
		return QStringLiteral("登陆数超限");
	case Err_Otp:
		return QStringLiteral("第三方认证失败");
	case Err_Network_Disconnected:
		return QStringLiteral("未连接或者网络错误");
	case Err_No_Valid_Data:
		return QStringLiteral("应答中不包含有效数据");
	case Err_Not_Login:
		return QStringLiteral("未登陆成功，没有操作权限");
	case Err_No_Such_Client_Rights:
		return QStringLiteral("没有权限操作该用户");
	case Err_No_Oper_Rights:
		return QStringLiteral("没有本操作的权限");
	case Err_Init_FAIL1:
		return QStringLiteral("初始化数据出错1");
	case Err_Init_FAIL2:
		return QStringLiteral("初始化数据出错2");
	case Err_Init_FAIL3:
		return QStringLiteral("初始化数据出错3");
	case Err_Init_Unsuccess:
		return QStringLiteral("未成功初始化");
	case Err_Cert_Expired:
		return QStringLiteral("认证码已过期");
	case Err_User_Has_Logged:
		return QStringLiteral("用户已经登录，请断开后再登陆");
	case Err_Req_Too_Much:
		return QStringLiteral("发送频率过高，请稍后再试");
	case Err_Qry_Incomplete:
		return QStringLiteral("数据查询不完整，请稍后再试");
	case Err_Cert_APPID:
		return QStringLiteral("应用程序ID与认证码不符");
	case Err_Force_Logout:
		return QStringLiteral("被强制退出");
	case Err_LoginName_TooShort:
		return QStringLiteral("登录名太短");
	case Err_Req_Parameter:
		return QStringLiteral("请求的参数错误");

///////////////////////////////////////////////////////////////////////////
	case Err_Contract_Qry:
		return QStringLiteral("查询合约失败 无此品种");
	case Err_Hold_QryNoEnd:
		return QStringLiteral("查询持仓没有返回结束，无法进行下一次查询");
	case Err_CountRent_QryNoEnd:
		return QStringLiteral("查询计算参数没有返回结束，无法进行下一次查询");

///////////////////////////////////////////////////////////////////////////
	case Err_Order_Contract:
		return QStringLiteral("下单无此合约");
	case Err_Order_Upper:
		return QStringLiteral("上手不存在");
	case Err_Order_State:
		return QStringLiteral("此状态不能撤单");
	case Err_Contract_NoTrade:
		return QStringLiteral("合约禁止交易");
	case Err_Contract_ErrTime:
		return QStringLiteral("合约不在交易时间段");
	case Err_Contract_NoOpen:
		return QStringLiteral("合约禁止开仓");
	case Err_MaxOrderVol:
		return QStringLiteral("委托超出最大下单量");
	case Err_MaxHoldVol:
		return QStringLiteral("持仓超出最大数量");
	case Err_Client_NoTrade:
		return QStringLiteral("客户禁止交易");
	case Err_Client_NoOpen:
		return QStringLiteral("客户禁止开仓");
	case Err_Money_NotEnough:
		return QStringLiteral("下单资金不足");
	case Err_LME_Check:
		return QStringLiteral("LME未准备就绪");
	case Err_CanNotMove_DeletedOrder:
		return QStringLiteral("已删除报单不能转移");
	case Err_CanNotDelete_RiskOrder:
		return QStringLiteral("强平单不能撤销");
	case Err_Order_ClientNoExist:
		return QStringLiteral("客户号不存在");
	case Err_OrderID_InCorrect:
		return QStringLiteral("订单号不正确");
	case Error_MatchInput_Vol:
		return QStringLiteral("录入成交数量不合法");
	case Error_Order_NoExist:
		return QStringLiteral("录入成交找不到委托");
	case Error_CanNotModify_RiskOrder:
		return QStringLiteral("强平单不能修改");
	case Error_CoverMode:
		return QStringLiteral("平仓方式错误");
	case Err_Order_Trade_Time:
		return QStringLiteral("下单不在交易时间");
	case Err_Order_Param_Error:
		return QStringLiteral("下单委托参数有误");
	case Err_CancelOrder_Param_Error:
		return QStringLiteral("撤单委托参数有误");
	case Err_CancelOrder_TimeOut:
		return QStringLiteral("撤单委托排队超时");
	case Err_CancelOrder_Cannot_Cancel:
		return QStringLiteral("撤单委托对象处于无法撤单状态");
	case Err_MaxCanCloseVol:
		return QStringLiteral("委托手数大于可平仓手数");
	case Err_No_QuoteInfo:
		return QStringLiteral("无法获取行情信息");

//////////////////////////////////////////////////////////////////////////

	case Err_Database:
		return QStringLiteral("数据库操作错误");


	case Err_Login_VersionErr:
		return QStringLiteral("登录时服务器版本错误");
	case Err_Login_UpNOErr:
		return QStringLiteral("登录时上手号错误");
	case Err_Login_UpUserErr:
		return QStringLiteral("登录时上手客户号错误");
	case Err_Trade_Trans:
		return QStringLiteral("交易数据包转换错误");
	case Err_Trade_Send:
		return QStringLiteral("交易数据包发送错误");
	case Err_Trade_APINoReady:
		return QStringLiteral("上手网关未就绪");
	case Err_Trade_APIFail:
		return QStringLiteral("上手网关撤单失败");
	case Err_Trade_Initing:
		return QStringLiteral("系统正在进行强制初始化");
	case Err_Trade_RejectByUpper:
		return QStringLiteral("被上手拒绝");
	case Err_Trade_TransWNOFind:
		return QStringLiteral("市场或品种不许交易");
	case Err_Trade_InvalidOrderType:
		return QStringLiteral("报单类型不被支持");
	case Err_Trade_PriceErr:
		return QStringLiteral("价格错误");
	case Err_Trade_UnknownOrderType:
		return QStringLiteral("报单类型错误");
	case Err_Trade_UnknownContract:
		return QStringLiteral("合约错误");
	case Err_Trade_ServerUnConnect:
		return QStringLiteral("交易所未就绪");
	case Err_Trade_UnknownOrder:
		return QStringLiteral("报单不存在");
	case Err_Trade_InvalidState:
		return QStringLiteral("报单状态不允许");
	case Err_Trade_AmendDisabled:
		return QStringLiteral("交易所不支持改单");
	case Err_Trade_InvalidVolume:
		return QStringLiteral("数量不合法");
	case Err_Trade_InvalidAmendOrderType:
		return QStringLiteral("此类型不许修改");
	case Err_Trade_UnknownAccount:
		return QStringLiteral("账户和用户不匹配");
	case Err_Trade_ErrDirect:
		return QStringLiteral("错误的方向，买卖不明");
	case Err_Trade_InvalidCommodityType:
		return QStringLiteral("不支持的商品类型");
	case Err_Trade_InvalidMode:
		return QStringLiteral("非法的报单模式");
	case Err_Trade_InvalidOperType:
		return QStringLiteral("港交所保单操作类型错误");

//////////////////////////////////////////////////////////////////////////
	case Err_Frnt_Version:
		return QStringLiteral("版本号不符合前置机要求");
	case Err_Frnt_Identity:
		return QStringLiteral("身份错误, 前置不允许前置登录");
	case Err_Frnt_SendServer:
		return QStringLiteral("发送给服务器失败");
	case Err_Frnt_CMDNotAllow:
		return QStringLiteral("不被支持的命令");
	case Err_Frnt_NORight:
		return QStringLiteral("客户没有权限");
	case Err_Frnt_SysNOErr:
		return QStringLiteral("系统号错误");
	case Err_Frnt_NOLogin:
		return QStringLiteral("未登录无权限");
	case Err_Frnt_ClientFull:
		return QStringLiteral("前置登录客户数超限");
	case Err_Frnt_IsNotClient:
		return QStringLiteral("前置不允许该类型客户登陆");
	case Err_Frnt_NoReady:
		return QStringLiteral("前置没有准备好");
	case Err_Frnt_NoData:
		return QStringLiteral("前置没所需数据");
	case Err_Frnt_APPNotAllow:
		return QStringLiteral("客户应用没有授权");
//////////////////////////////////////////////////////////////////////////
	case Err_Cert_Incorrect:
		return QStringLiteral("认证码错误");
	case Err_Open_Log_Init_Failed:
		return QStringLiteral("日志文件初始化失败");
	case Err_Open_Log_Failed:
		return QStringLiteral("日志文件打开失败");
	case Error_No_SuchRights:
		return QStringLiteral("用户无此权限");
	case Error_No_SuchOrderWay:
		return QStringLiteral("委托方式错误");
	case Error_No_SuchOffset:
		return QStringLiteral("开平标志错误");
/////////////////////////////////////////////////////////////////////////

	case Error_Otp_SyncTime:
		return QStringLiteral("动态令牌时间同步失败");
/////////////////////////////////////////////////////////////////////////
	case Error_CashOper_Value:
		return QStringLiteral("出金入金操作金额错误");
	case Error_CashCheck_SerialID:
		return QStringLiteral("出金入金审核序列号错误");
	case Error_CashCheck_NoMoneyInfo:
		return QStringLiteral("出金入金审核无资金信息");
	case Error_CashCheck_MoneyNotEnough:
		return QStringLiteral("出金入金审核资金不足");
/////////////////////////////////////////////////////////////////////////
	case Error_User_Exist:
		return QStringLiteral("用户已存在");
	case Error_User_Unexist:
		return QStringLiteral("用户不存在");
	case Error_User_Parent_Unexist:
		return QStringLiteral("用户父级不存在");
	case Error_User_Creator_Unexist:
		return QStringLiteral("用户创建者不存在");
	case Error_User_Funder_Unexist:
		return QStringLiteral("用户资金帐户者不存在");
	case Error_Exchange_Unexist:
		return QStringLiteral("交易所不存在");
	case Error_Exchange_Exist:
		return QStringLiteral("交易所已存在");
	case Error_Role_Exist:
		return QStringLiteral("角色已存在");
	case Error_RoleUser_Exist:
		return QStringLiteral("角色和账户存在关系");
	case Error_RoleFunctions_Exist:
		return QStringLiteral("角色和业务功能存在关系");
	case Error_ApplyMoney_Unexist:
		return QStringLiteral("融资审核对象不存在");
	case Error_UserAndFunction_Exist:
		return QStringLiteral("账户和功能存在关系");
	case Error_MaxAllowLevel_Over:
		return QStringLiteral("新增账户超出账户允许的最大下设层级");
	case Error_MaxAllowNum_Over:
		return QStringLiteral("新增账户超出账户允许的最大下设个数");
	case Error_User_Status_Unallow:
		return QStringLiteral("用户当前状态不允许该操作");
	case Error_User_HasPosition:
		return QStringLiteral("子账户含有持仓");
	case Error_User_Other_Login:
		return QStringLiteral("用户已在其他端口登录");

	case Error_User_Over_PropRights:
		return QStringLiteral("用户属性超出权限");
	case Error_User_Delete_HasBind:
		return QStringLiteral("删除帐户含有绑定对象");
	case Error_User_Parent_Reset:
		return QStringLiteral("父级账户设置不正确");
	case Error_User_HasMoney:
		return QStringLiteral("子账户含有资金");

/////////////////////////////////////////////////////////////////////////////
	case Error_User_NoOpen_Force:
		return QStringLiteral("账户处于强平,禁止开仓");
	case Error_User_NoOpen_Limit:
		return QStringLiteral("账户处于限仓,禁止开仓");
	case  Error_User_NoOpen_SameStock:
		return QStringLiteral("超过同一股票持仓比例限定,禁止开仓");

	case Error_User_NoOpen_Second_Board:
		return QStringLiteral("超过创业板比例限定,禁止开仓");
	case Error_User_NoOpen_LossCorp_Buy:
		return QStringLiteral("禁止买入亏损企业股");
	case  Error_User_NoOpen_LossCorp_Sell:
		return QStringLiteral(" 禁止卖出亏损企业股");

	case Error_User_NoOpen_LossCorp_Trade:
		return QStringLiteral("禁止交易亏损企业股");
	case Error_User_NoOpen_RiseStop_Buy:
		return QStringLiteral("禁止买入涨停股");

	case Error_User_NoOpen_RiseStop_Sell:
		return QStringLiteral("禁止卖出涨停股");
	case Error_User_NoOpen_RiseStop_Trade:
		return QStringLiteral("禁止交易涨停股");
	case  Error_User_NoOpen_FallStop_Buy:
		return QStringLiteral("禁止买入跌停股");

	case Error_User_NoOpen_FallStop_Sell:
		return QStringLiteral("禁止卖出跌停股");
	case Error_User_NoOpen_FallStop_Trade:
		return QStringLiteral("禁止交易跌停股");
	case  Error_User_NoOpen_New_Buy:
		return QStringLiteral(" 禁止买入新股");
	case Error_User_NoOpen_New_Sell:
		return QStringLiteral("禁止卖出新股");
	case  Error_User_NoOpen_New_Trade:
		return QStringLiteral("禁止交易新股");
	case Error_User_NoOpen_RiseStop:
		return QStringLiteral("涨停股无法买入");
	case Error_User_NoClose_FallStop:
		return QStringLiteral("跌停股无法买出");
	case Error_User_Will_NoOpen_Force:
		return QStringLiteral("用户资金达到强平线,禁止开仓");
	case Error_User_Will_NoOpen_Limit:
		return QStringLiteral("用户资金达到限仓线,禁止开仓");
	default:
		break;
	}
	return QStringLiteral("");
}


#endif