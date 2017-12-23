//
// Created by Guillaume on 02/10/2017.
//

#ifndef KEYLOGGER_ASERVER_HH
#define KEYLOGGER_ASERVER_HH

#include <memory>
#include <vector>
#include <thread>
#include <unordered_map>
#include "IServer.hh"

namespace bl {
	namespace network {
		namespace server {
			class AServerUdp : public IServer {
			public:
				explicit AServerUdp(
						std::string const &factoryKey,
						unsigned short port
				);
				~AServerUdp() override = default;
			public:
				void run() override;
				void stop() override;
				void restart() override;
				std::shared_ptr<std::thread> asyncRun() override;
				bool isRunning() override;
				std::vector<std::string> getClientsIds() override;
			protected:
				bool m_running = false;
			private:
				std::string const m_factoryKey;
				unsigned short m_port;
			private:
				std::unordered_map<std::string, std::thread> m_clients;
				std::vector<std::string> m_clientsIds;
			};
		}
	}
}

#endif //KEYLOGGER_ASERVER_HH
