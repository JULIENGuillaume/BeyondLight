#include <iostream>
#include <memory>
#include <boost/uuid/uuid_io.hpp>
#include "IServer.hh"
#include "BeyondLightServer.hh"
#include "SocketFactory.hh"
#include "UdpSslAsyncBoostSocket.hh"

void FactoriesInit() {
	network::socket::SocketFactory::getInstance()->registerModel(network::socket::serverKeyUdpSslAsyncBoostSocket,
	                                                             std::shared_ptr<network::socket::ISocket>(
			                                                             new network::socket::UdpSslAsyncBoostSocket()));
}

int main() {
	FactoriesInit();

	try {
		std::shared_ptr<network::server::IServer> server(new network::server::BeyondLightServer(8080));
		server->run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	return 0;
}