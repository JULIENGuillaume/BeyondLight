//
// Created by Guillaume on 29/12/2017.
//

#ifndef BEYONDLIGHT_API_HH
#define BEYONDLIGHT_API_HH

#include "../ServerCore.hh"
#include "ApiBuilding.hh"
#include "ApiPlanet.hh"
#include "ApiTechnology.hh"
#include "ApiUser.hh"

namespace bl {
	namespace server {
		namespace api {
			class Api {
			public:
				explicit Api(ServerCore &core);
				void execute(network::client::ClientMessage message);

				ServerCore &getCore();

			private:
				ServerCore &m_core;
				ApiBuilding m_apiBuilding;
				ApiPlanet m_apiPlanet;
				ApiTechnology m_apiTechnology;
				ApiUser m_apiUser;
			};
		}
	}
}


#endif //BEYONDLIGHT_API_HH
