//
// Created by Guillaume on 02/10/2017.
//

#include <iostream>
#include "UdpAsyncBoostSocket.hh"
#include "SocketFactory.hh"
#include "AServerUdp.hh"

bl::network::server::AServerUdp::AServerUdp(std::string const &factoryKey, unsigned short port) : m_factoryKey(factoryKey), m_port(port) {
	for (size_t i = 0; i < this->maxSockets; ++i) {
		this->m_sockets.push_back(socket::SocketFactory::getInstance()->create(m_factoryKey));
		this->m_sockets.back()->openConnection(static_cast<unsigned short>(port + i + 1));
	}
}

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
		bool firstClient = true;
		size_t i = 0;
		//TODO: launch over a dedicated TCP socket, use it for auth / update, then assign a UDP socket, and close the TCP

		while (m_running) {
			serverSocket->receive();
			auto newClient = dynamic_cast<socket::UdpAsyncBoostSocket *>(serverSocket.get())->getLastSenderEndpoint();
			dynamic_cast<socket::UdpAsyncBoostSocket *>(serverSocket.get())->sendTo(std::to_string(i + this->m_port + 1), newClient);
			if (firstClient) {
				this->m_loopThread = std::make_shared<std::thread>(&AServerUdp::mainLoop, this, this->m_sockets[0]);
				firstClient = false;
			}
			auto clientId = newClient.address().to_string() + "|" + std::to_string(newClient.port());
			this->m_clients.insert(std::make_pair(clientId, newClient));
			i = (i + 1) % this->maxSockets;
		}
	} catch (std::exception &e) {
		std::cerr << "Server ended unexpectedly " << e.what() << std::endl;
	}
}

std::unordered_map<std::string, boost::asio::ip::udp::endpoint> &bl::network::server::AServerUdp::getClients() {
	return this->m_clients;
}

std::shared_ptr<std::thread> bl::network::server::AServerUdp::asyncRun() {
	return std::make_shared<std::thread>(&AServerUdp::run, this);
}

void bl::network::server::AServerUdp::stop() {
	m_running = false;
	m_loopThread->join();
	this->m_clients.clear();
}

void bl::network::server::AServerUdp::restart() {
	this->stop();
	this->run();
}

bool bl::network::server::AServerUdp::isRunning() {
	return m_running;
}
