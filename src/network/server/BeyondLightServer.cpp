/*
** BeyondLightServer.cpp for BeyondLight in /home/guillaume/delivery/BeyondLight/BeyondLightServer.cpp
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Tue Nov 07 14:42:17 2017 Guillaume Julien
** Last update Tue Nov 07 14:42:17 2017 Guillaume Julien
*/

#include <SocketFactory.hh>
#include "BeyondLightServer.hh"

network::server::BeyondLightServer::BeyondLightServer(unsigned short port) : AServerUdp(socket::serverKeyUdpSslAsyncBoostSocket, port) {

}

void network::server::BeyondLightServer::mainLoop(std::shared_ptr<network::socket::ISocket> socket) {
	std::cout << "Main loop reached" << std::endl;
	socket->send("Hello wolrd! ");
	std::cout << "End of server" << std::endl;
}
