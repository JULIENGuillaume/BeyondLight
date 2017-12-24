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
		bool firstClient = true;

		//TODO: launch over a dedicated TCP socket, use it for auth / update, then assign a UDP socket, and close the TCP


		while (m_running) {
			//std::cout << "Server is ready to receive new data" << std::endl;
			serverSocket->receive();
			std::shared_ptr<socket::ISocket> newSocket = socket::SocketFactory::getInstance()->create(m_factoryKey);
			if (newSocket == nullptr) {
				std::cerr << "Invalid key, cannot specialize the server on this socket" << std::endl;
				this->stop();
				return;
			}
			auto newClient = dynamic_cast<socket::UdpAsyncBoostSocket *>(serverSocket.get())->getLastSenderEndpoint();
			//std::cout << "Server has received new data !" << std::endl;
			newSocket->connect(newClient.address().to_string(), newClient.port());
			if (firstClient) {
				this->m_loopThread = std::make_shared<std::thread>(&AServerUdp::mainLoop, this, newSocket);
				firstClient = false;
			}
			auto clientId = newClient.address().to_string() + "|" + std::to_string(newClient.port());
			this->m_clients.insert(std::make_pair(clientId, newClient));
		}
		std::cout << "Server isn't running anymore" << std::endl;
	} catch (std::exception &e) {
		std::cout << "Server ended unexpectedly " << e.what() << std::endl;
		quick_exit(42);
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
