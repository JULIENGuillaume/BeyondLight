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
#include "ISocket.hh"

namespace bl {
	namespace network {
		namespace server {
			class AServerTcpUdp : public IServer {
			public:
				explicit AServerTcpUdp(
					std::string const &factoryKeyUdp,
					std::string const &factoryKeyTcp,
						unsigned short port
				);
				~AServerTcpUdp() override = default;
			public:
				void run() override;
				void stop() override;
				void restart() override;
				std::shared_ptr<std::thread> asyncRun() override;
				bool isRunning() override;
				std::unordered_map<std::string, boost::asio::ip::udp::endpoint>& getClients() override;
			protected:
				bool m_running = false;
				const size_t maxSockets = 1; //TODO: check how to make it work with more sockets
				std::vector<std::shared_ptr<bl::network::socket::ISocket>> m_sockets;
			private:
				std::string const m_factoryKeyUdp;
				std::string const m_factoryKeyTcp;
				unsigned short m_port;
			private:
				std::unordered_map<std::string, boost::asio::ip::udp::endpoint> m_clients;
				std::shared_ptr<std::thread> m_loopThread;
			};
		}
	}
}

#endif //KEYLOGGER_ASERVER_HH
