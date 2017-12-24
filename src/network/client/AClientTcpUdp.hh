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
				explicit AClientTcpUdp(const std::string &factoryKey);
				~AClientTcpUdp() override = default;
			public:
				bool connectTo(
						const std::string &address,
						unsigned short port
				) override;
				void disconnect() override;
				std::shared_ptr<std::thread> asyncLaunch() override;
				void launch() override;
				bool isRunning() override;
			protected:
				std::shared_ptr<socket::ISocket> m_socket;
				bool m_running = false;
			};
		}
	}
}

#endif //KEYLOGGER_ACLIENT_HH
