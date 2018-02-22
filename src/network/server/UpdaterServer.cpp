//
// Created by Guillaume Julien on 13/02/2018.
//

#include <boost/filesystem.hpp>
#include <fstream>
#include <SocketFactory.hh>
#include <TcpBoostSslSocket.hh>
#include "UpdaterServer.hh"

bl::network::server::UpdaterServer::UpdaterServer(unsigned short port) :
		AServerTcp(
				socket::serverKeyTcpSslBoostSocket,
				port) {
}

void bl::network::server::UpdaterServer::mainLoop(std::shared_ptr<socket::ISocket> socket) {
	std::shared_ptr<socket::TcpBoostSslSocket> tcpSocket = std::dynamic_pointer_cast<socket::TcpBoostSslSocket>(socket);
	tcpSocket->handshake();
	try {
		boost::filesystem::path path("./reference_dir");
		if (boost::filesystem::exists(path) && boost::filesystem::is_directory(path)) {
			for (boost::filesystem::directory_entry &x : boost::filesystem::directory_iterator(path)) {
				auto filePath = x.path();
				std::ifstream input(filePath.string(), std::ios::binary);
				if (input.is_open()) {
					std::string buffer((std::istreambuf_iterator<char>(input)),
											 (std::istreambuf_iterator<char>()));
					tcpSocket->send("42:" + filePath.filename().string() + ":" + std::to_string(buffer.size()));
					tcpSocket->directSend(buffer);
				}
			}
			tcpSocket->send("1337:All files have been send");
		} else {
			tcpSocket->send("1337:There is no file to be downloaded");
		}
	} catch (std::exception &e) {
		std::cerr << "Updater stopped: " << e.what() << std::endl;
	}
}
