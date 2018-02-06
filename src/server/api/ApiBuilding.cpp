//
// Created by Guillaume on 29/12/2017.
//

#include "../ServerCore.hh"
#include "ApiBuilding.hh"
#include "Api.hh"

bl::server::api::ApiBuilding::ApiBuilding(bl::server::api::Api &basicApi) : basicApi(basicApi) {}

bl::network::server::ServerMessage  bl::server::api::ApiBuilding::execute(bl::network::client::ClientMessage &message) {
	return bl::network::server::ServerMessage{};

}
