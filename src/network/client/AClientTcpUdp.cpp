//
// Created by Guillaume on 02/10/2017.
//

#include <SocketFactory.hh>
#include <fstream>
#include <UdpAsyncBoostSocket.hh>
#include "AClientTcpUdp.hh"

bl::network::client::AClientTcpUdp::AClientTcpUdp(
	std::string const &factoryKeyUdp,
	std::string const &factoryKeyTcp
) : m_socket(socket::SocketFactory::getInstance()->create(factoryKeyTcp)),
    m_tcpSocketKey(factoryKeyTcp),
    m_udpSocketKey(factoryKeyUdp) {
	if (m_socket == nullptr)
		std::cerr << "Can't create socket client: invalid factory key" << std::endl;
}

bool bl::network::client::AClientTcpUdp::connectTo(const std::string &address, unsigned short port) {
	if (!this->m_running) {
		if (!this->m_socket->connect(address, port))
			return false;
		this->m_serverAdress = address;
		/*auto str = this->m_socket->receive();
		while (str.find("\r\n") == str.npos) {
			str += this->m_socket->receive();
		}
		str = str.substr(std::string("#$BL-->").size());
		this->m_socket->connect(address, static_cast<unsigned short>(std::stoi(str)));*/
		/*dynamic_cast<socket::UdpAsyncBoostSocket *>(m_socket.get())->updateTargetEndpoint(
			dynamic_cast<socket::UdpAsyncBoostSocket *>(m_socket.get())->getLastSenderEndpoint());*/
		m_running = true;
	} else {
		std::cerr << "You are already connected, please disconnect first" << std::endl;
	}
	return true;
}

void bl::network::client::AClientTcpUdp::disconnect() {
	m_running = false;
	this->m_socket->close();
}

std::shared_ptr<std::thread> bl::network::client::AClientTcpUdp::asyncLaunch() {
	return std::make_shared<std::thread>(&AClientTcpUdp::launch, this);
}

void bl::network::client::AClientTcpUdp::launch() {
	try {
		this->mainLoop();
	} catch (std::exception &e) {
		std::cerr << "Main loop has quit with " << e.what() << std::endl;
	}
}

bool bl::network::client::AClientTcpUdp::isRunning() {
	return this->m_running;
}

std::shared_ptr<std::thread> bl::network::client::AClientTcpUdp::switchToUdp(const std::string &address, unsigned short port) {
	this->m_running = false;
	try {
		this->m_socket->close();
	} catch (std::exception const &e) {
		std::cerr << "Close socket: " << e.what() << std::endl;
	}
	try {
		this->m_socket = socket::SocketFactory::getInstance()->create(this->m_udpSocketKey);
		this->m_socket->connect(address, port);
	} catch (std::exception const &e) {
		std::cerr << "Connect socket: " << e.what() << std::endl;
	}
	this->m_running = true;
	return asyncLaunch();
}

const std::string &bl::network::client::AClientTcpUdp::getConnectedServer() const {
	return this->m_serverAdress;
}
