//
// Created by diguie_t on 11/28/2017.
//

#include "ABaseModel.hh"

namespace bl {
	namespace mvc {

		ABaseModel::ABaseModel(std::shared_ptr<network::client::ClientNetworkHandler> networkHandler) {
			this->m_networkHandler = networkHandler;
		}
	}
}