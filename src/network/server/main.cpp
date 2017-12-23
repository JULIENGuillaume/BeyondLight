#include <iostream>
#include <memory>
#include "UdpAsyncBoostSocket.hh"
#include "../socket/SocketFactory.hh"
#include "IServer.hh"
#include "BeyondLightServer.hh"
#include "../../server/ServerCore.hh"

void FactoriesInit() {
	bl::network::socket::SocketFactory::getInstance()->registerModel(bl::network::socket::serverKeyUdpSslAsyncBoostSocket,
	                                                             std::shared_ptr<bl::network::socket::ISocket>(
			                                                             new bl::network::socket::UdpAsyncBoostSocket()));
}

int main() {
	FactoriesInit();
	//TODO: move the main to a more coherent place

	try {
		//std::shared_ptr<bl::network::server::IServer> server(new bl::network::server::BeyondLightServer(8080));
		//server->run();
		//bl::network::server::ServerNetworkHandler serverNetworkHandler;
		bl::server::ServerCore core;
		core.start();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}