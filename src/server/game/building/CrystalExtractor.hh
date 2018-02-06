//
// Created by Guillaume on 19/12/2017.
//

#ifndef BEYONDLIGHT_CRYSTALEXTRACTOR_HH
#define BEYONDLIGHT_CRYSTALEXTRACTOR_HH

#include "ABuilding.hh"
#include "specialities/IResourceProductionBuilding.hh"
#include "../../../common/event/Chrono.hh"

namespace bl {
	namespace server {
		namespace game {
			namespace planet {
				class Planet;
			}
			namespace building {
				class CrystalExtractor : public ABuilding, public specialities::IResourceProductionBuilding {
				public:
					static const int id = 2;
				public:
					explicit CrystalExtractor(planet::Planet &planet);
					void updateResource() override;
					nlohmann::json serialize() const override;
					ISerializable *deserialize(nlohmann::json const &json) override;
				protected:
					void updateBuildingOnDeltaTime(uint64_t seconds) override;
				private:
					common::event::Chrono m_chrono;
					uint64_t m_timeLeftFromLastProd = 0;
					const uint64_t m_secondsForProduction = 1;
				};
			}
		}
	}
}

#endif //BEYONDLIGHT_CRYSTALEXTRACTOR_HH
