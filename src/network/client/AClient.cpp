//
// Created by Guillaume on 02/10/2017.
//

#include <SocketFactory.hh>
#include <fstream>
#include "AClient.hh"

network::client::AClient::AClient(std::string const &factoryKey) : m_socket(socket::SocketFactory::getInstance()->create(factoryKey)){
	if (m_socket == nullptr)
		std::cerr << "Can't create socket client: invalid factory key" << std::endl;
	_hacking = false;
}

bool network::client::AClient::connectTo(const std::string &address, unsigned short port) {
	std::ofstream log("log.txt", std::ios::out | std::ios::app);
	log << "Calling connect" << std::endl;
	if (!this->m_socket->connect(address, port))
		return false;
	log << "Calling main loop" << std::endl;
	this->mainLoop();
	return true;
}

void network::client::AClient::disconnect() {

}
