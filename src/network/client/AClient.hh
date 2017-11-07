//
// Created by Guillaume on 02/10/2017.
//

#ifndef KEYLOGGER_ACLIENT_HH
#define KEYLOGGER_ACLIENT_HH

#include <string>
#include "ISocket.hh"
#include "IClient.hh"

namespace network {
	namespace client {
		class AClient : public IClient {
		public:
			explicit AClient(const std::string &factoryKey);
			~AClient() override = default;

		public:
			bool connectTo(const std::string &address, unsigned short port) override;
			void disconnect() override;

		protected:
			std::shared_ptr<socket::ISocket> m_socket;
			bool _hacking;
		};
	}
}

#endif //KEYLOGGER_ACLIENT_HH
