//
// Created by Guillaume on 29/12/2017.
//

#include "Api.hh"

bl::server::api::Api::Api(bl::server::ServerCore &core) :
	m_core(core),
	m_apiBuilding(*this),
	m_apiPlanet(*this),
	m_apiTechnology(*this),
	m_apiUser(*this) {}

void bl::server::api::Api::execute(bl::network::client::ClientMessage message) {

}

bl::server::ServerCore &bl::server::api::Api::getCore() {
	return m_core;
}
