//
// Created by Guillaume Julien on 14/12/2017.
//

#ifndef BEYONDLIGHT_PLANET_HH
#define BEYONDLIGHT_PLANET_HH

#include <memory>
#include "../building/IBuilding.hh"
#include "../../UniqueObject.hh"

namespace bl {
	namespace server {
		namespace game {
			namespace planet {
				class Planet : public UniqueObject {
				public:
					Planet();
					Planet(Planet const& src);

				private:
					std::vector<std::shared_ptr<building::IBuilding>> m_buildings;

				};
			}
		}
	}
}
#endif //BEYONDLIGHT_PLANET_HH
