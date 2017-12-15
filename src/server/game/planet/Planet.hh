//
// Created by Guillaume Julien on 14/12/2017.
//

#ifndef BEYONDLIGHT_PLANET_HH
#define BEYONDLIGHT_PLANET_HH

#include <memory>
#include "../building/IBuilding.hh"
#include "../../UniqueObject.hh"
#include "../../../common/game/Resources.hh"
#include "../building/specialities/IResourceProductionBuilding.hh"

namespace bl {
	namespace server {
		namespace game {
			namespace planet {
				class Planet : public UniqueObject {
				public:
					Planet();
					Planet(Planet const &src);
				public:
					common::game::Resources &getStockResources();
					common::game::Resources const &getStockResources() const;
					void updateResources();

				private:
					void addBuilding(std::shared_ptr<building::IBuilding> const &building);
				private:
					std::vector<std::shared_ptr<building::IBuilding>> m_buildings;
					std::vector<std::shared_ptr<building::specialities::IResourceProductionBuilding>> m_resourceProductionBuildings;
					common::game::Resources m_stockResources;
				};
			}
		}
	}
}
#endif //BEYONDLIGHT_PLANET_HH
