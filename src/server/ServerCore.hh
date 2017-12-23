//
// Created by Guillaume on 23/12/2017.
//

#ifndef BEYONDLIGHT_SERVERCORE_HH
#define BEYONDLIGHT_SERVERCORE_HH

#include <ServerNetworkHandler.hh>

namespace bl {
	namespace server {
		class ServerCore {
		public:
			ServerCore();

		public:
			void start();

		private:
			bl::network::server::ServerNetworkHandler m_serverNetworkHandler;
			bool m_isRunning = true;
		};
	}
}


#endif //BEYONDLIGHT_SERVERCORE_HH
