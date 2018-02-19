//
// Created by Guillaume on 29/12/2017.
//

#ifndef BEYONDLIGHT_API_HH
#define BEYONDLIGHT_API_HH

#include "ApiBuilding.hh"
#include "ApiPlanet.hh"
#include "ApiTechnology.hh"
#include "ApiUser.hh"

namespace bl {
	namespace network {
		namespace client {
			class ClientMessage;
		}
	}
	namespace server {
		class ServerCore;
		namespace api {
			enum class EApiType : int32_t {
				API_TYPE_UNKNOW,
				API_TYPE_BASIC,
				API_TYPE_BUILDING,
				API_TYPE_PLANET,
				API_TYPE_TECHNOLOGY,
				API_TYPE_USER
			};

			class Api {
			public:
				explicit Api(ServerCore &core);
				bl::network::server::ServerMessage  execute(network::client::ClientMessage &message);

				ServerCore &getCore();

			protected:
				bl::network::server::ServerMessage  basicApiExecution(network::client::ClientMessage &message);

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

/*
namespace std {

	template<>
	class hash<bl::server::api::EApiType> {
	public:
		std::size_t operator()(bl::server::api::EApiType const &key) const noexcept {
			std::cout << "hash< A::E >::operator()" << std::endl;
			return key;
		}

	};
}
*/
#endif //BEYONDLIGHT_API_HH
