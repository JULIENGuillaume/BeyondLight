//
// Created by Guillaume on 15/02/2018.
//

#ifndef BEYONDLIGHT_ACLIENTTCP_HH
#define BEYONDLIGHT_ACLIENTTCP_HH

#include <ISocket.hh>
#include "IClient.hh"

namespace bl {
	namespace network {
		namespace client {
			class AClientTcp : public IClient {
			public:
				explicit AClientTcp(std::string const &factoryKeyTcp);
				~AClientTcp() override;
			public:
				bool connectTo(
						const std::string &address,
						unsigned short port
				) override;
				void disconnect() override;
				std::shared_ptr<std::thread> asyncLaunch() override;
				void launch() override;
				bool isRunning() override;
				const std::string &getConnectedServer() const override;
			protected:
				std::shared_ptr<socket::ISocket> m_socket;
				bool m_running = false;
				std::string m_serverAdress;
				const std::string m_tcpSocketKey;
			};
		}
	}
}

#endif //BEYONDLIGHT_ACLIENTTCP_HH
