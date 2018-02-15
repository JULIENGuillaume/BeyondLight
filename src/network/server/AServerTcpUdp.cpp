//
// Created by Guillaume on 02/10/2017.
//

#include <iostream>
#include <TcpBoostAcceptor.hh>
#include "UdpAsyncBoostSocket.hh"
#include "SocketFactory.hh"
#include "AServerTcpUdp.hh"

bl::network::server::AServerTcpUdp::AServerTcpUdp(std::string const &factoryKeyUdp,
                                                  std::string const &factoryKeyTcp,
                                                  unsigned short port) : m_factoryKeyUdp(factoryKeyUdp),
                                                                         m_factoryKeyTcp(factoryKeyTcp),
                                                                         m_port(port) {
	m_running = true;
}

void bl::network::server::AServerTcpUdp::run() {
	try {
		for (size_t i = 0; i < this->maxSockets; ++i) {
			this->m_sockets.push_back(socket::SocketFactory::getInstance()->create(m_factoryKeyUdp));
			this->m_sockets.back()->openConnection(static_cast<unsigned short>(m_port + i + 1));
			this->m_loopThread.push_back(std::make_shared<std::thread>(&AServerTcpUdp::mainLoop, this, this->m_sockets[i]));
		}
		auto acceptor = std::shared_ptr<socket::IAcceptor>(new socket::TcpBoostAcceptor(m_port));

		while (m_running) {
			auto newSocket = socket::SocketFactory::getInstance()->create(m_factoryKeyTcp);
			acceptor->accept(newSocket);
			this->m_loggingClients.emplace_back(&AServerTcpUdp::advancedSecuredTcpConnection, this, newSocket);
		}
	} catch (std::exception &e) {
		std::cerr << "Server ended unexpectedly " << e.what() << std::endl;
	}
}

std::unordered_map<std::string, boost::asio::ip::udp::endpoint> &bl::network::server::AServerTcpUdp::getClients() {
	return this->m_clients;
}

std::shared_ptr<std::thread> bl::network::server::AServerTcpUdp::asyncRun() {
	return std::make_shared<std::thread>(&AServerTcpUdp::run, this);
}

void bl::network::server::AServerTcpUdp::stop() {
	m_running = false;
	for (const auto &thread : m_loopThread) {
		thread->join();
	}
	this->m_clients.clear();
}

void bl::network::server::AServerTcpUdp::restart() {
	this->stop();
	this->run();
}

bool bl::network::server::AServerTcpUdp::isRunning() {
	return m_running;
}

void bl::network::server::AServerTcpUdp::sendUdpSocketPort(const std::shared_ptr<bl::network::socket::ISocket> &socket) {
	socket->send(std::to_string(this->m_actualPort + this->m_port + 1)); //TODO send in a message
	this->m_actualPort = (this->m_actualPort + 1) % this->maxSockets;
}
