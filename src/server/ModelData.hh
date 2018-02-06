//
// Created by Guillaume on 06/02/2018.
//

#ifndef BEYONDLIGHT_MODELDATA_HH
#define BEYONDLIGHT_MODELDATA_HH

#include <memory>
#include <unordered_map>

namespace bl {
	namespace server {
		namespace game {
			namespace technology {
				class ITechnology;
			}
		}
		struct ModelData {
			ModelData();
			std::unordered_map<int, std::shared_ptr<game::technology::ITechnology>> technologies;
		};
	}
}

#endif //BEYONDLIGHT_MODELDATA_HH
