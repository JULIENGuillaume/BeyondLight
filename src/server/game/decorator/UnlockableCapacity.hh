//
// Created by Guillaume Julien on 05/02/2018.
//

#ifndef BEYONDLIGHT_UNLOCKABLECAPACITY_HH
#define BEYONDLIGHT_UNLOCKABLECAPACITY_HH

#include <ISerializable.hh>
#include <unordered_map>
#include "../planet/Planet.hh"

namespace bl {
	namespace server {
		namespace game {
			namespace decorator {
				class UnlockableCapacity : public virtual common::pattern::ISerializable {
				public:
					virtual ~UnlockableCapacity() = default;
				public:
					bool unlock(planet::Planet const &planet);
					bool isUnlocked() const;
					bool isUnlockable(planet::Planet const &planet) const;
					void addResearchDependency(int dependency);
					void addBuildingDependency(int dependency, int level);
				protected:
					bool m_unlocked = false;
					std::vector<int> m_researchDependencies = {};
					std::unordered_map<int, int> m_buildingDependencies = {};
				};
			}
		}
	}
}

#endif //BEYONDLIGHT_UNLOCKABLECAPACITY_HH
