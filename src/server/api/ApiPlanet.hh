//
// Created by Guillaume on 29/12/2017.
//

#ifndef BEYONDLIGHT_APIPLANET_HH
#define BEYONDLIGHT_APIPLANET_HH

#include <ServerMessage.hh>

namespace bl {
	namespace network {
		namespace client {
			class ClientMessage;
		}
	}
	namespace server {
		namespace api {
			class Api;
			class ApiPlanet {
			public:
				explicit ApiPlanet(Api &basicApi);
				bl::network::server::ServerMessage  execute(network::client::ClientMessage &message);
			private:
				bl::network::server::ServerMessage  getResourcesInfo(network::client::ClientMessage &message);

			private:
				Api &basicApi;
			};
		}
	}
}


#endif //BEYONDLIGHT_APIPLANET_HH
