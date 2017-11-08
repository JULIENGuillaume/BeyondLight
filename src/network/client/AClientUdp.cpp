//
// Created by Guillaume on 02/10/2017.
//

#include <SocketFactory.hh>
#include <fstream>
#include "AClientUdp.hh"

network::client::AClientUdp::AClientUdp(std::string const &factoryKey) : m_socket(socket::SocketFactory::getInstance()->create(factoryKey)){
	if (m_socket == nullptr)
		std::cerr << "Can't create socket client: invalid factory key" << std::endl;
	_hacking = false;
}

bool network::client::AClientUdp::connectTo(const std::string &address, unsigned short port) {
	if (!this->m_socket->connect(address, port))
		return false;
	this->m_socket->receive();
	this->mainLoop();
	return true;
}

void network::client::AClientUdp::disconnect() {

}
