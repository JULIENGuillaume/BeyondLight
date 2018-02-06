//
// Created by Guillaume on 29/12/2017.
//

#include "../ServerCore.hh"
#include "Api.hh"

bl::server::api::Api::Api(bl::server::ServerCore &core) :
	m_core(core),
	m_apiBuilding(*this),
	m_apiPlanet(*this),
	m_apiTechnology(*this),
	m_apiUser(*this) {}

bl::network::server::ServerMessage bl::server::api::Api::execute(bl::network::client::ClientMessage &message) {
	std::unordered_map<EApiType, std::function<bl::network::server::ServerMessage(bl::network::client::ClientMessage)>> lMap = {
		{EApiType::API_TYPE_UNKNOW, [this](bl::network::client::ClientMessage) -> bl::network::server::ServerMessage {throw std::runtime_error("Can't execute an unknown api");}},
		{EApiType::API_TYPE_BASIC, [this](bl::network::client::ClientMessage msg) -> bl::network::server::ServerMessage  {return this->basicApiExecution(msg);}},
		{EApiType::API_TYPE_BUILDING, [this](bl::network::client::ClientMessage msg) -> bl::network::server::ServerMessage  {return this->m_apiBuilding.execute(msg);}},
		{EApiType::API_TYPE_PLANET, [this](bl::network::client::ClientMessage msg) -> bl::network::server::ServerMessage  {return this->m_apiPlanet.execute(msg);}},
		{EApiType::API_TYPE_TECHNOLOGY, [this](bl::network::client::ClientMessage msg) -> bl::network::server::ServerMessage  {return this->m_apiTechnology.execute(msg);}},
		{EApiType::API_TYPE_USER, [this](bl::network::client::ClientMessage msg) -> bl::network::server::ServerMessage  {return this->m_apiUser.execute(msg);}}
	};

	return lMap[message.getBody().apiType](message);
}

bl::server::ServerCore &bl::server::api::Api::getCore() {
	return m_core;
}

bl::network::server::ServerMessage bl::server::api::Api::basicApiExecution(bl::network::client::ClientMessage& message) {
	return bl::network::server::ServerMessage{};
}
