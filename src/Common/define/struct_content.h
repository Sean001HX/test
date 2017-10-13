#ifndef _STRUCT_CONTENT_H
#define _STRUCT_CONTENT_H

// ��ͷ  // ������ cmdcode
// ���ݡ�����mc����Դ����(tc)�������롿�����ݡ�  content
// У����(����)
// ��β  ��END��

#define	CMDCODE					"cmdcode"				// ������
#define	RESOURCE				"resource"				// ��Դmc/pc...
#define	ERRCODE					"errcode"				// ������
#define	CONTENT					"content"				// ��������
#define	REQNUMBER				"reqnumber"				// �������

////////// �ṹ���ֶ� ///////////
#define	IPADDRESS				"ipaddress"				// ��ַ
#define	IPPORT					"ipport"				// �˿�
#define	LOGINNAME				"loginname"				// ��¼��
#define	CREATELOGINNAME			"createloginname"		// �����ߵ�¼��
#define	PASSWORD				"password"				// ����
#define	OLDPASSWORD				"old_password"			// ԭʼ����
#define	NEWPASSWORD				"new_password"			// ������
#define	ACCOUNTNAME				"accountname"			// �˻���
#define	TELNO					"telno"					// �ֻ���
#define	SERIALNO				"serialno"				// ���
#define	ROOTMANAGERORNOT		"rootmanagerornot"		// ���˻��¹���Ա(true�ǣ�fasle����)
#define	BINDFUNDLOGINNAME		"bindfundloginname"		// �����󶨵��ʽ��˻�


#define	COMMISSIONRATE			"commissionrate"		// Ӷ�����
#define	PROCOMMRATE				"procommrate"			// �ֳɱ���
#define	MATCHFEERATE			"matchfeerate"			// ��Ϸѱ���

#define	ACCOUNTPROP			    "acc_prop"		        // �˻�����,����Ա/����Ա
#define	ACCOUNTSTATUS			"acc_status"			// �˻�״̬
#define	APPROVALSTATUS			"approval_status"		// ���״̬
#define	ACCOUNTTYPE			    "acc_type"		        // �˻�����,ģ��/ʵ��
#define	APPROVALLOGINNAME		"approvalloginname"		// ����ߵ�¼��
#define	OPERATIONLOGINNAME		"operationloginname"	// �����ߵ�¼��

#define	POPULARLINK				"popularlink"			// �ƹ�����
#define	QRCODE					"QRcode"				// ��ά��
#define	ROLESNAME				"rolesname"				// ��ɫ��
#define	ROLEID					"roleid"				// ��ɫid
#define	OPROLEID				"oproleid"				// ������ɫid
#define	ROLETYPE				"roletype"				// ��ɫ����
#define	FUNCTIONID				"functionid"			// ����id
#define	USERID					"userid"				// �û�id
#define	INFOMATCHFEE			"infomatchfee"			// ��Ϣ��Ϸ�
#define	COUNTERFEE				"counterfee"			// ������
#define	SUMCOMMISSION			"sumcommission"			// �ۼ�Ӷ��
#define	COMMISSIONCHANGE		"commissionchange"		// Ӷ��䶯
#define	COMMISSIONSOURCE		"commissionsource"		// Ӷ����Դ
#define	CHANGETIME				"changetime"			// �䶯ʱ��
#define	CHANGETYPE				"changetype"			// �䶯����
#define CHANGEREASON            "changereason"          // �䶯����
#define	EARNINGSBALANCE			"earningsbalance"		// ��˾ܾ�
#define	SUMLEVELFEE				"sumlevelfee"			// ӯ�����
#define	PROCOMMCHANGE			"procommchange"			// �ֳɱ䶯
#define	PROCOMMSUM				"procommsum"			// �ۼƷֳ�
#define	PROCOMMSOURCE		    "procommsource"		    // �ֳ���Դ

#define	INFERIORFUND			"inferiorfund"			// �Ӻ��ʽ�
#define	PRIORITYFUND			"priorityfund"			// �����ʽ�
#define	UPPERFUNDNAME			"upperfundname"			// �ϼ��ʽ��˻�
#define	UPPERMANAGER			"uppermanager"			// ��������
#define	WARNINGLINE				"warningline"			// ������
#define	FORCELINE				"forceline"				// ǿƽ��
#define	LIMITLINE				"limitline"				// �޲���
#define	LEVERAGERATE			"leveragerate"			// �ܸ˱���
#define	BUSINESSTYPE			"businesstype"			// ҵ������,�����ʽ
#define	AMOUNTMONEY				"amountmoney"			// �������

#define	CHANGEMONEY				"changemoney"			// �ʽ���ˮ�䶯���
#define	FUNDSERIALID			"fundserialId"			// �ʽ���ˮ�䶯���

#define	BBLACK				    "bBlack"				// �Ƿ�Ϊ������

#define STOCKAREA               "stock_area"			// ��Ʊ��������,��A��/B��/...
#define STOCKPLATEAREA          "stock_plate_area"		// ��Ʊ�����������,������/��ҵ��/��С��...
#define	REMARKSINFO				"remarksinfo"			// ��ע��Ϣ
#define	STOCKCODE				"stockcode"				// ��Ʊ����
#define	STOCKNAME				"stockname"				// ��Ʊ����
#define	POSITIONPRICE			"positionprice"			// �ֲּ۸�
#define	POSITIONQTY 			"positionqty"			// �ֲ�����
#define	ISSELLQTY				"issellqty"				// ��������
#define FROZENNUMBER            "frozennumber"          // ��������
#define	TOTALSHARES				"total_shares"		    // �ܹ�Ʊ

#define	POSITIONCOST			"positioncost"			// �ֲֳɱ�
#define	FLOATPRICE				"floatprice"			// ����ӯ��
#define	OPENTIME				"opentime"				// ����ʱ��
#define	DEALNO					"dealno"				// �ɽ����
#define	TRADEDIR				"tradedir"				// ���׷���
#define	DEALPRICE				"dealprice"				// �ɽ��۸�
#define	DEALQTY					"dealqty"				// �ɽ�����
#define	DEALTIME				"dealtime"				// �ɽ�ʱ��
#define	STAMPFEE				"stampfee"				// ӡ����
#define	TRANSFERFEE				"transferfee"			// ������
#define	SECURITIESCOMPANY		"securitiescompany"		// ֤ȯ��˾
#define	FUNDBALANCE				"fundbalance"			// �ʽ����
#define	REGDATE					"regdate"				// ע������
#define	LOGINIP					"loginip"				// ��¼ip	
#define	LOGINTIME				"logintime"				// ��½ʱ��
#define	MACADDRESS				"macaddress"			// ��¼��ַ
#define	STAMPFEERATE			"stampfeerate"			// ӡ��˰����
#define	TRANSFERTAXRATE			"transfertaxrate"		// ����˰����
#define	ONCELOWESTFEE			"oncelowestfee"			// ÿ����ͷ���
#define	MATCHFEERATERATE		"matchfeeraterate"		// ��Ϣ��Ϸ�
#define	STATUS					"status"				// ״̬
#define	RISKPROJECT				"riskproject"			// �����Ŀ
#define	OPERATIONTYPE			"operationtype"			// ��������
#define	RISKEXPLAIN				"riskexplain"			// ���˵��
#define	SWITCHFLAG				"switchflag"			// ����
#define	POSITIONRATE			"positionrate"			// �ֱֲ���
#define	ILLUSTRATE				"illustrate"			// ˵��
#define	TRADEAMOUNT				"tradeamount"			// �ɽ����
#define	TOTALASSETS				"totalassets"			// ���ʲ�
#define	OPENCOST				"opencost"				// ���ֳɱ�
#define	POSITIONMARKETVALUE	    "positionmarketvalue"	// �ֲ���ֵ
#define	AVAILABLEFUNDS			"availablefunds"		// �����ʽ�
#define AVAILABLEGETFUNDS       "availablegetfunds"     // ��ȡ�ʽ�
#define	SELFONLYFUND			"selfonlyfund"			// �����ʽ�ֵ

#define	HAPPENAMOUNT			"happenamount"			// �������
#define	SECURITIESCODE			"securitiescode"		// ֤ȯ����
#define	SECURITIESNAME			"securitiesname"		// ֤ȯ����
#define	DEALAVGPRICE			"dealavgprice"			// �ɽ�����
#define	STOCKLEFTAMOUNT			"stockleftamount"		// ��Ʊ���
#define	COMMISSION				"commission"			// Ӷ��
#define	SUMPLRATE				"sumplrate"				// ��ӯ����
#define	WARNINGTYPE				"warningtype"			// Ԥ������
#define	WARNINGTIME				"warningtime"			// Ԥ��ʱ��
#define	WARNINGTEXT				"warningtext"			// Ԥ������
#define	ORDERSTATUS				"orderstatus"			// ����״̬
#define	INMONEYFUND				"inmoneyfund"			// ����ʽ�
#define	BANKOPNENAME			"bankopenname"			// ���п�����
#define	BANKNAME				"bankname"				// ��������	
#define	BANKCARD				"bankcard"				// ���п���
#define	COMMITIME				"commitime"				// �ύʱ��
#define	ISAPPROVAL				"isapproval"			// �Ƿ����
#define	APPROVALTIME			"approvaltime"			// ���ʱ��
#define	OUTMONEYFUND			"outmoneyfund"			// ������
#define	ORDERPICE				"orderpice"				// ί�м۸�
#define	ORDERTYPE				"ordertype"				// ί������
#define	ORDERVOLUME				"ordervolume"			// ί������
#define	ORDERID					"orderid"				// ί��id
#define	ORDERSTREAM				"orderstream"			// ί������
#define	ORDERDERECTION			"orderderection"		// ί�з���
#define	ORDERMODE				"ordermode"			    // ί��ģʽ
#define	ORDERREF				"orderref"				// ί�б��
#define ORDERTIME               "ordertime"             // ί��ʱ��
#define ORDERLASTUPDATETIME     "updateTime"            // ������ʱ��
#define	CURRENCYRATE			"currency_rate"			// ���ֻ���
#define CANCELORDERNUMBER       "cancelvolume"          // ��������
#define FROZENFUND              "frozenfund"            // �����ʽ�
#define FUNDCHANGEVALUE         "fundchangevalue"       // �ʽ�䶯
#define AMPLITUDE               "Amplitude"             // ���
#define QUANTITYRATIO           "quantityratio"         // ����
#define APPINTRATIO_            "appintRatio_"          // ί��
#define CHANGEHAND              "changeHand"            // ����
#define DATETIME                "date_time"             // ʱ����Ϣ
#define RISKType                "risk_type"             // �������
#define RISKTEXT                "risk_text"             // �������
#define ALLTOTALVALUE           "allTotalValue"         // ����ֵ
#define BUSSNESSID              "bussnessID"            // ҵ��Id
#define BUSSNESSNAME            "bussnessName"          // ҵ������
#define XSHG                    "XSHG"                  // ��֤
#define XSHE                    "XSHE"                  // ����
#define NAVIGATIONID            "NavigationID"          // ����Id
#define FUNCTIONNAME            "FunctionName"          // ��������
#define FINACEMONEY             "finace_money"          // ���������ʽ�
#define QRYSTARTDATETIME        "start_time"            // ��ѯ��ʷ������ݵ���ʼʱ��
#define QRYENDDATETIME          "end_time"              // ��ѯ��ʷ������ݵ���ֹʱ��
#define BLAST                   "bLast"                 // �Ƿ�Ϊ��ѯ�������һ������
//   ��Ʊ�����ֶ�
#define SUBSCRIBETYPE           "Type"                  // �������� 0Ϊ���ģ�1Ϊ������
#define EXCHANGECD              "ExchangeCD"            // ������
#define TICKERS                 "Tickers"               // ��Ʊ����
#define TICKER                  "Ticker"                // ��Ʊ����
#define SHORTNM                 "ShortNM"               // ��Ʊ����
#define CHANGEPCT               "ChangePct"             // �Ƿ�
#define LASTPRICE               "LastPrice"             // ���¼�
#define CHANGE                  "Change"                // �ǵ�
#define NOWVOLUME               "nowvolume"             // ����
#define ALLVOLUME               "allvolume"             // ����
#define PREVCLOSEPRICE          "PrevClosePrice"        // ����
#define OPENPRICE               "OpenPrice"             // ����
#define HIGHPRICE               "HighPrice"             // ���
#define LOWPRICE                "LowPrice"              // ���
#define TRADEMONEY              "Value"                 // �ɽ���
#define TRADEVOLUME             "Volume"                // �ɽ�����
#define QUOTATIONDATE           "quotationDate "        // ��������
#define QUOTATIONTIME           "quotationtime"         // ����ʱ��
#define CURRENTTIME             "CurrentTime"           // ��ǰʱ��
#define QUOTATIONS              "Quotations"            // ����Ϊ����ʱ��Quotations��ֵ��QuotationΪ��
#define QUOTATION               "Quotation"             // ����Ϊ����ʱ��Quotation��ֵ��QuotationsΪ��
#define SUSPENSION              "Suspension"            // ͣ�Ʊ�� 1: ͣ�� 0: δͣ��
#define SENDTYPE                "SendType"              // 0Ϊ����ʱ ���ض��Ĺ�Ʊ���ص������������,1Ϊ�������͵���Ϣ
#define ISTICKER                "IsTicker"              // 0��ʾ��Ʊ,1��ʾָ��

#define ASKBOOKVOLUME1          "AskBook_volume1"		// ��һ������
#define ASKBOOKVOLUME2          "AskBook_volume2"		// ����������
#define ASKBOOKVOLUME3          "AskBook_volume3"		// ����������
#define ASKBOOKVOLUME4			"AskBook_volume4"		// ����������
#define ASKBOOKVOLUME5			"AskBook_volume5"		// ����������
#define BIDBOOKVOLUME1          "BidBook_volume1"		// ��һ������
#define BIDBOOKVOLUME2          "BidBook_volume2"		// ���������
#define BIDBOOKVOLUME3			"BidBook_volume3"		// ����������
#define BIDBOOKVOLUME4			"BidBook_volume4"		// ����������
#define BIDBOOKVOLUME5			"BidBook_volume5"		// ����������

#define	ASKBOOKPRICE1           "AskBook_price1"		// ��һ�ּ۸�
#define	ASKBOOKPRICE2           "AskBook_price2"		// �����ּ۸�
#define	ASKBOOKPRICE3           "AskBook_price3"		// �����ּ۸�
#define	ASKBOOKPRICE4  		    "AskBook_price4"		// �����ּ۸�
#define	ASKBOOKPRICE5  			"AskBook_price5"		// �����ּ۸�

#define	BIDBOOKPRICE1           "BidBook_price1"		// ��һ�ּ۸�
#define	BIDBOOKPRICE2           "BidBook_price2"		// ����ּ۸�
#define	BIDBOOKPRICE3			"BidBook_price3"		// �����ּ۸�
#define	BIDBOOKPRICE4  			"BidBook_price4"		// �����ּ۸�
#define	BIDBOOKPRICE5  			"BidBook_price5"		// �����ּ۸�

// ָ���ֶ�
#define INDEXID                  "IndexID"				// ָ��ID
#define INDEXNAME                "IndexName"			// ָ������
#define PRECLOSEINDEX            "PreCloseIndex"		// ���ռ�
#define OPENINDEX                "OpenIndex"			// ���̼�
#define TURNOVER                 "Turnover"				// �ɽ���
#define HIGHINDEX                "HighIndex"			// ��߼�
#define LOWINDEX                 "LowIndex"				// ��ͼ�
#define LASTINDEX                "LastIndex"			// ���¼�
#define TRADVOLUME               "TradVolume"			// �ɽ�����
#define CLOSEINDEX               "CloseIndex"			// 
#define COMPOSITE                "Composite"			// 
#define COMPOSITES               "Composites"			// 
#define UPSANDDOWNS              "UpsAndDowns"			//  �ǵ���

#define SUMMARGINSET			 "summarginset"			// ����������
#define LEFTMARGINSET			 "leftmarginset"		// ʣ����������
#define INTEREST				 "interest"				// ��Ϣ����
#define SUMINTEREST				 "suminterest"			// �ۼ���Ϣ
#define INTERESTSOURCE			 "interestsource"		// ��Ϣ�䶯��Դ
#define COMMODITYTYPE			 "commoditytype"		// ��Ʒ����

#endif