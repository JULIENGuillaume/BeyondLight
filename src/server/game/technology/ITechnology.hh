//
// Created by Guillaume on 04/12/2017.
//

#ifndef BEYONDLIGHT_ITECHNOLOGY_HH
#define BEYONDLIGHT_ITECHNOLOGY_HH

#include <ISerializable.hh>
#include "../decorator/IdentifiableCapacity.hh"
#include "../decorator/UnlockableCapacity.hh"

namespace bl {
	namespace server {
		namespace game {
			namespace technology {
				class ITechnology : public decorator::IdentifiableCapacity, public decorator::UnlockableCapacity {
				public:
					~ITechnology() override = default;
				public:
					virtual uint64_t getResearchTime() = 0;
				public:
					nlohmann::json serialize() const override = 0;
					ISerializable *deserialize(nlohmann::json const &json) override = 0;
				};
			}
		}
	}
}

#endif //BEYONDLIGHT_ITECHNOLOGY_HH
