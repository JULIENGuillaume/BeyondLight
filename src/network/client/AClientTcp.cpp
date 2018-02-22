//
// Created by Guillaume on 15/02/2018.
//

#include <SocketFactory.hh>
#include <fstream>
#include <UdpAsyncBoostSocket.hh>
#include "AClientTcp.hh"

bl::network::client::AClientTcp::AClientTcp(std::string const &factoryKeyTcp) : m_socket(socket::SocketFactory::getInstance()->create(factoryKeyTcp)),
																				m_tcpSocketKey(factoryKeyTcp) {
}

bl::network::client::AClientTcp::~AClientTcp() {
	try {
		this->disconnect();
	} catch (...) {}
}

bool bl::network::client::AClientTcp::connectTo(
		const std::string &address,
		unsigned short port
) {
	if (!this->m_running) {
		m_running = true;
		if (!this->m_socket->connect(address, port))
			return false;
		this->m_serverAdress = address;
	} else {
		std::cerr << "You are already connected, please disconnect first" << std::endl;
	}
	return true;
}

void bl::network::client::AClientTcp::disconnect() {
	m_running = false;
	this->m_socket->close();
}

std::shared_ptr<std::thread> bl::network::client::AClientTcp::asyncLaunch() {
	return std::make_shared<std::thread>(&AClientTcp::launch, this);
}

void bl::network::client::AClientTcp::launch() {
	try {
		this->mainLoop();
	} catch (std::exception &e) {
		std::cerr << "Main loop has quit with " << e.what() << std::endl;
		return;
	}
}

bool bl::network::client::AClientTcp::isRunning() {
	return this->m_running;
}

const std::string &bl::network::client::AClientTcp::getConnectedServer() const {
	return this->m_serverAdress;
}
