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
#include "../../server/LoggingHelper.hh"

bl::network::server::BeyondLightServer::BeyondLightServer(unsigned short port, bl::network::server::ServerNetworkHandler *handler, ::bl::server::LoadedData &data) :
	AServerTcpUdp(socket::serverKeyUdpAsyncBoostSocket,
	              socket::serverKeyTcpSslBoostSocket,
	              port),
	m_handler(handler),
	m_data(data) {
}

void bl::network::server::BeyondLightServer::mainLoop(std::shared_ptr<bl::network::socket::ISocket> socket) {
	try {
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
	try {
		std::shared_ptr<socket::TcpBoostSslSocket> tcpSocket = std::dynamic_pointer_cast<socket::TcpBoostSslSocket>(socket);
		::bl::server::LoggingHelper helper(tcpSocket, this->m_data);
		bool isLogged = false;
		std::string data;

		tcpSocket->handshake();
		while (m_running && m_workingLoop && !isLogged) {
			data += tcpSocket->receive();
			while (data.find(newLineDelim) != data.npos) {
				auto line = data.substr(0, data.find(newLineDelim));
				data.erase(0, data.find(newLineDelim) + newLineDelim.length());
				if (line.find(this->msgStartHeader) != line.npos) {
					line = line.substr(line.find(this->msgStartHeader) + this->msgStartHeader.size());
				}
				isLogged = helper.executeCommand(line);
			}
		}
		if (isLogged) {
			this->sendUdpSocketPort(socket);
			tcpSocket->close();
			return;
		}
	} catch (std::exception const&) {
		return;
	}
}

void bl::network::server::BeyondLightServer::readingThread(std::shared_ptr<bl::network::socket::ISocket> socket) {
	std::string data;

	while (m_running && m_workingLoop) {
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
		} catch (boost::system::system_error const &) {}
	}
}

void bl::network::server::BeyondLightServer::sendingThread(std::shared_ptr<bl::network::socket::ISocket> socket) {
	while (m_running && m_workingLoop) {
		try {
			while (!this->m_toSend.empty()) {
				dynamic_cast<socket::UdpAsyncBoostSocket *>(socket.get())->sendTo(this->m_toSend.front().second, this->m_toSend.front().first);
				this->m_toSend.pop();
				this->m_handler->notifyWatchers(socket::EWatcherType::WATCH_SEND);
				this->m_handler->notifyWatchers(socket::EWatcherType::WATCH_ALL_WATCHER_SEND_DONE);
			}
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		} catch (std::exception const &) {}
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