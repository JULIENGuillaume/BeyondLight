//
// Created by diguie_t on 11/26/2017.
//

#include "ModelHandler.hh"
#include "BuildingModel.hh"
#include "ResourcesModel.hh"

namespace bl {
	namespace mvc {
		ModelHandler::ModelHandler(std::shared_ptr<network::client::NetworkHandler> networkHandler) {
			this->m_networkHandler = networkHandler;
			this->m_data = {
					{"building-iron-mine", std::shared_ptr<ABaseModel>(new BuildingModel(networkHandler, 1))},
					{"building-crystal-extractor", std::shared_ptr<ABaseModel>(new BuildingModel(networkHandler, 2))}, // todo "buidling-id" instead ?
					{"player-resources", std::shared_ptr<ABaseModel>(new ResourcesModel(networkHandler, ::boost::uuids::uuid()))}
			};
		}
	}
}