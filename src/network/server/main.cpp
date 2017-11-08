#include <iostream>
#include <memory>
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

	std::shared_ptr<network::server::IServer> server(new network::server::BeyondLightServer(8080));
	server->run();
	std::cout << "Hello, World!" << std::endl;
	return 0;
}