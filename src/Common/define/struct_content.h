#ifndef _STRUCT_CONTENT_H
#define _STRUCT_CONTENT_H

// 包头  // 命令码 cmdcode
// 内容【【（mc）来源】，(tc)【错误码】，内容】  content
// 校验码(暂留)
// 包尾  §END§

#define	CMDCODE					"cmdcode"				// 命令码
#define	RESOURCE				"resource"				// 来源mc/pc...
#define	ERRCODE					"errcode"				// 错误码
#define	CONTENT					"content"				// 发送内容
#define	REQNUMBER				"reqnumber"				// 请求序号

////////// 结构体字段 ///////////
#define	IPADDRESS				"ipaddress"				// 地址
#define	IPPORT					"ipport"				// 端口
#define	LOGINNAME				"loginname"				// 登录名
#define	CREATELOGINNAME			"createloginname"		// 创建者登录名
#define	PASSWORD				"password"				// 密码
#define	OLDPASSWORD				"old_password"			// 原始密码
#define	NEWPASSWORD				"new_password"			// 新密码
#define	ACCOUNTNAME				"accountname"			// 账户名
#define	TELNO					"telno"					// 手机号
#define	SERIALNO				"serialno"				// 序号
#define	ROOTMANAGERORNOT		"rootmanagerornot"		// 根账户下管理员(true是，fasle不是)
#define	BINDFUNDLOGINNAME		"bindfundloginname"		// 机构绑定的资金账户


#define	COMMISSIONRATE			"commissionrate"		// 佣金比例
#define	PROCOMMRATE				"procommrate"			// 分成比例
#define	MATCHFEERATE			"matchfeerate"			// 撮合费比例

#define	ACCOUNTPROP			    "acc_prop"		        // 账户属性,交易员/管理员
#define	ACCOUNTSTATUS			"acc_status"			// 账户状态
#define	APPROVALSTATUS			"approval_status"		// 审核状态
#define	ACCOUNTTYPE			    "acc_type"		        // 账户类型,模拟/实盘
#define	APPROVALLOGINNAME		"approvalloginname"		// 审核者登录名
#define	OPERATIONLOGINNAME		"operationloginname"	// 操作者登录名

#define	POPULARLINK				"popularlink"			// 推广链接
#define	QRCODE					"QRcode"				// 二维码
#define	ROLESNAME				"rolesname"				// 角色名
#define	ROLEID					"roleid"				// 角色id
#define	OPROLEID				"oproleid"				// 操作角色id
#define	ROLETYPE				"roletype"				// 角色类型
#define	FUNCTIONID				"functionid"			// 功能id
#define	USERID					"userid"				// 用户id
#define	INFOMATCHFEE			"infomatchfee"			// 信息撮合费
#define	COUNTERFEE				"counterfee"			// 手续费
#define	SUMCOMMISSION			"sumcommission"			// 累计佣金
#define	COMMISSIONCHANGE		"commissionchange"		// 佣金变动
#define	COMMISSIONSOURCE		"commissionsource"		// 佣金来源
#define	CHANGETIME				"changetime"			// 变动时间
#define	CHANGETYPE				"changetype"			// 变动类型
#define CHANGEREASON            "changereason"          // 变动理由
#define	EARNINGSBALANCE			"earningsbalance"		// 审核拒绝
#define	SUMLEVELFEE				"sumlevelfee"			// 盈利余额
#define	PROCOMMCHANGE			"procommchange"			// 分成变动
#define	PROCOMMSUM				"procommsum"			// 累计分成
#define	PROCOMMSOURCE		    "procommsource"		    // 分成来源

#define	INFERIORFUND			"inferiorfund"			// 劣后资金
#define	PRIORITYFUND			"priorityfund"			// 优先资金
#define	UPPERFUNDNAME			"upperfundname"			// 上级资金账户
#define	UPPERMANAGER			"uppermanager"			// 所属上线
#define	WARNINGLINE				"warningline"			// 警告线
#define	FORCELINE				"forceline"				// 强平线
#define	LIMITLINE				"limitline"				// 限仓线
#define	LEVERAGERATE			"leveragerate"			// 杠杆比例
#define	BUSINESSTYPE			"businesstype"			// 业务类型,出入金方式
#define	AMOUNTMONEY				"amountmoney"			// 出入金金额

#define	CHANGEMONEY				"changemoney"			// 资金流水变动金额
#define	FUNDSERIALID			"fundserialId"			// 资金流水变动金额

#define	BBLACK				    "bBlack"				// 是否为黑名单

#define STOCKAREA               "stock_area"			// 股票所属区域,如A股/B股/...
#define STOCKPLATEAREA          "stock_plate_area"		// 股票所属板块区域,如主板/创业板/中小板...
#define	REMARKSINFO				"remarksinfo"			// 备注信息
#define	STOCKCODE				"stockcode"				// 股票代码
#define	STOCKNAME				"stockname"				// 股票名称
#define	POSITIONPRICE			"positionprice"			// 持仓价格
#define	POSITIONQTY 			"positionqty"			// 持仓数量
#define	ISSELLQTY				"issellqty"				// 可卖数量
#define FROZENNUMBER            "frozennumber"          // 冻结数量
#define	TOTALSHARES				"total_shares"		    // 总股票

#define	POSITIONCOST			"positioncost"			// 持仓成本
#define	FLOATPRICE				"floatprice"			// 浮动盈亏
#define	OPENTIME				"opentime"				// 开仓时间
#define	DEALNO					"dealno"				// 成交编号
#define	TRADEDIR				"tradedir"				// 交易方向
#define	DEALPRICE				"dealprice"				// 成交价格
#define	DEALQTY					"dealqty"				// 成交数量
#define	DEALTIME				"dealtime"				// 成交时间
#define	STAMPFEE				"stampfee"				// 印花费
#define	TRANSFERFEE				"transferfee"			// 过户费
#define	SECURITIESCOMPANY		"securitiescompany"		// 证券公司
#define	FUNDBALANCE				"fundbalance"			// 资金余额
#define	REGDATE					"regdate"				// 注册日期
#define	LOGINIP					"loginip"				// 登录ip	
#define	LOGINTIME				"logintime"				// 登陆时间
#define	MACADDRESS				"macaddress"			// 登录地址
#define	STAMPFEERATE			"stampfeerate"			// 印花税比例
#define	TRANSFERTAXRATE			"transfertaxrate"		// 过户税比例
#define	ONCELOWESTFEE			"oncelowestfee"			// 每笔最低费用
#define	MATCHFEERATERATE		"matchfeeraterate"		// 信息撮合费
#define	STATUS					"status"				// 状态
#define	RISKPROJECT				"riskproject"			// 风控项目
#define	OPERATIONTYPE			"operationtype"			// 操作类型
#define	RISKEXPLAIN				"riskexplain"			// 风控说明
#define	SWITCHFLAG				"switchflag"			// 开关
#define	POSITIONRATE			"positionrate"			// 持仓比例
#define	ILLUSTRATE				"illustrate"			// 说明
#define	TRADEAMOUNT				"tradeamount"			// 成交金额
#define	TOTALASSETS				"totalassets"			// 总资产
#define	OPENCOST				"opencost"				// 开仓成本
#define	POSITIONMARKETVALUE	    "positionmarketvalue"	// 持仓市值
#define	AVAILABLEFUNDS			"availablefunds"		// 可用资金
#define AVAILABLEGETFUNDS       "availablegetfunds"     // 可取资金
#define	SELFONLYFUND			"selfonlyfund"			// 自有资金净值

#define	HAPPENAMOUNT			"happenamount"			// 发生金额
#define	SECURITIESCODE			"securitiescode"		// 证券代码
#define	SECURITIESNAME			"securitiesname"		// 证券名称
#define	DEALAVGPRICE			"dealavgprice"			// 成交均价
#define	STOCKLEFTAMOUNT			"stockleftamount"		// 股票余额
#define	COMMISSION				"commission"			// 佣金
#define	SUMPLRATE				"sumplrate"				// 总盈亏率
#define	WARNINGTYPE				"warningtype"			// 预警类型
#define	WARNINGTIME				"warningtime"			// 预警时间
#define	WARNINGTEXT				"warningtext"			// 预警内容
#define	ORDERSTATUS				"orderstatus"			// 订单状态
#define	INMONEYFUND				"inmoneyfund"			// 入金资金
#define	BANKOPNENAME			"bankopenname"			// 银行开户名
#define	BANKNAME				"bankname"				// 银行名称	
#define	BANKCARD				"bankcard"				// 银行卡号
#define	COMMITIME				"commitime"				// 提交时间
#define	ISAPPROVAL				"isapproval"			// 是否审核
#define	APPROVALTIME			"approvaltime"			// 审核时间
#define	OUTMONEYFUND			"outmoneyfund"			// 出金金额
#define	ORDERPICE				"orderpice"				// 委托价格
#define	ORDERTYPE				"ordertype"				// 委托类型
#define	ORDERVOLUME				"ordervolume"			// 委托手数
#define	ORDERID					"orderid"				// 委托id
#define	ORDERSTREAM				"orderstream"			// 委托流号
#define	ORDERDERECTION			"orderderection"		// 委托方向
#define	ORDERMODE				"ordermode"			    // 委托模式
#define	ORDERREF				"orderref"				// 委托编号
#define ORDERTIME               "ordertime"             // 委托时间
#define ORDERLASTUPDATETIME     "updateTime"            // 最后更新时间
#define	CURRENCYRATE			"currency_rate"			// 币种汇率
#define CANCELORDERNUMBER       "cancelvolume"          // 撤单数量
#define FROZENFUND              "frozenfund"            // 冻结资金
#define FUNDCHANGEVALUE         "fundchangevalue"       // 资金变动
#define AMPLITUDE               "Amplitude"             // 振幅
#define QUANTITYRATIO           "quantityratio"         // 量比
#define APPINTRATIO_            "appintRatio_"          // 委比
#define CHANGEHAND              "changeHand"            // 换手
#define DATETIME                "date_time"             // 时间信息
#define RISKType                "risk_type"             // 风控类型
#define RISKTEXT                "risk_text"             // 风控内容
#define ALLTOTALVALUE           "allTotalValue"         // 总市值
#define BUSSNESSID              "bussnessID"            // 业务Id
#define BUSSNESSNAME            "bussnessName"          // 业务名称
#define XSHG                    "XSHG"                  // 上证
#define XSHE                    "XSHE"                  // 沪深
#define NAVIGATIONID            "NavigationID"          // 导航Id
#define FUNCTIONNAME            "FunctionName"          // 功能名称
#define FINACEMONEY             "finace_money"          // 申请融资资金
#define QRYSTARTDATETIME        "start_time"            // 查询历史相关数据的起始时间
#define QRYENDDATETIME          "end_time"              // 查询历史相关数据的终止时间
#define BLAST                   "bLast"                 // 是否为查询返回最后一条数据
//   股票行情字段
#define SUBSCRIBETYPE           "Type"                  // 订阅类型 0为订阅，1为反订阅
#define EXCHANGECD              "ExchangeCD"            // 交易所
#define TICKERS                 "Tickers"               // 股票代码
#define TICKER                  "Ticker"                // 股票代码
#define SHORTNM                 "ShortNM"               // 股票名称
#define CHANGEPCT               "ChangePct"             // 涨幅
#define LASTPRICE               "LastPrice"             // 最新价
#define CHANGE                  "Change"                // 涨跌
#define NOWVOLUME               "nowvolume"             // 现手
#define ALLVOLUME               "allvolume"             // 总手
#define PREVCLOSEPRICE          "PrevClosePrice"        // 昨收
#define OPENPRICE               "OpenPrice"             // 开盘
#define HIGHPRICE               "HighPrice"             // 最高
#define LOWPRICE                "LowPrice"              // 最低
#define TRADEMONEY              "Value"                 // 成交额
#define TRADEVOLUME             "Volume"                // 成交手数
#define QUOTATIONDATE           "quotationDate "        // 行情日期
#define QUOTATIONTIME           "quotationtime"         // 行情时间
#define CURRENTTIME             "CurrentTime"           // 当前时间
#define QUOTATIONS              "Quotations"            // 行情为订阅时，Quotations有值，Quotation为空
#define QUOTATION               "Quotation"             // 行情为订阅时，Quotation有值，Quotations为空
#define SUSPENSION              "Suspension"            // 停牌标记 1: 停牌 0: 未停牌
#define SENDTYPE                "SendType"              // 0为订阅时 返回订阅股票返回的相关详情数据,1为正常推送的消息
#define ISTICKER                "IsTicker"              // 0表示股票,1表示指数

#define ASKBOOKVOLUME1          "AskBook_volume1"		// 卖一手数量
#define ASKBOOKVOLUME2          "AskBook_volume2"		// 卖二手数量
#define ASKBOOKVOLUME3          "AskBook_volume3"		// 卖三手数量
#define ASKBOOKVOLUME4			"AskBook_volume4"		// 卖四手数量
#define ASKBOOKVOLUME5			"AskBook_volume5"		// 卖五手数量
#define BIDBOOKVOLUME1          "BidBook_volume1"		// 买一手数量
#define BIDBOOKVOLUME2          "BidBook_volume2"		// 买二手数量
#define BIDBOOKVOLUME3			"BidBook_volume3"		// 买三手数量
#define BIDBOOKVOLUME4			"BidBook_volume4"		// 买四手数量
#define BIDBOOKVOLUME5			"BidBook_volume5"		// 买五手数量

#define	ASKBOOKPRICE1           "AskBook_price1"		// 卖一手价格
#define	ASKBOOKPRICE2           "AskBook_price2"		// 卖二手价格
#define	ASKBOOKPRICE3           "AskBook_price3"		// 卖三手价格
#define	ASKBOOKPRICE4  		    "AskBook_price4"		// 卖四手价格
#define	ASKBOOKPRICE5  			"AskBook_price5"		// 卖五手价格

#define	BIDBOOKPRICE1           "BidBook_price1"		// 买一手价格
#define	BIDBOOKPRICE2           "BidBook_price2"		// 买二手价格
#define	BIDBOOKPRICE3			"BidBook_price3"		// 买三手价格
#define	BIDBOOKPRICE4  			"BidBook_price4"		// 买四手价格
#define	BIDBOOKPRICE5  			"BidBook_price5"		// 买五手价格

// 指数字段
#define INDEXID                  "IndexID"				// 指数ID
#define INDEXNAME                "IndexName"			// 指数名称
#define PRECLOSEINDEX            "PreCloseIndex"		// 昨收价
#define OPENINDEX                "OpenIndex"			// 开盘价
#define TURNOVER                 "Turnover"				// 成交额
#define HIGHINDEX                "HighIndex"			// 最高价
#define LOWINDEX                 "LowIndex"				// 最低价
#define LASTINDEX                "LastIndex"			// 最新价
#define TRADVOLUME               "TradVolume"			// 成交手数
#define CLOSEINDEX               "CloseIndex"			// 
#define COMPOSITE                "Composite"			// 
#define COMPOSITES               "Composites"			// 
#define UPSANDDOWNS              "UpsAndDowns"			//  涨跌幅

#define SUMMARGINSET			 "summarginset"			// 总融资数量
#define LEFTMARGINSET			 "leftmarginset"		// 剩余融资数量
#define INTEREST				 "interest"				// 利息比例
#define SUMINTEREST				 "suminterest"			// 累计利息
#define INTERESTSOURCE			 "interestsource"		// 利息变动来源
#define COMMODITYTYPE			 "commoditytype"		// 商品类型

#endif