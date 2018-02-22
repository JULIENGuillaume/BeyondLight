//
// Created by Guillaume on 15/02/2018.
//

#ifndef BEYONDLIGHT_ASERVERTCP_HH
#define BEYONDLIGHT_ASERVERTCP_HH

#include "IServer.hh"

namespace bl {
	namespace network {
		namespace server {
			class AServerTcp : public IServer {
			public:
				explicit AServerTcp(
				std::string const &factoryKeyTcp,
				unsigned short port
				);
				~AServerTcp() override = default;
			public:
				void run() override;
				void stop() override;
				void restart() override;
				std::shared_ptr<std::thread> asyncRun() override;
				bool isRunning() override;
				std::unordered_map<std::string, boost::asio::ip::udp::endpoint>& getClients() override;
			protected:
				bool m_running = false;
			private:
				std::string const m_factoryKeyTcp;
				unsigned short m_port;
			private:
				std::unordered_map<std::string, boost::asio::ip::udp::endpoint> m_clients;
				std::vector<std::thread> m_clientThreads;
			};
		}
	}
}

#endif //BEYONDLIGHT_ASERVERTCP_HH
