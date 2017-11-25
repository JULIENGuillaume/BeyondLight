#include <iostream>
#include <memory>
#include "IClient.hh"
#include "BeyondLightClient.hh"
#include "SocketFactory.hh"
#include "UdpSslAsyncBoostSocket.hh"
#include "../../common/NetworkWrapper.hh"
#include "../../client/MainHandler.hh"

std::shared_ptr<network::socket::ISocket> NetworkWrapper::m_socket = nullptr;

void FactoriesInit() {
	network::socket::SocketFactory::getInstance()->registerModel(network::socket::clientKeyUdpSslAsyncBoostSocket,
	                                                             std::shared_ptr<network::socket::ISocket>(
			                                                             new network::socket::UdpSslAsyncBoostSocket()));
}

int main() {
	FactoriesInit();

	try {
		MainHandler mainHandler;

		if (mainHandler.init()) {
			std::cerr << "initialization failed!" << std::endl;
			return (1);
		}

		mainHandler.createBrowser();
		mainHandler.startMainLoop();

		mainHandler.destroy();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}


	return 0;
}