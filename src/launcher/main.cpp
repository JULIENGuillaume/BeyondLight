//
// Created by Guillaume Julien on 13/02/2018.
//

#include <LauncherClient.hh>
#include <TcpBoostSslSocket.hh>
#include <SocketFactory.hh>

void FactoriesInit() {
	bl::network::socket::SocketFactory::getInstance()->registerModel(bl::network::socket::clientKeyTcpSslBoostSocket,
																	 std::shared_ptr<bl::network::socket::ISocket>(
																			 new bl::network::socket::TcpBoostSslSocket(
																					 true)));
}

int main() {
	std::string s;
	try {
		FactoriesInit();
		bl::network::client::LauncherClient launcher;
		launcher.connectTo("89.234.182.223", 3242);
		launcher.launch();
	} catch (std::exception &e) {
		std::cerr << "Launcher stopped: " << e.what() << std::endl;
		std::cin >> s;
		return EXIT_FAILURE;
	}
	std::cin >> s;
	return EXIT_SUCCESS;
}