//
// Created by Guillaume Julien on 13/02/2018.
//

#include <SocketFactory.hh>
#include "UpdaterServer.hh"

bl::network::server::UpdaterServer::UpdaterServer(unsigned short port) : AServerTcp(
		socket::serverKeyTcpSslBoostSocket,
		port){
}

void bl::network::server::UpdaterServer::mainLoop(std::shared_ptr<socket::ISocket> socket) {
	bool running = true;
	while (running) {
		try {
			socket->send("Hello world");
		} catch (std::exception &e) {
			running = false;
			std::cerr << "Updater stopped: " << e.what() << std::endl; 
		}
	}
}
