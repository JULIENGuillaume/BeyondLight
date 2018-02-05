//
// Created by Guillaume on 04/12/2017.
//

#ifndef BEYONDLIGHT_IBUILDING_HH
#define BEYONDLIGHT_IBUILDING_HH

#include <string>
#include <map>
#include "../../../common/pattern/ISerializable.hh"
#include "../resource/UpgradeCost.hh"
#include "../decorator/IdentifiableCapacity.hh"
#include "../decorator/UpgradableCapacity.hh"

namespace bl {
	namespace server {
		namespace game {
			namespace building {
				class IBuilding : public decorator::IdentifiableCapacity, public decorator::UpgradableCapacity {
				public:
					~IBuilding() override = default;
				public:
					virtual bool upgrade() = 0;

					nlohmann::json serialize() const override = 0;
					ISerializable *deserialize(nlohmann::json const &json) override = 0;
				protected:
					virtual void updateBuildingOnDeltaTime(uint64_t seconds) = 0;
				};
			}
		}
	}
}

#endif //BEYONDLIGHT_IBUILDING_HH
