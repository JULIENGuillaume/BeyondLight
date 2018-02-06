//
// Created by Guillaume on 23/12/2017.
//

#ifndef BEYONDLIGHT_SERVERNETWORKHANDLER_HH
#define BEYONDLIGHT_SERVERNETWORKHANDLER_HH

#include <ANetworkHandler.hh>
#include <boost/asio/ip/udp.hpp>
#include "../client/ClientMessage.hh"
#include "ServerMessage.hh"
#include "IServer.hh"
#include "../../server/LoadedData.hh"

namespace bl {
	namespace network {
		namespace server {
			class ServerNetworkHandler : public socket::ANetworkHandler  {
			public:
				explicit ServerNetworkHandler(unsigned short port, ::bl::server::LoadedData &data);
				~ServerNetworkHandler() override = default;
			public:
				std::string getLine() override;
				std::pair<boost::asio::ip::udp::endpoint, std::string> getLineFrom();
				std::pair<boost::asio::ip::udp::endpoint, client::ClientMessage> getMessage();
				void send(std::string const &cmd) override;
				void send(ServerMessage const& msg, boost::asio::ip::udp::endpoint const& endpoint);
				void send(ServerMessageType type, uint64_t code, std::string const& msg, boost::asio::ip::udp::endpoint const& endpoint);

			public:
				std::unordered_map<std::string, boost::asio::ip::udp::endpoint>& getListClient();

			protected:
				void retrieveLine() override;
			private:
				std::shared_ptr<IServer> m_networkServer;
				std::shared_ptr<std::thread> m_networkThread;
				std::queue<std::pair<boost::asio::ip::udp::endpoint, std::string>> m_linesFrom;
				::bl::server::LoadedData &m_data;
			};
		}
	}
}


#endif //BEYONDLIGHT_SERVERNETWORKHANDLER_HH
