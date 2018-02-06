//
// Created by Guillaume on 04/12/2017.
//

#ifndef BEYONDLIGHT_IRONMINE_HH
#define BEYONDLIGHT_IRONMINE_HH

#include "ABuilding.hh"
#include "specialities/IResourceProductionBuilding.hh"
#include "../../../common/event/Chrono.hh"

namespace bl {
	namespace server {
		namespace game {
			namespace building {
				class IronMine : public ABuilding, public specialities::IResourceProductionBuilding {
				public:
					static const int id = 1;
				public:
					explicit IronMine(planet::Planet &planet);
				public:
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


#endif //BEYONDLIGHT_IRONMINE_HH
