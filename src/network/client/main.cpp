#include <iostream>
#include <memory>
#include "IClient.hh"
#include "BeyondLightClient.hh"
#include "SocketFactory.hh"
#include "UdpSslAsyncBoostSocket.hh"

void FactoriesInit() {
	network::socket::SocketFactory::getInstance()->registerModel(network::socket::serverKeyUdpSslAsyncBoostSocket,
	                                                             std::shared_ptr<network::socket::ISocket>(
			                                                             new network::socket::UdpSslAsyncBoostSocket()));

	network::socket::SocketFactory::getInstance()->registerModel(network::socket::clientKeyUdpSslAsyncBoostSocket,
	                                                             std::shared_ptr<network::socket::ISocket>(
			                                                             new network::socket::UdpSslAsyncBoostSocket()));
}

int main() {
	FactoriesInit();

	std::shared_ptr<network::client::IClient> client(new network::client::BeyondLightClient());
	client->connectTo("0.0.0.0", 8080);
	return 0;
}