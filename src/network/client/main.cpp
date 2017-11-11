#include <iostream>
#include <memory>
#include "IClient.hh"
#include "BeyondLightClient.hh"
#include "SocketFactory.hh"
#include "UdpSslAsyncBoostSocket.hh"

void FactoriesInit() {
	network::socket::SocketFactory::getInstance()->registerModel(network::socket::clientKeyUdpSslAsyncBoostSocket,
	                                                             std::shared_ptr<network::socket::ISocket>(
			                                                             new network::socket::UdpSslAsyncBoostSocket()));
}

int main() {
	FactoriesInit();

	try {
		std::shared_ptr<network::client::IClient> client(new network::client::BeyondLightClient());
		client->connectTo("127.0.0.1", 8080);
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}


	return 0;
}