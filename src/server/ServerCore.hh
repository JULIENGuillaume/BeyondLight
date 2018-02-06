//
// Created by Guillaume on 23/12/2017.
//

#ifndef BEYONDLIGHT_SERVERCORE_HH
#define BEYONDLIGHT_SERVERCORE_HH

#include <ServerNetworkHandler.hh>
#include "storage/Database.hh"
#include "LoadedData.hh"
#include "ModelData.hh"

namespace bl {
	namespace server {
		class ServerCore {
		public:
			ServerCore();

		public:
			void start();

		public:
			const network::server::ServerNetworkHandler &getServerNetworkHandler() const;
			network::server::ServerNetworkHandler &getServerNetworkHandler();
			const storage::Database &getDatabase() const;
			storage::Database &getDatabase();
			static LoadedData &getData();
			static ModelData &getModels();

		private:
			void executeCommand(std::pair<boost::asio::ip::udp::endpoint, bl::network::client::ClientMessage> msg, api::Api &refApi);

		private:
			bl::network::server::ServerNetworkHandler m_serverNetworkHandler;
			bl::server::storage::Database m_database;
			bool m_isRunning = true;
			static LoadedData m_data;
			static ModelData m_models;
		};
	}
}


#endif //BEYONDLIGHT_SERVERCORE_HH
