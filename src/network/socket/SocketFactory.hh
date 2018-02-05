//
// Created by Guillaume on 02/10/2017.
//

#ifndef KEYLOGGER_SOCKETFACTORY_HH
#define KEYLOGGER_SOCKETFACTORY_HH

#include "../../common/pattern/PFactory.hpp"
#include "../../common/pattern/PSingleton.hpp"

namespace bl {
	namespace network {
		namespace socket {
			class ISocket;
			const std::string defaultKeyTcpBoostSocket = "TCP_BOOST_SOCKET_TCP_DEFAULT_KEY";
			const std::string clientKeyTcpSslBoostSocket = "TCP_BOOST_SOCKET_SSL_CLIENT_KEY";
			const std::string serverKeyTcpSslBoostSocket = "TCP_BOOST_SOCKET_SSL_SERVER_KEY";
			const std::string clientKeyUdpAsyncBoostSocket = "UDP_BOOST_SOCKET_ASYNC_CLIENT_KEY";
			const std::string serverKeyUdpAsyncBoostSocket = "UDP_BOOST_SOCKET_ASYNC_SERVER_KEY";

			class SocketFactory :
					public bl::common::pattern::PFactory<ISocket>,
					public bl::common::pattern::PSingleton<SocketFactory> {
			public:
				SocketFactory() = default;
				~SocketFactory() override = default;
			};
		}
	}
}

#endif //KEYLOGGER_SOCKETFACTORY_HH
