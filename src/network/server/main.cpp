#include <iostream>
#include <memory>
#include <bsoncxx/builder/stream/document.hpp>
#include "../../server/storage/include/json.hpp"

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

    nlohmann::json j;

    j["name"] = "Daniel";
    j["age"] = 42;
    j["lastName"] = "Daniel";

	server::storage::Database::getDbInstance()->insert("myCollection", j);

	nlohmann::json daniel = server::storage::Database::getDbInstance()->getByKey("myCollection", "name", "Daniel");

    for (auto it = daniel.begin(); it != daniel.end(); ++it) {
        std::cout << it.key() << " : " << it.value() << std::endl;
    }

	auto delCount = server::storage::Database::getDbInstance()->removeByKey("myCollection", "name", "Daniel");

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