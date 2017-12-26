//
// Created by diguie_t on 11/23/2017.
//

#ifndef BEYONDLIGHT_NETWORKHANDLER_HH
#define BEYONDLIGHT_NETWORKHANDLER_HH

#include <future>
#include <string>
#include <map>
#include <queue>
#include <ANetworkHandler.hh>
#include <ServerMessage.hh>
#include "IClient.hh"
#include "ClientMessage.hh"

namespace bl {
	namespace network {
		namespace client {
			class ClientNetworkHandler : public socket::ANetworkHandler {
			public:
				explicit ClientNetworkHandler(
						std::string const &ip = "127.0.0.1",
						unsigned short port = 4224
				);
				~ClientNetworkHandler() override;
			public:
				std::string getLine() override;
				server::ServerMessage getMessage();
				void send(std::string const &cmd) override;
				void send(ClientMessageType type, uint64_t code, std::string const& msg);

			public:
				void swapToUdp(unsigned short port);

			protected:
				void retrieveLine() override;
			private:
				std::shared_ptr<IClient> m_networkClient;
				std::shared_ptr<std::thread> m_networkThread;
				static bool creationAllowed;
			};
		}
	}
}

#endif //BEYONDLIGHT_NETWORKHANDLER_HH
