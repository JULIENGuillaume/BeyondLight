//
// Created by Guillaume Julien on 14/12/2017.
//

#ifndef BEYONDLIGHT_PLANET_HH
#define BEYONDLIGHT_PLANET_HH

#include <memory>
#include <unordered_map>
#include "../building/IBuilding.hh"
#include "../../UniqueObject.hh"
#include "../../../common/game/Resources.hh"
#include "../building/specialities/IResourceProductionBuilding.hh"
#include "../../user/User.hh"

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
					nlohmann::json serialize() const override;
					ISerializable *deserialize(nlohmann::json const &json) override;
					bool claimBy(user::User const& claimer);
					const std::string &getPlanetOwner() const;
				public:
					bool tryToUpdateBuilding(int id);
					const std::shared_ptr<building::IBuilding>& getBuildingInfo(int id) const;
				private:
					void addBuilding(std::shared_ptr<building::IBuilding> const &building);
					void resetBuildings();
				private:
					std::vector<std::shared_ptr<building::IBuilding>> m_buildings;
					std::unordered_map<uint64_t, std::shared_ptr<building::IBuilding>> m_idToBuildings;
					std::vector<std::shared_ptr<building::specialities::IResourceProductionBuilding>> m_resourceProductionBuildings;
					common::game::Resources m_stockResources;
					std::string m_planetOwner;
				};
			}
		}
	}
}
#endif //BEYONDLIGHT_PLANET_HH
