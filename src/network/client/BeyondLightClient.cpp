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
#include "../../../client/MainHandler.hh"

network::client::BeyondLightClient::BeyondLightClient() : AClientUdp(socket::clientKeyUdpSslAsyncBoostSocket) {}

void network::client::BeyondLightClient::mainLoop() {
	MainHandler mainHandler;
	std::cout << "Client is in the main loop" << std::endl;
	mainHandler.init();
	mainHandler.createBrowser();
	std::cout << "Browser created" << std::endl;
	mainHandler.startMainLoop();
	mainHandler.destroy();
}
