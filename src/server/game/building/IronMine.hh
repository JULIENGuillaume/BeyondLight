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
				class IronMine : public ABuilding, specialities::IResourceProductionBuilding {
				public:
					IronMine(planet::Planet &planet);
				private:
					void updateResource() override;
				private:
					common::event::Chrono m_chrono;
				};
			}
		}
	}
}


#endif //BEYONDLIGHT_IRONMINE_HH
