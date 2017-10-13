#include <stdio.h>
#include "TLDataApi/mdl_api.h"
#include "TLDataApi/mdl_shl1_msg.h"
#include "TLDataApi/mdl_shl2_msg.h"
#include "TLDataApi/mdl_szl2_msg.h"
#include "TLDataApi/mdl_szl1_msg.h"
#include "TLDataApi/mdl_cffex_msg.h"
#include "TLDataApi/mdl_czce_msg.h"
#include "TLDataApi/mdl_dce_msg.h"
#include "TLDataApi/mdl_shfe_msg.h"
#include "TLDataApi/mdl_hkex_msg.h"
#include "TLDataApi/mdl_bar_msg.h"

using namespace datayes::mdl;

#if defined(_MSC_VER)
#pragma comment(lib, "mdl_api.lib")
#endif

class TLDataCbk
{
public:
//     virtual void onConnect(bool bConnect, const std::string& err_msg) = 0;      // 连接
//     virtual void onLogin(bool bLogin, const std::string& err_msg) = 0;          // 登录(未使用到)
    virtual void onUpdateEquityQuoteInfo(const mdl_shl1_msg::Equity& info) = 0; // 更新股票行情
    virtual void onUpdateEquityQuoteInfo(const mdl_szl1_msg::SZL1Stock& info) = 0; // 更新股票行情
//     virtual void onUpdateIndexQuoteInfo(const mdl_shl1_msg::Indexes& info) = 0; // 更新指数行情
//     virtual void onUpdateIndexQuoteInfo(const mdl_szl1_msg::SZL1Index& info) = 0; // 更新指数行情
};

class MyMessageHandler : public MessageHandler {
public:
	bool Open(const char* address) {
		m_IOManager = CreateIOManager();
		if (m_IOManager.IsNull()) {
			printf("Incompatible API lib version.\n");
			return false;
		}
		
		SubscriberPtr sub = m_IOManager->CreateSubscriber(this);
		sub->SetServerAddress(address);

		//// subscribe level1 msg
		// shanghai level1 new version
// 		sub->SubcribeMessage<mdl_shl1_msg::Indexes>();//上海指数
		sub->SubcribeMessage<mdl_shl1_msg::Equity>();//上海股票

// 		sub->SubcribeMessage<mdl_szl1_msg::SZL1Index>();//深圳指数
		sub->SubcribeMessage<mdl_szl1_msg::SZL1Stock>();//深圳股票
				
		// connect to server
		std::string err = sub->Connect();
		if (err.empty()) {
			printf("Connect to server successfully.\n");
			return true;
		}
		printf("Connect to server failed: %s.\n", err.c_str());
		return false; 
	}
 
	void Close() {
		if (!m_IOManager.IsNull()) {
			m_IOManager->Shutdown();
		}
	}

    void setTLDataCbk(TLDataCbk* cbk){
        m_cbk = cbk;
    }

	// handle network failure
	virtual void OnMDLAPIMessage(const MDLMessage* msg) {
		MDLMessageHead* head = msg->GetHead();
		if (head->MessageID == mdl_api_msg::ConnectingEvent::MessageID) {
			mdl_api_msg::ConnectingEvent* resp = (mdl_api_msg::ConnectingEvent*)msg->GetBody();
			printf("Connect to %s ...\n", resp->Address.c_str());
		}
		else if (head->MessageID == mdl_api_msg::ConnectErrorEvent::MessageID) {
			mdl_api_msg::ConnectErrorEvent* resp = (mdl_api_msg::ConnectErrorEvent*)msg->GetBody();
			printf("Connect to %s failed %s.\n", resp->Address.c_str(), resp->ErrorMessage.c_str());
		}
		else if (head->MessageID == mdl_api_msg::DisconnectedEvent::MessageID) {
			mdl_api_msg::DisconnectedEvent* resp = (mdl_api_msg::DisconnectedEvent*)msg->GetBody();
			printf("Disconnected from %s: %s.\n", resp->Address.c_str(), resp->ErrorMessage.c_str());
		}
	}

	// handle server response
	virtual void OnMDLSysMessage(const MDLMessage* msg) {
		MDLMessageHead* head = msg->GetHead();
		if (head->MessageID == mdl_sys_msg::LogonResponse::MessageID) {
			mdl_sys_msg::LogonResponse* resp = (mdl_sys_msg::LogonResponse*)msg->GetBody();
			if (resp->ReturnCode != MDLEC_OK) {
				printf("Logon failed: return code %d.\n", resp->ReturnCode);
			}
			for (uint32_t i = 0; i < resp->Services.Length; ++i) {
				for (uint32_t j = 0; j < resp->Services[i]->Messages.Length; ++j) {
					if (resp->Services[i]->Messages[j]->MessageStatus != MDLEC_OK) {
						printf("The server doesn't publish message (service id %d message id %d)\n", 
							resp->Services[i]->ServiceID,
							resp->Services[i]->Messages[j]->MessageID);
					}
				}
			}
		}
	}

	// print shanghai level1 message
	virtual void OnMDLSHL1Message(const MDLMessage* msg) {
		MDLMessageHead* head = msg->GetHead();

		if (head->MessageID == mdl_shl1_msg::Equity::MessageID) {
			mdl_shl1_msg::Equity* body = (mdl_shl1_msg::Equity*)msg->GetBody();
            if (body && m_cbk)
                m_cbk->onUpdateEquityQuoteInfo(*body);
// 			PrintNewStockMessage(body);
		}
// 		else if (head->MessageID == mdl_shl1_msg::Indexes::MessageID) {
// 			mdl_shl1_msg::Indexes* body = (mdl_shl1_msg::Indexes*)msg->GetBody(); 
//             if (body && m_cbk)
//                 m_cbk->onUpdateIndexQuoteInfo(*body);
// // 			PrintIndexMessage(body); 
// 		}
	}

// 	// print shenzhen level1 message
	virtual void OnMDLSZL1Message(const MDLMessage* msg) {
		MDLMessageHead* head = msg->GetHead();
// 		if (head->MessageID == mdl_szl1_msg::SZL1Index::MessageID) {
// 			mdl_szl1_msg::SZL1Index* body = (mdl_szl1_msg::SZL1Index*)msg->GetBody();
//             if (body && m_cbk)
//                 m_cbk->onUpdateIndexQuoteInfo(*body);
// // 			PrintIndexMessage(body); 
// 		}
// 		else
        if (head->MessageID == mdl_szl1_msg::SZL1Stock::MessageID) {
			mdl_szl1_msg::SZL1Stock* body = (mdl_szl1_msg::SZL1Stock*)msg->GetBody();
            if (body && m_cbk)
                m_cbk->onUpdateEquityQuoteInfo(*body);
// 			PrintStockMessage(body); 
		}
	}


private:
	IOManagerPtr    m_IOManager;
    TLDataCbk*      m_cbk;
};
