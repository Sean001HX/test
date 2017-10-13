#pragma once

#include <string>
#include <vector>


struct BrokerNode
{
	std::string id_;
	std::string securityName_;
};


struct AddrNode
{
	std::string ip_;
	int port_;
};


struct SecurityNode
{
	int depCode_;
	std::string ver_;
	std::vector<AddrNode> addrNodes_;
};