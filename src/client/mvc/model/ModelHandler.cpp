//
// Created by diguie_t on 11/26/2017.
//

#include "ModelHandler.hh"
#include "BuildingModel.hh"
#include "ResourcesModel.hh"
#include "TechnologyModel.hh"
#include "ChatModel.hh"
#include "ShipModel.hh"

namespace bl {
	namespace mvc {
		ModelHandler::ModelHandler(std::shared_ptr<network::client::ClientNetworkHandler> networkHandler) {
			this->m_networkHandler = networkHandler;
			this->m_data = {
					{"building-iron-mine",          std::shared_ptr<ABaseModel>(new BuildingModel(networkHandler, 1))}, // todo "buidling-id" instead ?
					{"building-crystal-extractor",  std::shared_ptr<ABaseModel>(new BuildingModel(networkHandler, 2))}, // todo "buidling-id" instead ?
					{"building-research-center",    std::shared_ptr<ABaseModel>(new BuildingModel(networkHandler, 3))}, // todo "buidling-id" instead ?
					{"building-iridium-refinery",   std::shared_ptr<ABaseModel>(new BuildingModel(networkHandler, 4))}, // todo "buidling-id" instead ?
					{"technology-refining-iridium", std::shared_ptr<ABaseModel>(new TechnologyModel(networkHandler, 1))}, // todo "buidling-id" instead ?
					{"player-resources",            std::shared_ptr<ABaseModel>(new ResourcesModel(networkHandler, ::boost::uuids::uuid()))},
					{"chat",                        std::shared_ptr<ABaseModel>(new ChatModel(networkHandler))},
					{"ship-nexus",                  std::shared_ptr<ABaseModel>(new ShipModel(networkHandler, 1))}
			};
		}
	}
}