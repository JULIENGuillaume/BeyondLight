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

network::server::BeyondLightServer::BeyondLightServer()
		: AServer(socket::serverKeyUdpSslAsyncBoostSocket) {

}
