//
// Created by Guillaume Julien on 13/02/2018.
//

#include <SocketFactory.hh>
#include <TcpBoostSslSocket.hh>
#include "UpdaterServer.hh"

bl::network::server::UpdaterServer::UpdaterServer(unsigned short port) : AServerTcp(
		socket::serverKeyTcpSslBoostSocket,
		port) {
}

void bl::network::server::UpdaterServer::mainLoop(std::shared_ptr<socket::ISocket> socket) {
	bool running = true;
	std::shared_ptr<socket::TcpBoostSslSocket> tcpSocket = std::dynamic_pointer_cast<socket::TcpBoostSslSocket>(socket);

	tcpSocket->handshake();
	while (running) {
		try {
			socket->send("Hello world");
		} catch (std::exception &e) {
			running = false;
			std::cerr << "Updater stopped: " << e.what() << std::endl; 
		}
	}
}
