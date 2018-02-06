//
// Created by Guillaume on 06/02/2018.
//

#ifndef BEYONDLIGHT_IRIDIUMREFINERY_HH
#define BEYONDLIGHT_IRIDIUMREFINERY_HH

#include "ABuilding.hh"
#include "specialities/IResourceProductionBuilding.hh"
#include "../../../common/event/Chrono.hh"

namespace bl {
	namespace server {
		namespace game {
			namespace building {
				class IridiumRefinery : public ABuilding, public specialities::IResourceProductionBuilding  {
				public:
					static const int id = 4;
				public:
					explicit IridiumRefinery(planet::Planet &planet);
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

#endif //BEYONDLIGHT_IRIDIUMREFINERY_HH
