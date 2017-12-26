//
// Created by Guillaume on 02/10/2017.
//

#ifndef KEYLOGGER_ACLIENT_HH
#define KEYLOGGER_ACLIENT_HH

#include <string>
#include "ISocket.hh"
#include "IClient.hh"

namespace bl {
	namespace network {
		namespace client {
			class AClientTcpUdp : public IClient {
			public:
				explicit AClientTcpUdp(std::string const &factoryKeyUdp,
				                       std::string const &factoryKeyTcp);
				~AClientTcpUdp() override;
			public:
				bool connectTo(
					const std::string &address,
					unsigned short port
				) override;
				void disconnect() override;
				std::shared_ptr<std::thread> asyncLaunch() override;
				void launch() override;
				bool isRunning() override;
				std::shared_ptr<std::thread> switchToUdp(const std::string &address, unsigned short port);
				const std::string &getConnectedServer() const override;
			protected:
				std::shared_ptr<socket::ISocket> m_socket;
				bool m_running = false;
				std::string m_serverAdress;
				const std::string m_tcpSocketKey;
				const std::string m_udpSocketKey;
			};
		}
	}
}

#endif //KEYLOGGER_ACLIENT_HH
