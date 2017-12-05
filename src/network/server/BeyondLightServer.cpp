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
#include "../../server/game/building/IBuilding.hh"
#include "../../server/game/building/IronMine.hh"

network::server::BeyondLightServer::BeyondLightServer(unsigned short port) : AServerUdp(socket::serverKeyUdpSslAsyncBoostSocket, port) {

}

void network::server::BeyondLightServer::mainLoop(std::shared_ptr<network::socket::ISocket> socket) {
	auto users = ::server::user::RegisteredUsers::getInstance();
	::server::game::building::IBuilding *build = new ::server::game::building::IronMine;
	std::cout << "Main loop reached" << std::endl;
	bool loggedIn = false;
	while (m_running) {
		auto msg = socket->receive();
		while (msg.find("\r\n") == msg.npos) {
			msg += socket->receive();
		}
		msg = msg.substr(0, msg.find("\r\n"));
		auto toks = common::Toolbox::split(msg, ":");
		if (!toks.empty()) {
			switch (std::atoi(toks[0].c_str())) {
				case 42:
					if (toks.size() == 3 && users->users.find(toks[1]) != users->users.end() && toks[2] == users->users[toks[1]]) {
						loggedIn = true;
						socket->send("123:OK");
					} else
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
				case 4242:
					if (toks.size() == 1 && loggedIn) {
						socket->send("14242:" + build->serialize().dump());
					} else {
						socket->send("321:KO");
					}
					break;
				case 421356:
					if (toks.size() == 2 && loggedIn) {
						int buildingId = std::atoi(toks[1].c_str());
						if (buildingId != build->getId())
							socket->send("321:KO");
						else {
							if (!build->upgrade())
								socket->send("321:KO");
							else
								socket->send("421357:" + toks[1] + ":" + std::to_string(build->getLevel()));
						}
					} else {
						socket->send("321:KO");
					}
					break;
				case 1337:
					this->m_running = false;
					socket->send("123:OK");
					break;
				default:
					socket->send("404:UNKNOWN");
					break;
			}
		}
	}
	std::cout << "End of server" << std::endl;
}
