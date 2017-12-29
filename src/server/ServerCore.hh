//
// Created by Guillaume on 23/12/2017.
//

#ifndef BEYONDLIGHT_SERVERCORE_HH
#define BEYONDLIGHT_SERVERCORE_HH

#include <ServerNetworkHandler.hh>
#include "storage/Database.hh"
#include "LoadedData.hh"

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
			const LoadedData &getData() const;
			LoadedData &getData();

		private:
			bl::network::server::ServerNetworkHandler m_serverNetworkHandler;
			bl::server::storage::Database m_database;
			bool m_isRunning = true;
			LoadedData m_data;
		};
	}
}


#endif //BEYONDLIGHT_SERVERCORE_HH
