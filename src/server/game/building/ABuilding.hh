//
// Created by Guillaume on 04/12/2017.
//

#ifndef BEYONDLIGHT_ABUILDING_HH
#define BEYONDLIGHT_ABUILDING_HH

#include "IBuilding.hh"

namespace bl {
	namespace server {
		namespace game {
			namespace planet {
				class Planet;
			}
			namespace building {
				class ABuilding : public IBuilding {
				public:
					ABuilding(
								int id,
								std::string const &name,
								std::string const &desc,
								std::vector<resource::UpgradeCost> const &upgrades,
								const std::unordered_set<int> &researchDependencies,
								const std::unordered_map<int, int> &buildingDependencies,
								planet::Planet &planet
						);
					~ABuilding() override = default;
				public:
					nlohmann::json serialize() const override;
					ISerializable *deserialize(nlohmann::json const &json) override;
					bool upgrade() override;
				protected:
					planet::Planet &m_planet;
				};
			}
		}
	}
}

#endif //BEYONDLIGHT_ABUILDING_HH
