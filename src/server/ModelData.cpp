//
// Created by Guillaume on 06/02/2018.
//

#include "ModelData.hh"
#include "game/technology/RefiningIridium.hh"

bl::server::ModelData::ModelData() {
	this->technologies.emplace(game::technology::RefiningIridium::id, std::shared_ptr<game::technology::ITechnology>(new game::technology::RefiningIridium));
}
