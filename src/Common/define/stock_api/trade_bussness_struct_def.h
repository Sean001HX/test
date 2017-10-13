

//  业务处理数据结构定义

#ifndef TRADE_BUSSNESS_STRUCT_DEF_H
#define TRADE_BUSSNESS_STRUCT_DEF_H

#define HX_TB_LOGIN_NAME_LEN                 16       //  帐户登录名长度限制
#define HX_TB_ACCOUNT_NAME_LEN               24       //  帐户名长度限制
#define HX_TB_PASSWORD_LEN                   24       //  密码长度限制
#define HX_TB_PHONE_NUMBER_LEN               16       //  电话号码长度
#define HX_TB_ADDRESS_LEN                    24       //  地址长度
#define HX_TB_DATA_TIME_LEN                  24       //  时间日期文本长度

#define HX_TB_LOGIN_NAME_LOW_LIMIT           4        // 登录名最短长度，modify  by xyc 2016.09.20 ctp、cms登录名可能为4位

#define HX_TB_COMM_SHORT_LEN                 8        // 
#define HX_TB_COMM_LEN                       16
#define HX_TB_COMM_LONG_LEN                  32          

#define HX_TB_EXCHANGE_ID_LEN                24       // 交易所编号长度

#define HX_TB_CURRENCY_LEN                   4        //  币种长度
#define HX_TB_ORDERREF_LEN                   40

#define HX_TB_DEFAULT_STOPLOSS_LEVEL          5       //  默认动态止盈止损支持档数

#define HX_TB_ORDER_VALID_MAX				 30000    //挂单有效日

#define HX_TB_RC_MSG_LEN					 128
#define HX_TB_CONTRACT_LEN					 16

#define HX_TB_HARDDISK_ID_LEN                48       // 硬盘序列号编号长度

#define HX_TB_TIME_LEN                       26       // 时间长度

#define HX_TB_LOG_MSG_LEN					 200	  // 日志记录内容
#define HX_TB_FUNCTIONS_MSG_LEN				 64		  // 业务/功能名称

#define HX_TB_POPULARIZE_LINK_LEN            10    //  推广用户链接长度

#endif