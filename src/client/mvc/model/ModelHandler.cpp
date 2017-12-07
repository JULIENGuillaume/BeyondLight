//
// Created by diguie_t on 11/26/2017.
//

#include "ModelHandler.hh"

namespace bl {
	namespace mvc {
		ModelHandler::ModelHandler() { // todo pass network handler so models can query for updates or send changes
			this->m_data = {
					//{"student", std::shared_ptr<ABaseModel>(new StudentModel())}
			};
		}
	}
}