#include <iostream>
#include <memory>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/json.hpp>

#include <mongocxx/client.hpp>
#include <mongocxx/instance.hpp>
#include "IServer.hh"
#include "BeyondLightServer.hh"
#include "SocketFactory.hh"
#include "UdpSslAsyncBoostSocket.hh"
#include "../../server/storage/Database.hh"


void FactoriesInit() {
	network::socket::SocketFactory::getInstance()->registerModel(network::socket::serverKeyUdpSslAsyncBoostSocket,
	                                                             std::shared_ptr<network::socket::ISocket>(
			                                                             new network::socket::UdpSslAsyncBoostSocket()));
}

int main() {
	mongocxx::instance inst{};

	std::srand(time(nullptr));

	server::storage::Database::getDbInstance()->insertUser(server::user::User(std::rand(), "Daniel"));
	server::storage::Database::getDbInstance()->insertMultipleUsers({server::user::User(std::rand(), "Daniel")});

	server::user::User *daniel = server::storage::Database::getDbInstance()->getUserByLogin("Daniel");

	std::cout << daniel->getId() << " - " << daniel->getLogin() << std::endl;

	auto delCount = server::storage::Database::getDbInstance()->removeUserByLogin("Daniel");

	std::cout << "deleted : " << delCount << " Daniels." << std::endl;

	/*
	FactoriesInit();

	try {
		std::shared_ptr<network::server::IServer> server(new network::server::BeyondLightServer(8080));
		server->run();
	} catch (std::exception &e) {
		std::cerr << e.what() << std::endl;
		return 1;
	}
	 */
	return 0;
}