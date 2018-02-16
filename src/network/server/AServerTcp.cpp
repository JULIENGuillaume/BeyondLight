//
// Created by Guillaume on 15/02/2018.
//

#include <iostream>
#include <SocketFactory.hh>
#include <TcpBoostAcceptor.hh>
#include "AServerTcp.hh"

bl::network::server::AServerTcp::AServerTcp(
		std::string const &factoryKeyTcp,
		unsigned short port
) : m_factoryKeyTcp(factoryKeyTcp),
	m_port(port) {
	m_running = true;
}

void bl::network::server::AServerTcp::run() {
	try {
		auto acceptor = std::shared_ptr<socket::IAcceptor>(new socket::TcpBoostAcceptor(m_port));

		while (m_running) {
			auto newSocket = socket::SocketFactory::getInstance()->create(m_factoryKeyTcp);
			acceptor->accept(newSocket);
			this->m_clientThreads.emplace_back(&AServerTcp::mainLoop, this, newSocket);
		}
	} catch (std::exception &e) {
		std::cerr << "Server ended unexpectedly " << e.what() << std::endl;
		m_running = false;
	}
}

void bl::network::server::AServerTcp::stop() {
	m_running = false;
	for (auto &thread : m_clientThreads) {
		thread.join();
	}
	this->m_clients.clear();
}

void bl::network::server::AServerTcp::restart() {
	this->stop();
	this->run();
}

std::shared_ptr<std::thread> bl::network::server::AServerTcp::asyncRun() {
	return std::make_shared<std::thread>(&AServerTcp::run, this);
}

bool bl::network::server::AServerTcp::isRunning() {
	return m_running;
}

std::unordered_map<std::string, boost::asio::ip::udp::endpoint> &bl::network::server::AServerTcp::getClients() {
	return m_clients;
}
