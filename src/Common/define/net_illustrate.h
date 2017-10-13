#ifndef __NET_ILLUSTRATE_H__
#define __NET_ILLUSTRATE_H__

enum E_COMM_MSG_TYPE : int
{
    EMPT_Init_Null = -1,                // ��Ч
	/////////////////// ��½��� //////////
	LOGIN_TRADE_REQ	= 0,                // ��¼����	= 1001
    LOGIN_TRADE_RSP,		            // ��¼�ص�	= 1002
    LOGIN_OUT_REQ,		                // �ǳ�����	= 1003
    LOGIN_QUIT_MSG,		                // ǿ������	= 1004
    HEART_BEAT_MSG,		                // ��������	= 1005

	///////////////// ��ȡ��� ////////////
	INSTITUTION_REQ,			        // ������ѯ����	= 2001
	INSTITUTION_RSP,			        // ������ѯӦ��	= 2002
	INSTITUTION_PREAPPROVAL_REQ,        // ����˻�����ѯ���� = 2003
    INSTITUTION_PREAPPROVAL_RSP,        // ����˻�����ѯӦ�� = 2004
	INSTITUTION_LINK_REQ,	            // �����ƹ��ѯ���� = 2005
	INSTITUTION_LINK_RSP,	            // �����ƹ��ѯӦ�� = 2006
	ROLES_QUERY_REQ,			        // ��ɫ��ѯ���� = 2007
	ROLES_QUERY_RSP,			        // ��ɫ��ѯӦ��	= 2008
	INSTITUTIONUSER_ROLE_RELATION_REQ,	// �������û�����ɫ��ϵ��ѯ���� = 2009
	INSTITUTIONUSER_ROLE_RELATION_RSP,	// �������û�����ɫ��ϵ��ѯӦ�� = 2010
	COMMISSION_QUERY_REQ,			    // Ӷ���ѯ���� = 2011
	COMMISSION_QUERY_RSP,			    // Ӷ���ѯӦ�� = 2012
	COMMISSION_DETAIL_REQ,			    // Ӷ����ϸ��ѯ���� = 2013
	COMMISSION_DETAIL_RSP,			    // Ӷ����ϸ��ѯӦ�� = 2014
	PROFITCOMMISSION_QUERY_REQ,			// �ֳɲ�ѯ���� = 2015
    PROFITCOMMISSION_QUERY_RSP,			// �ֳɲ�ѯӦ�� = 2016
    PROFITCOMMISSION_DETAIL_REQ,		// �ֳ���ϸ��ѯ���� = 2017
    PROFITCOMMISSION_DETAIL_RSP,		// �ֳ���ϸ��ѯӦ�� = 2018
	TOPOLOGICAL_TREE_REQ,			    // ��������ѯ���� = 2019
	TOPOLOGICAL_TREE_RSP,			    // ��������ѯӦ�� = 2020
	CHILD_QUERY_REQ,					// ���˻���ѯ���� = 2021
	CHILD_QUERY_RSP,					// ���˻���ѯӦ�� = 2022
	CHILD_APPROVAL_REQ,				    // ���˻���˲�ѯ���� = 2023
	CHILD_APPROVAL_RSP,				    // ���˻���˲�ѯӦ�� = 2024
	FUNDACC_QUERY_REQ,					// �ʽ��˻���ѯ���� = 2025
    FUNDACC_QUERY_RSP,					// �ʽ��˻�Ӧ�� = 2026
	ONLINE_USER_REQ,					// �����û���ѯ���� = 2027
	ONLINE_USER_RSP,					// �����û�Ӧ�� = 2028

    STOCK_CONTRACT_QUERY_REQ,		    // ��Ʊ��Լ��ѯ���� = 2029
    STOCK_CONTRACT_QUERY_RSP,		    // ��Ʊ��Լ��ѯӦ�� = 2030
    STOCK_INSTRUMENT_QUERY_REQ,		    // ��Ʊ��������ѯ���� = 2031
	STOCK_INSTRUMENT_QUERY_RSP,		    // ��Ʊ��������ѯӦ�� = 2032
	FORBID_BUY_SELL_QUERY_REQ,		    // ��ֹ������ѯ���� = 2033
	FORBID_BUY_SELL_QUERY_RSP,		    // ��ֹ������ѯӦ�� = 2034
	POSI_RATE_QUERY_REQ,				// �ֱֲ������ò�ѯ���� = 2035
	POSI_RATE_QUERY_RSP,				// �ֱֲ������ò�ѯӦ�� = 2036
	POSI_QUERY_REQ,					    // �ֲֲ�ѯ���� = 2037
	POSI_QUERY_RSP,					    // �ֲֲ�ѯӦ�� = 2038

	CURRENTENTRUST_QUERY_REQ,			// ��ǰί�в�ѯ���� = 2039
    CURRENTENTRUST_QUERY_RSP,			// ��ǰί�в�ѯӦ�� = 2040
    TODAYENTRUST_QUERY_REQ,				// ����ί�в�ѯ���� = 2041
    TODAYENTRUST_QUERY_RSP,				// ����ί�в�ѯӦ�� = 2042
    HISTORYENTRUST_QUERY_REQ,			// ��ʷί�в�ѯ���� = 2043
    HISTORYENTRUST_QUERY_RSP,			// ��ʷί�в�ѯӦ�� = 2044
    TRADE_QUERY_REQ,					// ���ճɽ���ѯ���� = 2045
	TRADE_QUERY_RSP,					// ���ճɽ���ѯӦ�� = 2046
    HISTORYTRADE_QUERY_REQ,			    // ��ʷ�ɽ���ѯ���� = 2047
    HISTORYTRADE_QUERY_RSP,			    // ��ʷ�ɽ���ѯӦ�� = 2048
    FUND_QUERY_REQ,					    // �ʽ��ѯ���� = 2049
	FUND_QUERY_RSP,					    // �ʽ��ѯӦ�� = 2050
	FUND_SERIAL_QUERY_REQ,			    // �ʽ���ˮ��ѯ���� = 2051
	FUND_SERIAL_QUERY_RSP,			    // �ʽ���ˮ��ѯӦ�� = 2052
	DELIVERY_QUERY_REQ,				    // �����ѯ���� = 2053
	DELIVERY_QUERY_RSP,				    // �����ѯӦ�� = 2054
	CHILD_FUNDMONITIOR_QUERY_REQ,	    // ���ʻ�ʵʱ�ʽ��ز�ѯ���� = 2055(��ʹ��)
	CHILD_FUNDMONITIOR_QUERY_RSP,	    // ���ʻ�ʵʱ�ʽ��ز�ѯӦ�� = 2056(��ʹ��)
	CHILD_SUMPOSITION_QUERY_REQ,		// ϵͳ�ֲֲܳ�ѯ���� = 2057(��ʹ��)
	CHILD_SUMPOSITION_QUERY_RSP,		// ϵͳ�ֲֲܳ�ѯӦ�� = 2058(��ʹ��)
	CHILD_TIMEWARN_NOTIFY_QUERY_REQ,	// ʵʱԤ��֪ͨ��ѯ���� = 2059
	CHILD_TIMEWARN_NOTIFY_QUERY_RSP,	// ʵʱԤ��֪ͨ��ѯӦ�� = 2060
    CHILD_EQUIPMENTMONEY_QUERY_REQ,		// ���ʻ�������˲�ѯ���� = 2061
    CHILD_EQUIPMENTMONEY_QUERY_RSP,		// ���ʻ�������˲�ѯӦ�� = 2062
	CHILD_AUTOOUTMONEY_QUERY_REQ,		// ���ʻ��Զ�������˲�ѯ���� = 2063
	CHILD_AUTOOUTMONEY_QUERY_RSP,		// ���ʻ��Զ�������˲�ѯӦ�� = 2064
	FEE_MANAGER_QUERY_REQ,				// ���ù����ѯ���� = 2065
	FEE_MANAGER_QUERY_RSP,				// ���ù����ѯ����Ӧ�� = 2066

	SELFFUNCTION_QUERY_REQ,				// �����ܲ�ѯ���� = 2067
	SELFFUNCTION_QUERY_RSP,				// �����ܲ�ѯ����Ӧ�� = 2068
	ROLEFUNCTION_QUERY_REQ,				// ��ɫ���ܲ�ѯ���� = 2069
	ROLEFUNCTION_QUERY_RSP,				// ��ɫ���ܲ�ѯ����Ӧ�� = 2070
	MANAGER_QUERY_REQ,					// ����Ա��ѯ���� = 2071
	MANAGER_QUERY_RSP,					// ����Ա��ѯ����Ӧ�� = 2072
	BUSSNESS_QUERY_REQ,					// ����ҵ���ѯ���� = 2073
	BUSSNESS_QUERY_RSP,					// ����ҵ���ѯ����Ӧ�� = 2074

    CUSTOMSTOCK_REQ,			        // ��ѡ��Ʊ��ѯ����	= 2075
    CUSTOMSTOCK_RSP,			        // ��ѡ��Ʊ��ѯӦ��	= 2076

    CHILD_AUTOINTOMONEY_QUERY_REQ,		// ���ʻ��Զ������˲�ѯ���� = 2077
    CHILD_AUTOINTOMONEY_QUERY_RSP,		// ���ʻ��Զ������˲�ѯӦ�� = 2078

	RISK_HISTORY_REQ,					    // �����ʷ��ѯ���� = 2079
	RISK_HISTORY_RSP,					    // �����ʷ��ѯӦ�� = 2080

	MARGIN_LEFTQTY_REQ,					    // ʣ����ȯ������ѯ���� = 2081
	MARGIN_LEFTQTY_RSP,					    // ʣ����ȯ������ѯӦ�� = 2082

	MARGIN_MANAGER_REQ,					    // ��ȯ�����ѯ���� = 2083
	MARGIN_MANAGER_RSP,					    // ��ȯ�����ѯӦ�� = 2084

	MARGIN_LIABILITIES_REQ,					// ��ȯ��ծ��ѯ���� = 2085
	MARGIN_LIABILITIES_RSP,					// ��ȯ��ծ��ѯӦ�� = 2086
	INTEREST_STATISTICS_REQ,				// ��Ϣͳ�Ʋ�ѯ���� = 2087
	INTEREST_STATISTICS_RSP,				// ��Ϣͳ�Ʋ�ѯӦ�� = 2088
	INTEREST_DETAIL_REQ,					// ��Ϣ��ϸ��ѯ���� = 2089
	INTEREST_DETAIL_RSP,					// ��Ϣ��ϸ��ѯӦ�� = 2090

	CURRENT_MARGINENTRUST_REQ,					// ��ǰ��ȯί������ = 2091
	CURRENT_MARGINENTRUST_RSP,					// ��ǰ��ȯί�в�ѯӦ�� = 2092
	CURRENT_MARGINTRADE_REQ,					// ��ǰ��ȯ�ɽ����� = 2093
	CURRENT_MARGINTRADE_RSP,					// ��ǰ��ȯ�ɽ���ѯӦ�� = 2094
	///////////////////////////////// ����/���� ��� ///////////////////
	ABOUT_ADD_CHANGE,				// ����/���� ��� = 3000

	INSTITUTION_ADD_REQ,				// ���������������� = 3001
	INSTITUTION_ADD_RSP,				// ������������Ӧ�� = 3002
	INSTITUTION_CHANGE_REQ,			    // �����޸����� = 3003
	INSTITUTION_CHANGE_RSP,			    // �����޸�Ӧ�� = 3004
    INSTITUTION_APPROVAL_REQ,		    // ����������� = 3005
	INSTITUTION_APPROVAL_RSP,		    // �������Ӧ�� = 3006
	ROLES_ADD_REQ,					    // ���ӽ�ɫ���� = 3007
	ROLES_ADD_RSP,					    // ���ӽ�ɫӦ�� = 3008
	ROLES_CHANGE_REQ,				    // �޸Ľ�ɫ���� = 3009
	ROLES_CHANGE_RSP,				    // �޸Ľ�ɫӦ�� = 3010
	BIND_FUNCTION_ROLE_RELATIUON_REQ,   // �󶨹��ܽ�ɫ��ϵ����  = 3011
	BIND_FUNCTION_ROLE_RELATIUON_RSP,   // �󶨹��ܽ�ɫ��ϵӦ�� = 3012
	USERROLE_ADDRELATION_REQ,		    // �����û�(����)��ɫ��ϵ�������� = 3013
	USERROLE_ADDRELATION_RSP,		    // �����û�(����)��ɫ��ϵ����Ӧ�� = 3014
	CHILDUSER_ADD_REQ,				    // ���ʻ��������� = 3015
	CHILDUSER_ADD_RSP,				    // ���ʻ�����Ӧ�� = 3016
	CHILDUSER_CHANGE_REQ,			    // ���ʻ��޸����� = 3017
	CHILDUSER_CHANGE_RSP,			    // ���ʻ��޸�Ӧ�� = 3018
	CHILDUSER_INOUTMONEY_REQ,		    // ���ʻ���������� = 3019
	CHILDUSER_INOUTMONEY_RSP,		    // ���ʻ������Ӧ�� = 3020
	CHILDUSER_APPROVAL_REQ,			    // ���ʻ�������� = 3021
	CHILDUSER_APPROVAL_RSP,			    // ���ʻ����Ӧ�� = 3022
	FUNDUSER_ADD_REQ,				    // �ʽ��˻��������� = 3023
	FUNDUSER_ADD_RSP,				    // �ʽ��˻�����Ӧ�� = 3024
	FUNDUSER_CHANGE_REQ,				// �ʽ��˻��޸����� = 3025
	FUNDUSER_CHANGE_RSP,				// �ʽ��˻��޸�Ӧ�� = 3026
	FEE_SET_REQ,						// ������������ = 3027
	FEE_SET_RSP,						// ��������Ӧ�� = 3028
	STOCK_INSTRUMENTBLACK_SET_REQ,	    // ��Ʊ�������������� = 3029
	STOCK_INSTRUMENTBLACK_SET_RSP,	    // ��Ʊ����������Ӧ�� = 3030
	FORBID_BUY_SELL_SET_REQ,			// ��ֹ������������	= 3031
	FORBID_BUY_SELL_SET_RSP,			// ��ֹ��������Ӧ�� = 3032
	POSI_RATE_SET_REQ,				    // �ֱֲ����������� = 3033
	POSI_RATE_SET_RSP,				    // �ֱֲ�������Ӧ�� = 3034
	CHILDUSER_AUTOINMONEY_APPROVAL_REQ,	// ���˻��Զ����������� = 3035
	CHILDUSER_AUTOINMONEY_APPROVAL_RSP,	// ���˻��Զ�������Ӧ�� = 3036
	CHILDUSER_AUTOOUTMONEY_APPROVAL_REQ,// ���˻��Զ������������ = 3037
	CHILDUSER_AUTOOUTMONEY_APPROVAL_RSP,// ���˻��Զ��������Ӧ�� = 3038
	PASSWORD_CHANGE_REQ,				// �����޸����� = 3039
	PASSWORD_CHANGE_RSP,				// �����޸�Ӧ�� = 3040

	MANAGER_ADD_REQ,					// ����Ա�������� = 3041
	MANAGER_ADD_RSP,					// ����Ա��������Ӧ�� = 3042
	MANAGER_CHANGE_REQ,					// ����Ա�޸����� = 3043
	MANAGER_CHANGE_RSP,					// ����Ա�޸�����Ӧ�� = 3044
	APPLY_EQUIPMONEY_REQ,               // ���������ʽ�����  =3045
	APPLY_EQUIPMONEY_RSP,               // ���������ʽ�����Ӧ�� =3046
    APPLY_EQUIPMONEY_APPROVAL_REQ,      // ���������ʽ��������  =3047
    APPLY_EQUIPMONEY_APPROVAL_RSP,      // ���������ʽ��������Ӧ�� =3048

    CUSTOMSTOCK_ADD_REQ,			    // ��ѡ��Ʊ��������	= 3049
    CUSTOMSTOCK_ADD_RSP,			    // ��ѡ��Ʊ����Ӧ��	= 3050

	ROLES_USER_CHANGE_REQ,			    // �޸��û���������֮���ϵ	= 3051
	ROLES_USER_CHANGE_RSP,			    // �޸��û���������֮���ϵ	= 3052

    CHILDUSER_AUTO_INMONEY_REQ,			// ���˻��Զ�������� = 3053
    CHILDUSER_AUTO_INMONEY_RSP,			// ���˻��Զ����Ӧ�� = 3054
    CHILDUSER_AUTO_OUTMONEY_REQ,		// ���˻��Զ��������� = 3055
    CHILDUSER_AUTO_OUTMONEYL_RSP,		// ���˻��Զ�����Ӧ�� = 3056

    CHILDUSER_AUTO_ADD_REQ,				// ���ʻ��Զ��������� = 3057
    CHILDUSER_AUTO_ADD_RSP,				// ���ʻ��Զ�����Ӧ�� = 3058

	MARGIN_SET_REQ,						// ��ȯ��Ϣ�������� = 3059
	MARGIN_SET_RSP,						// ��ȯ��Ϣ����Ӧ�� = 3060

	//////////////////////// ������� ////////////
	ABOUT_TRADE,					    // ������� = 4000
	OPENCLOSE_REQ,					    // ��ƽ������ = 4001
    ORDERINSERT_MSG,					// ί���ύ���� = 4002
    ORDERCHANGE_MSG,					// ί�иı����� = 4003
	CANCELORDER_REQ,					// �������� = 4004
    ORDERCANCEL_MSG,					// ί�г������� = 4005
    TRADEOVER_MSG,					    // �ɽ����� = 4006
    POSITION_MSG,					    // �ֲ����� = 4007
    MONEYCHANGE_MSG,					// �ʽ����� = 4008
    RISKTIGGER_MSG,					    // ������� = 4009

	//////////////////// ɾ����� ////////////////
	ABOUT_DELETE,				// ɾ����� = 5000
	INSTITUTION_DEL_REQ,		// ����ɾ������ = 5001
	INSTITUTION_DEL_RSP,		// ����ɾ��Ӧ�� = 5002
	ROLES_DEL_REQ,			    // ��ɫɾ������ = 5003
	ROLES_DEL_RSP,			    // ��ɫɾ��Ӧ�� = 5004
	ROLES_USER_DEL_REQ,		    // ɾ���û���������֮���ϵ = 5005
	ROLES_USER_DEL_RSP,		    // ɾ���û���������֮���ϵӦ�� = 5006
	CHILDUSER_DEL_REQ,		    // ���˻�ɾ������ = 5007
	CHILDUSER_DEL_RSP,		    // ���˻�ɾ��Ӧ�� = 5008
	FUNDUSER_DEL_REQ,		    // �ʽ��˻�ɾ������ = 5009
	FUNDUSER_DEL_RSP,		    // �ʽ��˻�ɾ��Ӧ��,5010
	MANAGER_DEL_REQ,			// ����Աɾ������ = 5011
	MANAGER_DEL_RSP,			// ����Աɾ������Ӧ�� = 5012

    CUSTOMSTOCK_DEL_REQ,		// ��ѡ��Ʊɾ������	= 5013
    CUSTOMSTOCK_DEL_RSP,		// ��ѡ��Ʊɾ��Ӧ��	= 5014

    EMPT_Max_Count,
};

// ��Ϣ�е�command code��ע�⣺������洢˳��һ��Ҫ��ö�١�E_COMM_MSG_TYPE���ж�Ӧ���һ��!!!
const char* const gszMsgCommandCode[E_COMM_MSG_TYPE::EMPT_Max_Count] = {
    /////////////////// ��½��� //////////
    "1001",
    "1002",
    "1003",
    "1004",
    "1005",
    ///////////////// ��ȡ��� ////////////
    "2001",
    "2002",
    "2003",
    "2004",
    "2005",
    "2006",
    "2007",
    "2008",
    "2009",
    "2010",
    "2011",
    "2012",
    "2013",
    "2014",
    "2015",
    "2016",
    "2017",
    "2018",
    "2019",
    "2020",
    "2021",
    "2022",
    "2023",
    "2024",
    "2025",
    "2026",
    "2027",
    "2028",
    "2029",
    "2030",
    "2031",
    "2032",
    "2033",
    "2034",
    "2035",
    "2036",
    "2037",
    "2038",
    "2039",
    "2040",
    "2041",
    "2042",
    "2043",
    "2044",
    "2045",
    "2046",
    "2047",
    "2048",
    "2049",
    "2050",
    "2051",
    "2052",
    "2053",
    "2054",
    "2055",
    "2056",
    "2057",
    "2058",
	"2059",
	"2060",
	"2061",
	"2062",
	"2063",
	"2064",
	"2065",
	"2066",
	"2067",
	"2068",
    "2069",
    "2070",
    "2071",
    "2072",
    "2073",
    "2074",
    "2075",
    "2076",
    "2077",
    "2078",
	"2079",
	"2080",
	"2081",
	"2082",
	"2083",
	"2084",
	"2085",
	"2086",
	"2087",
	"2088",
	"2089",
	"2090",
	"2091",
	"2092",
	"2093",
	"2094",
    ///////////////////////////////// ����/���� ��� ///////////////////
	"3000",
    "3001",
    "3002",
    "3003",
    "3004",
    "3005",
    "3006",
    "3007",
    "3008",
    "3009",
    "3010",
    "3011",
    "3012",
    "3013",
    "3014",
    "3015",
    "3016",
    "3017",
    "3018",
    "3019",
    "3020",
    "3021",
    "3022",
    "3023",
    "3024",
    "3025",
    "3026",
    "3027",
    "3028",
    "3029",
    "3030",
    "3031",
    "3032",
    "3033",
    "3034",
    "3035",
    "3036",
    "3037",
    "3038",
    "3039",
    "3040",
	"3041",
	"3042",
	"3043",
	"3044",
	"3045",
    "3046",
    "3047",
    "3048",
    "3049",
    "3050",
	"3051",
	"3052",
    "3053",
    "3054",
    "3055",
    "3056",
    "3057",
    "3058",
	"3059",
	"3060",

    //////////////////////// ������� ////////////
	"4000",
    "4001",
    "4002",
    "4003",
    "4004",
    "4005",
    "4006",
    "4007",
    "4008",
    "4009",
	
    //////////////////// ɾ����� ////////////////
	"5000",
    "5001",
    "5002",
    "5003",
    "5004",
    "5005",
    "5006",
    "5007",
    "5008",
    "5009",
    "5010",
	"5011",
	"5012",
    "5013",
    "5014",
};

#endif