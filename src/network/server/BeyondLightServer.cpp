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
#include <UdpAsyncBoostSocket.hh>
#include <TcpBoostSslSocket.hh>
#include "BeyondLightServer.hh"
#include "../../server/game/building/IBuilding.hh"
#include "../../server/game/planet/Planet.hh"

bl::network::server::BeyondLightServer::BeyondLightServer(unsigned short port, bl::network::server::ServerNetworkHandler *handler) :
	AServerTcpUdp(socket::serverKeyUdpSslAsyncBoostSocket, socket::serverKeyTcpSslBoostSocket, port), m_handler(handler) {
}

void bl::network::server::BeyondLightServer::mainLoop(std::shared_ptr<bl::network::socket::ISocket> socket) {
	try {
		if (std::dynamic_pointer_cast<socket::TcpBoostSslSocket>(socket) != nullptr) {
			advancedSecuredTcpConnection(socket);
			this->m_workingLoop = false;
			return;
		}
		this->m_activeThreads.emplace_back(&bl::network::server::BeyondLightServer::readingThread, this, socket);
		this->m_activeThreads.emplace_back(&bl::network::server::BeyondLightServer::sendingThread, this, socket);

		while (this->m_running && this->m_workingLoop) {
			std::this_thread::sleep_for(std::chrono::milliseconds(100));
		}
	} catch (std::exception &e) {
		std::cerr << "Server thread exiting with error " << e.what() << std::endl;
	}
}

void bl::network::server::BeyondLightServer::advancedSecuredTcpConnection(std::shared_ptr<bl::network::socket::ISocket> socket) {
	std::shared_ptr<socket::TcpBoostSslSocket> tcpSocket = std::dynamic_pointer_cast<socket::TcpBoostSslSocket>(socket);
	bool isLogged = false;
	std::string data;
	while (m_running && m_workingLoop && !isLogged) {
		data += tcpSocket->receive();
		while (data.find(newLineDelim) != data.npos) {
			auto line = data.substr(0, data.find(newLineDelim));
			data.erase(0, data.find(newLineDelim) + newLineDelim.length());
			if (line.find(this->msgStartHeader) != line.npos) {
				line = line.substr(line.find(this->msgStartHeader) + this->msgStartHeader.size());
			}
		}

	}
}

void bl::network::server::BeyondLightServer::readingThread(std::shared_ptr<bl::network::socket::ISocket> socket) {
	std::string data;
	bool isOpen = true;

	//std::cout << "Reading thread server launched" << std::endl;
	while (isOpen && m_running && m_workingLoop) {
		try {
			data += socket->receive();
			while (data.find(newLineDelim) != data.npos) {
				auto line = data.substr(0, data.find(newLineDelim));
				data.erase(0, data.find(newLineDelim) + newLineDelim.length());
				if (line.find(this->msgStartHeader) != line.npos) {
					line = line.substr(line.find(this->msgStartHeader) + this->msgStartHeader.size());
				}
				this->m_lines.push(std::make_pair(dynamic_cast<socket::UdpAsyncBoostSocket *>(socket.get())->getLastSenderEndpoint(), line));
				this->m_handler->notifyWatchers(socket::EWatcherType::WATCH_READ);
				this->m_handler->notifyWatchers(socket::EWatcherType::WATCH_ALL_WATCHER_READ_DONE);
			}
		} catch (boost::system::system_error const &e) {
			isOpen = false;
			std::cerr << "Exception in reading thread, quitting" << std::endl;
			std::cerr << e.what() << std::endl;
			this->m_handler->notifyWatchers(socket::EWatcherType::WATCH_QUIT);
			this->m_running = false;
			this->m_workingLoop = false;
		}
	}
}

void bl::network::server::BeyondLightServer::sendingThread(std::shared_ptr<bl::network::socket::ISocket> socket) {
	bool isOpen = true;

	//std::cout << "Sending thread server launched" << std::endl;
	while (isOpen && m_running && m_workingLoop) {
		try {
			while (!this->m_toSend.empty()) {
				dynamic_cast<socket::UdpAsyncBoostSocket *>(socket.get())->sendTo(this->m_toSend.front().second, this->m_toSend.front().first);
				//socket->send(this->m_toSend.front().second);
				this->m_toSend.pop();
				this->m_handler->notifyWatchers(socket::EWatcherType::WATCH_SEND);
				this->m_handler->notifyWatchers(socket::EWatcherType::WATCH_ALL_WATCHER_SEND_DONE);
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		} catch (std::exception const &) {
			isOpen = false;
			std::cerr << "Exception in sending thread, quitting" << std::endl;
			this->m_handler->notifyWatchers(socket::EWatcherType::WATCH_QUIT);
			this->m_running = false;
			this->m_workingLoop = false;
		}
	}
}

const std::pair<boost::asio::ip::udp::endpoint, std::string> &bl::network::server::BeyondLightServer::getLine() const {
	return this->m_lines.front();
}

void bl::network::server::BeyondLightServer::addToSend(std::string const &cmd, boost::asio::ip::udp::endpoint const &endpoint) {
	this->m_toSend.push(std::make_pair(endpoint, cmd));
}

void bl::network::server::BeyondLightServer::setLineToRead() {
	this->m_lines.pop();
}

std::pair<boost::asio::ip::udp::endpoint, std::string> bl::network::server::BeyondLightServer::getAndEraseLine() {
	auto line = this->getLine();
	this->setLineToRead();
	while (line.second.empty()) {
		line = this->getLine();
		this->setLineToRead();
	}
	return line;
}

/*TODO: remove old server
void bl::network::server::BeyondLightServer::mainLoop(std::shared_ptr<bl::network::socket::ISocket> socket) {
	auto users = ::server::user::RegisteredUsers::getInstance(); 
	//::bl::server::game::building::IBuilding *build = new ::bl::server::game::building::IronMine(<#initializer#>); TODO: build a planet instead
	::bl::server::game::planet::Planet planet;
	std::cout << "Main loop reached" << std::endl;
	bool loggedIn = false;
	while (m_running) {
		auto msg = socket->receive();
		while (msg.find("\r\n") == msg.npos) {
			msg += socket->receive();
		}
		msg = msg.substr(0, msg.find("\r\n"));
		auto toks = bl::common::Toolbox::split(msg, ":");
		std::cout << "Received " << msg << std::endl;
		if (!toks.empty()) {
			switch (std::atoi(toks[0].c_str())) {
				case 42:
					if (toks.size() == 3 && users->users.find(toks[1]) != users->users.end() && toks[2] == users->users[toks[1]]) {
						loggedIn = true;
						socket->send("123:OK");
					} else {
						socket->send("321:KO");
					}
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
						nlohmann::json sendingJson;
						sendingJson["buildings"] = (planet.serialize())["buildings"];
						std::string toSend = sendingJson.dump();
						std::cout << "Sending " << toSend << std::endl;
						socket->send("14242:" + toSend);
					} else {
						socket->send("321:KO");
					}
					break;
				case 3242:
					if (toks.size() == 1 && loggedIn) {
						planet.updateResources();
						nlohmann::json sendingJson;
						sendingJson["resources"] = (planet.serialize())["resources"];
						std::string toSend = sendingJson.dump();
						std::cout << "Sending " << toSend << std::endl;
						socket->send("324201:" + toSend);
					} else {
						socket->send("321:KO");
					}
					break;
				case 421356:
					if (toks.size() == 2 && loggedIn) {
						int buildingId = std::atoi(toks[1].c_str());
						if (!planet.tryToUpdateBuilding(buildingId)) {
							socket->send("321:KO");
						} else {
							socket->send("421357:" + toks[1] + ":" + std::to_string(planet.getBuildingInfo(buildingId)->getLevel()));
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
*/