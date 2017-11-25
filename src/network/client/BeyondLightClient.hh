/*
** BeyondLightClient.hh for BeyondLight in /home/guillaume/delivery/BeyondLight/BeyondLightClient.hh
**
** Made by Guillaume Julien
** Login   <guillaume.julien@epitech.eu>
**
** Started on  Tue Nov 07 14:43:06 2017 Guillaume Julien
** Last update Tue Nov 07 14:43:06 2017 Guillaume Julien
*/

#ifndef BEYONDLIGHT_BEYONDLIGHTCLIENT_HH
#define BEYONDLIGHT_BEYONDLIGHTCLIENT_HH

#include <queue>
#include "AClientUdp.hh"
#include "NetworkHandler.hh"

namespace network {
	namespace client {
		class BeyondLightClient : public AClientUdp {
		public:
			explicit BeyondLightClient(network::client::NetworkHandler *handler);

		public:
			std::string const& getLine() const;
			void setLineToRead();
			std::string const& getAndEraseLine();
			void addToSend(std::string const& cmd);
			void disconnect() override;

		protected:
			void mainLoop() override;

		private:
			void readingThread();
			void sendingThread();

		private:
			NetworkHandler *m_handler;
			std::queue<std::string> m_toSend;
			std::queue<std::string> m_lines;

		private:
			std::vector<std::thread> m_activeThreads;

		private:
			const std::string newLineDelim = "\r\n";
		};
	}
}


#endif //BEYONDLIGHT_BEYONDLIGHTCLIENT_HH
