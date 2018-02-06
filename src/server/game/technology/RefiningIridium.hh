//
// Created by Guillaume on 06/02/2018.
//

#ifndef BEYONDLIGHT_REFININGIRIDUM_HH
#define BEYONDLIGHT_REFININGIRIDUM_HH

#include "ATechnology.hh"

namespace bl {
	namespace server {
		namespace game {
			namespace technology {
				class RefiningIridium : public ATechnology {
				public:
					static const int id = 1;
				public:
					RefiningIridium();
					~RefiningIridium() override = default;
				};
			}
		}
	}
}

#endif //BEYONDLIGHT_REFININGIRIDUM_HH
