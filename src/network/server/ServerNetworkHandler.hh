//
// Created by Guillaume on 23/12/2017.
//

#ifndef BEYONDLIGHT_SERVERNETWORKHANDLER_HH
#define BEYONDLIGHT_SERVERNETWORKHANDLER_HH

#include <ANetworkHandler.hh>
#include "ServerMessage.hh"
#include "IServer.hh"

namespace bl {
	namespace network {
		namespace server {
			class ServerNetworkHandler : public socket::ANetworkHandler  {
			public:
				explicit ServerNetworkHandler(unsigned short port = 4224);
				~ServerNetworkHandler() override = default;
			public:
				std::string getLine() override;
				void send(std::string const &cmd) override;
				void send(ServerMessageType type, uint64_t code, std::string const& msg);

			protected:
				void retrieveLine() override;
			private:
				std::shared_ptr<IServer> m_networkServer;
				std::shared_ptr<std::thread> m_networkThread;
			};
		}
	}
}


#endif //BEYONDLIGHT_SERVERNETWORKHANDLER_HH
