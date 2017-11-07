//
// Created by Guillaume on 02/10/2017.
//

#include <iostream>
#include "SocketFactory.hh"
#include "AServer.hh"

network::server::AServer::AServer(std::string const &factoryKey) : m_factoryKey(factoryKey) {}

void network::server::AServer::run() {
	running = true;
	while (running) {
		std::shared_ptr<socket::ISocket> newSocket = socket::SocketFactory::getInstance()->create(m_factoryKey);
		if (newSocket == nullptr) {
			std::cerr << "Invalid key, cannot specialize the server on this socket" << std::endl;
			this->stop();
		}
		this->m_clients.emplace_back(&AServer::mainLoop, this, newSocket);
	}
}

void network::server::AServer::stop() {
	running = false;
	for (std::thread &thread : this->m_clients) {
		thread.join();
	}
	this->m_clients.clear();
}

void network::server::AServer::restart() {
	this->stop();
	this->run();
}
