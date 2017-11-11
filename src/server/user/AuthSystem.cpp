/*
** AuthSystem.cpp for BeyondLight in /home/guillaume/delivery/BeyondLight/AuthSystem.cpp
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Thu Nov 09 17:59:05 2017 Guillaume Julien
** Last update Thu Nov 09 17:59:05 2017 Guillaume Julien
*/

#include <UdpSslAsyncBoostSocket.hh>
#include "AuthSystem.hh"

server::user::AuthSystem::AuthSystem() {

}

server::user::AuthSystem::~AuthSystem() {

}

bool server::user::AuthSystem::tryToAuthenticate() {
	const std::string realLogin = "root";
	const std::string realPassword = "bite";

	std::string login;
	std::string password;

	m_clientSocket->send("");

	return login == realLogin && password == realPassword;
}

void server::user::AuthSystem::setClientSocket(std::shared_ptr<network::socket::ISocket> &clientSocket) {
	auto p = std::dynamic_pointer_cast<network::socket::UdpSslAsyncBoostSocket>(clientSocket);
	this->m_clientSocket = clientSocket;
}
