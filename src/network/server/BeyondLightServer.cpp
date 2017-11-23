/*
** BeyondLightServer.cpp for BeyondLight in /home/guillaume/delivery/BeyondLight/BeyondLightServer.cpp
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Tue Nov 07 14:42:17 2017 Guillaume Julien
** Last update Tue Nov 07 14:42:17 2017 Guillaume Julien
*/

#include <SocketFactory.hh>
#include "BeyondLightServer.hh"
#include "../../common/Toolbox.hh"
#include "../../server/user/RegisteredUsers.hh"

network::server::BeyondLightServer::BeyondLightServer(unsigned short port) : AServerUdp(socket::serverKeyUdpSslAsyncBoostSocket, port) {

}

void network::server::BeyondLightServer::mainLoop(std::shared_ptr<network::socket::ISocket> socket) {
	auto users = ::server::user::RegisteredUsers::getInstance();
	std::cout << "Main loop reached" << std::endl;
	auto msg = socket->receive();
	auto toks = common::Toolbox::split(msg, ":");
	if (!toks.empty()) {
		switch (std::atoi(toks[0].c_str())) {
			case 42:
				if (toks.size() == 3 && users->users.find(toks[1]) != users->users.end() && toks[2] == users->users[toks[1]])
					socket->send("123:OK");
				else
					socket->send("321:KO");
				break;
			case 43:
				if (toks.size() == 7) {
					std::cout << "Registered user " << toks[3] << " with password " << toks[5] << std::endl;
					users->users.emplace(toks[3], toks[5]);
					socket->send("123:OK");
				} else {
					socket->send("321:KO");
				}
			          break;
			default:
				socket->send("404:UNKNOWN");
				break;
		}
	}
	std::cout << "End of server" << std::endl;
}
