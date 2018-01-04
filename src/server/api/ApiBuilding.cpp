//
// Created by Guillaume on 29/12/2017.
//

#include "../ServerCore.hh"
#include "ApiBuilding.hh"
#include "Api.hh"

bl::server::api::ApiBuilding::ApiBuilding(bl::server::api::Api &basicApi) : basicApi(basicApi) {}

void bl::server::api::ApiBuilding::execute(bl::network::client::ClientMessage &message) {

}
