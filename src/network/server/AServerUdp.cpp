//
// Created by Guillaume on 02/10/2017.
//

#include <iostream>
#include "UdpSslAsyncBoostSocket.hh"
#include "SocketFactory.hh"
#include "AServerUdp.hh"

bl::network::server::AServerUdp::AServerUdp(std::string const &factoryKey, unsigned short port) : m_factoryKey(factoryKey), m_port(port) {}

void bl::network::server::AServerUdp::run() {
	std::shared_ptr<socket::ISocket> serverSocket = socket::SocketFactory::getInstance()->create(m_factoryKey);
	if (serverSocket == nullptr) {
		std::cerr << "Invalid key, cannot specialize the server on this socket" << std::endl;
		this->stop();
		return;
	}
	if (serverSocket->openConnection(m_port))
		running = true;
	std::cout << "Server is running" << std::endl;
	while (running) {
		serverSocket->receive();
		std::shared_ptr<socket::ISocket> newSocket = socket::SocketFactory::getInstance()->create(m_factoryKey);
		if (newSocket == nullptr) {
			std::cerr << "Invalid key, cannot specialize the server on this socket" << std::endl;
			this->stop();
			return;
		}
		auto newClient = dynamic_cast<socket::UdpSslAsyncBoostSocket*>(serverSocket.get())->getLastSenderEndpoint();
		newSocket->connect(newClient.address().to_string(), newClient.port());
		this->m_clients.emplace_back(&AServerUdp::mainLoop, this, newSocket);
	}
}

void bl::network::server::AServerUdp::stop() {
	running = false;
	for (std::thread &thread : this->m_clients) {
		thread.join();
	}
	this->m_clients.clear();
}

void bl::network::server::AServerUdp::restart() {
	this->stop();
	this->run();
}
