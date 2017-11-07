//
// Created by Guillaume on 02/10/2017.
//

#ifndef KEYLOGGER_SOCKETFACTORY_HH
#define KEYLOGGER_SOCKETFACTORY_HH

#include "ISocket.hh"
#include "PFactory.hpp"
#include "PSingleton.hpp"

namespace network {
	namespace socket {

		const std::string defaultKeyTcpBoostSocket = "TCP_BOOST_SOCKET_TCP_DEFAULT_KEY";
		const std::string clientKeyTcpSslBoostSocket = "TCP_BOOST_SOCKET_TCP_SSL_CLIENT_KEY";
		const std::string serverKeyTcpSslBoostSocket = "TCP_BOOST_SOCKET_TCP_SSL_SERVER_KEY";
		const std::string clientKeyUdpSslAsyncBoostSocket = "TCP_BOOST_SOCKET_UDP_SSL_ASYNC_CLIENT_KEY";
		const std::string serverKeyUdpSslAsyncBoostSocket = "TCP_BOOST_SOCKET_UDP_SSL_ASYNC_SERVER_KEY";

		class SocketFactory : public pattern::PFactory<ISocket>, public pattern::PSingleton<SocketFactory> {
		public:
			SocketFactory() = default;
			~SocketFactory() override = default;
		};
	}
}

#endif //KEYLOGGER_SOCKETFACTORY_HH
