#include <iostream>
#include <memory>
#include <TcpBoostSslSocket.hh>
#include "SocketFactory.hh"
#include "UdpAsyncBoostSocket.hh"
#include "IClient.hh"
#include "BeyondLightClient.hh"
#include "../common/NetworkWrapper.hh"
#include "MainHandler.hh"

std::shared_ptr<bl::network::socket::ISocket> NetworkWrapper::m_socket = nullptr;

void FactoriesInit() {
	bl::network::socket::SocketFactory::getInstance()->registerModel(bl::network::socket::clientKeyUdpAsyncBoostSocket,
	                                                             std::shared_ptr<bl::network::socket::ISocket>(
			                                                             new bl::network::socket::UdpAsyncBoostSocket()));

	bl::network::socket::SocketFactory::getInstance()->registerModel(bl::network::socket::clientKeyTcpSslBoostSocket,
	                                                                 std::shared_ptr<bl::network::socket::ISocket>(
		                                                                 new bl::network::socket::TcpBoostSslSocket(
			                                                                 true)));
}

int main() {
	FactoriesInit();

		try {
			std::cerr << "Creating main handler" << std::endl;
			bl::MainHandler mainHandler;

			std::cerr << "Creating browser" << std::endl;
			mainHandler.createBrowser();
			std::cerr << "starting main loop" << std::endl;
			mainHandler.startMainLoop();
		} catch (std::exception &e) {
			std::cerr << "Client exited with " << e.what() << std::endl;
			return 1;
		}

	return 0;
}