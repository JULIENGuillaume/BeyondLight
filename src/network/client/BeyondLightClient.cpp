/*
** BeyondLightClient.cpp for BeyondLight in /home/guillaume/delivery/BeyondLight/BeyondLightClient.cpp
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Tue Nov 07 14:43:06 2017 Guillaume Julien
** Last update Tue Nov 07 14:43:06 2017 Guillaume Julien
*/

#include "SocketFactory.hh"
#include "BeyondLightClient.hh"

network::client::BeyondLightClient::BeyondLightClient() : AClientUdp(socket::clientKeyUdpSslAsyncBoostSocket) {}

void network::client::BeyondLightClient::mainLoop() {
	std::cout << "Client is in the main loop" << std::endl;
	std::cout << this->m_socket->receive() << std::endl;
	std::cout << this->m_socket->receive() << std::endl;
}
