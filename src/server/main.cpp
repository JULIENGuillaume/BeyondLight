#include <iostream>
#include <memory>
#include <TcpBoostSslSocket.hh>
#include "UdpAsyncBoostSocket.hh"
#include "SocketFactory.hh"
#include "IServer.hh"
#include "BeyondLightServer.hh"
#include "ServerCore.hh"

void FactoriesInit() {
	bl::network::socket::SocketFactory::getInstance()->registerModel(bl::network::socket::serverKeyUdpAsyncBoostSocket,
	                                                             std::shared_ptr<bl::network::socket::ISocket>(
			                                                             new bl::network::socket::UdpAsyncBoostSocket()));

	bl::network::socket::SocketFactory::getInstance()->registerModel(bl::network::socket::serverKeyTcpSslBoostSocket,
	                                                             std::shared_ptr<bl::network::socket::ISocket>(
		                                                             new bl::network::socket::TcpBoostSslSocket(
			                                                             false)));
}

void dumpStrAsHexa(std::string const& str) {
	int i;
	for (i = 0; i < str.size(); i++) {
		if (i != 0 && ((i % 8) == 0))
			std::cout << std::endl;
		std::cout << std::hex << (int)str[i] << "\t";
	}
	while (i++ % 8)
		std::cout << ".\t";
	std::cout << std::endl;
}

int main() {
	FactoriesInit();

	try {
		bl::server::ServerCore core;
		core.start();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
	/*bl::network::client::ClientMessage cMessage;
	bl::network::server::ServerMessage sMessage;

	cMessage.getBody().apiType = bl::server::api::EApiType::API_TYPE_USER;
	cMessage.getBody().msgType = bl::network::client::ClientMessageType::CLIENT_MESSAGE_TYPE_REQUEST;
	cMessage.getBody().code = 42;
	cMessage.getBody().sessionId = "125";
	cMessage.getBody().messageSize = 4;
	cMessage.getBody().message = "toto";
	std::cout << "====== Dumping cMessage ======" << std::endl;
	dumpStrAsHexa(cMessage.serialize());
	std::cout << "==============================" << std::endl << std::endl;

	sMessage.getBody().message = "haha";
	sMessage.getBody().messageSize = 4;
	sMessage.getBody().code = 75;
	sMessage.getBody().type = bl::network::server::ServerMessageType::SERVER_MESSAGE_TYPE_INFO;
	std::cout << "====== Dumping sMessage ======" << std::endl;
	dumpStrAsHexa(sMessage.serialize());
	std::cout << "==============================" << std::endl << std::endl;

	std::string s;
	std::cin >> s;*/
}