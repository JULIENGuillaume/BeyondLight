//
// Created by Guillaume on 02/10/2017.
//

#include <SocketFactory.hh>
#include <fstream>
#include <UdpAsyncBoostSocket.hh>
#include "AClientUdp.hh"
#include "../../common/NetworkWrapper.hh"

bl::network::client::AClientUdp::AClientUdp(std::string const &factoryKey) : m_socket(socket::SocketFactory::getInstance()->create(factoryKey)) {
	if (m_socket == nullptr)
		std::cerr << "Can't create socket client: invalid factory key" << std::endl;
}

bool bl::network::client::AClientUdp::connectTo(const std::string &address, unsigned short port) {
	std::cout << "Client is trying to connect to " << address << " " << port << std::endl;
	if (!this->m_socket->connect(address, port))
		return false;
	std::cout << "Client has successfully connected to server" << std::endl;
	this->m_socket->receive();
	std::cout << "Client has completed handshake" << std::endl;
	dynamic_cast<socket::UdpAsyncBoostSocket *>(m_socket.get())->updateTargetEndpoint(
			dynamic_cast<socket::UdpAsyncBoostSocket *>(m_socket.get())->getLastSenderEndpoint());
	NetworkWrapper::m_socket = this->m_socket;
	m_running = true;
	return true;
}

void bl::network::client::AClientUdp::disconnect() {
	m_running = false;
}

std::shared_ptr<std::thread> bl::network::client::AClientUdp::asyncLaunch() {
	return std::make_shared<std::thread>(&AClientUdp::launch, this);
}

void bl::network::client::AClientUdp::launch() {
	try {
		this->mainLoop();
	} catch (std::exception &e) {
		std::cout << "Main loop has quit with " << e.what() << std::endl;
		quick_exit(42);
	}
}

bool bl::network::client::AClientUdp::isRunning() {
	return this->m_running;
}
