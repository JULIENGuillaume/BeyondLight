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
}