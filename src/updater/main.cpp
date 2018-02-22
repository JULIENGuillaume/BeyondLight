//
// Created by Guillaume Julien on 13/02/2018.
//

#include <SocketFactory.hh>
#include <UpdaterServer.hh>
#include <UdpAsyncBoostSocket.hh>
#include <TcpBoostSslSocket.hh>

void FactoriesInit() {
	bl::network::socket::SocketFactory::getInstance()->registerModel(bl::network::socket::serverKeyTcpSslBoostSocket,
																	 std::shared_ptr<bl::network::socket::ISocket>(
																			 new bl::network::socket::TcpBoostSslSocket(
																					 false)));
}

int main() {
	std::string s;
	try {
		FactoriesInit();
		bl::network::server::UpdaterServer updater(3242);
		updater.run();
	} catch (std::exception &e) {
		std::cerr << "Program stopped: " << e.what() << std::endl;
		std::cin >> s;
		return EXIT_FAILURE;
	}
	std::cin >> s;
	return EXIT_SUCCESS;
}