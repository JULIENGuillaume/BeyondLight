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
#include "../../client/ServerApiHelper.hh"

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
				void setSessionId(std::string const& sessionId);
				std::string getLine() override;
				server::ServerMessage getMessage();
				void send(std::string const &cmd) override;
				void send(ClientMessageType type,
				          bl::server::api::EApiType apiRequestType,
				          uint64_t code,
				          std::string const& msg);
				void send(ClientMessage const& msg);

			public:
				void swapToUdp(unsigned short port);
				const std::shared_ptr<bl::client::ServerApiHelper> &getApiHelper() const;

			protected:
				void retrieveLine() override;
				void directSend(std::string const &cmd);
				void directSend(ClientMessageType type, uint64_t code, std::string const& msg);
			private:
				std::shared_ptr<IClient> m_networkClient;
				std::shared_ptr<std::thread> m_networkThread;
				std::shared_ptr<::bl::client::ServerApiHelper> m_apiHelper;
				std::string m_sessionId;
				static bool creationAllowed;
			};
		}
	}
}

#endif //BEYONDLIGHT_NETWORKHANDLER_HH
