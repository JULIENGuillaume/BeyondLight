/*
** BeyondLightServer.hh for BeyondLight in /home/guillaume/delivery/BeyondLight/BeyondLightServer.hh
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Tue Nov 07 14:42:17 2017 Guillaume Julien
** Last update Tue Nov 07 14:42:17 2017 Guillaume Julien
*/

#ifndef BEYONDLIGHT_BEYONDLIGHTSERVER_HH
#define BEYONDLIGHT_BEYONDLIGHTSERVER_HH

#include <boost/asio/ip/udp.hpp>
#include "AServerTcpUdp.hh"
#include "ServerNetworkHandler.hh"

namespace bl {
	namespace network {
		namespace server {
			class BeyondLightServer : public AServerTcpUdp {
			public:
				explicit BeyondLightServer(unsigned short port, bl::network::server::ServerNetworkHandler *handler);
			public:
				const std::pair<boost::asio::ip::udp::endpoint, std::string> & getLine() const;
				void setLineToRead();
				std::pair<boost::asio::ip::udp::endpoint, std::string> getAndEraseLine();
				void addToSend(std::string const &cmd, boost::asio::ip::udp::endpoint const &endpoint);
			protected:
				void mainLoop(std::shared_ptr<bl::network::socket::ISocket> socket) override;
			private:
				void readingThread(std::shared_ptr<bl::network::socket::ISocket> socket);
				void sendingThread(std::shared_ptr<bl::network::socket::ISocket> socket);
			private:
				ServerNetworkHandler *m_handler;
				std::queue<std::pair<boost::asio::ip::udp::endpoint, std::string>> m_toSend;
				std::queue<std::pair<boost::asio::ip::udp::endpoint, std::string>> m_lines;
			private:
				std::vector<std::thread> m_activeThreads;
			private:
				const std::string newLineDelim = "\r\n";
				const std::string msgStartHeader = "#$BL-->";
			};
		}
	}
}
#endif //BEYONDLIGHT_BEYONDLIGHTSERVER_HH
