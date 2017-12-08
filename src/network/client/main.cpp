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
		bl::MainHandler mainHandler;

		mainHandler.createBrowser();
		mainHandler.startMainLoop();

	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}


	return 0;
}