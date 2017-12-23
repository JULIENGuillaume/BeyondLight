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

#include "AServerUdp.hh"
#include "ServerNetworkHandler.hh"

namespace bl {
	namespace network {
		namespace server {
			class BeyondLightServer : public AServerUdp {
			public:
				explicit BeyondLightServer(unsigned short port, bl::network::server::ServerNetworkHandler *handler);
			public:
				std::string const &getLine() const;
				void setLineToRead();
				std::string getAndEraseLine();
				void addToSend(std::string const &cmd);
			protected:
				void mainLoop(std::shared_ptr<bl::network::socket::ISocket> socket) override;
			private:
				void readingThread(std::shared_ptr<bl::network::socket::ISocket> socket);
				void sendingThread(std::shared_ptr<bl::network::socket::ISocket> socket);
			private:
				ServerNetworkHandler *m_handler;
				std::queue<std::string> m_toSend;
				std::queue<std::string> m_lines;
			private:
				std::vector<std::thread> m_activeThreads;
			private:
				const std::string newLineDelim = "\r\n";
			};
		}
	}
}
#endif //BEYONDLIGHT_BEYONDLIGHTSERVER_HH
