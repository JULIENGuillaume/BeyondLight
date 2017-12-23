//
// Created by Guillaume on 02/10/2017.
//

#include <iostream>
#include "UdpAsyncBoostSocket.hh"
#include "SocketFactory.hh"
#include "AServerUdp.hh"

bl::network::server::AServerUdp::AServerUdp(std::string const &factoryKey, unsigned short port) : m_factoryKey(factoryKey), m_port(port) {}

void bl::network::server::AServerUdp::run() {
	try {
		std::shared_ptr<socket::ISocket> serverSocket = socket::SocketFactory::getInstance()->create(m_factoryKey);
		if (serverSocket == nullptr) {
			std::cerr << "Invalid key, cannot specialize the server on this socket" << std::endl;
			this->stop();
			return;
		}
		if (serverSocket->openConnection(m_port))
			m_running = true;
		std::cout << "Server is running" << std::endl;
		//TODO: launch over a dedicated TCP socket, use it for auth / update, then assign a UDP socket, and close the TCP
		while (m_running) {
			//std::cout << "Server is ready to receive new data" << std::endl;
			serverSocket->receive();
			//std::cout << "Server has received new data !" << std::endl;
			std::shared_ptr<socket::ISocket> newSocket = socket::SocketFactory::getInstance()->create(m_factoryKey);
			if (newSocket == nullptr) {
				std::cerr << "Invalid key, cannot specialize the server on this socket" << std::endl;
				this->stop();
				return;
			}
			auto newClient = dynamic_cast<socket::UdpAsyncBoostSocket *>(serverSocket.get())->getLastSenderEndpoint();
			std::cout << "A new client has been created !" << std::endl;
			newSocket->connect(newClient.address().to_string(), newClient.port());
			auto clientId = newClient.address().to_string();
			this->m_clientsIds.push_back(clientId);
			std::cout << "New client has been connected to !" << std::endl;
			this->m_clients.insert(std::make_pair(clientId, std::thread(&AServerUdp::mainLoop, this, newSocket)));
		}
		std::cout << "Server isn't running anymore" << std::endl;
	} catch (std::exception &e) {
		std::cout << "Server ended unexpectedly " << e.what() << std::endl;
		quick_exit(42);
	}
}

std::vector<std::string> bl::network::server::AServerUdp::getClientsIds() {
	return this->m_clientsIds;
}

std::shared_ptr<std::thread> bl::network::server::AServerUdp::asyncRun() {
	return std::make_shared<std::thread>(&AServerUdp::run, this);
}

void bl::network::server::AServerUdp::stop() {
	m_running = false;
	for (auto &client : this->m_clients) {
		client.second.join();
	}
	this->m_clients.clear();
}

void bl::network::server::AServerUdp::restart() {
	this->stop();
	this->run();
}

bool bl::network::server::AServerUdp::isRunning() {
	return m_running;
}
