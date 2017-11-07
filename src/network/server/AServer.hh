//
// Created by Guillaume on 02/10/2017.
//

#ifndef KEYLOGGER_ASERVER_HH
#define KEYLOGGER_ASERVER_HH

#include <memory>
#include <vector>
#include <thread>
#include "ISocket.hh"
#include "IServer.hh"

namespace network {
	namespace server {
		class AServer : public IServer {
		public:
			explicit AServer(std::string const &factoryKey);
			~AServer() override = default;

		public:
			void run() override;
			void stop() override;
			void restart() override;

		private:
			std::string const m_factoryKey;
		private:
			std::vector<std::thread> m_clients;
			bool running = false;
		};
	}
}

#endif //KEYLOGGER_ASERVER_HH
