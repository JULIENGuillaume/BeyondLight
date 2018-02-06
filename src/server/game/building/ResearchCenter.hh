//
// Created by Guillaume on 06/02/2018.
//

#ifndef BEYONDLIGHT_RESEARCHCENTER_HH
#define BEYONDLIGHT_RESEARCHCENTER_HH

#include "ABuilding.hh"

namespace bl {
	namespace server {
		namespace game {
			namespace planet {
				class Planet;
			}
			namespace building {
				class ResearchCenter : public ABuilding {
				public:
					static const int id = 3;
				public:
					explicit ResearchCenter(planet::Planet &planet);
					~ResearchCenter() override = default;
				public:
				protected:
					void updateBuildingOnDeltaTime(uint64_t seconds) override;
				private:
					int m_actualResearch = -1;
					uint64_t m_remainingUpdateTime = 0;
				};
			}
		}
	}
}

#endif //BEYONDLIGHT_RESEARCHCENTER_HH
