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
			bl::MainHandler mainHandler;

			mainHandler.createBrowser();
			mainHandler.startMainLoop();
		} catch (std::exception &e) {
			std::cerr << e.what() << std::endl;
			return 1;
		}

	return 0;
}