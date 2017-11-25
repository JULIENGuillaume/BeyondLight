//
// Created by Guillaume on 02/10/2017.
//

#include <SocketFactory.hh>
#include <fstream>
#include <UdpSslAsyncBoostSocket.hh>
#include "AClientUdp.hh"
#include "../../common/NetworkWrapper.hh"

network::client::AClientUdp::AClientUdp(std::string const &factoryKey) : m_socket(socket::SocketFactory::getInstance()->create(factoryKey)) {
	if (m_socket == nullptr)
		std::cerr << "Can't create socket client: invalid factory key" << std::endl;
}

bool network::client::AClientUdp::connectTo(const std::string &address, unsigned short port) {
	if (!this->m_socket->connect(address, port))
		return false;
	this->m_socket->receive();
	dynamic_cast<socket::UdpSslAsyncBoostSocket *>(m_socket.get())->updateTargetEndpoint(
			dynamic_cast<socket::UdpSslAsyncBoostSocket *>(m_socket.get())->getLastSenderEndpoint());
	NetworkWrapper::m_socket = this->m_socket;
	m_running = true;
	return true;
}

void network::client::AClientUdp::disconnect() {
	m_running = false;
}

std::shared_ptr<std::thread> network::client::AClientUdp::asyncLaunch() {
	return std::make_shared<std::thread>(&AClientUdp::launch, this);
}

void network::client::AClientUdp::launch() {
	this->mainLoop();
}
