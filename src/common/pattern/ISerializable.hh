//
// Created by Guillaume on 04/12/2017.
//

#ifndef BEYONDLIGHT_SERIALIZABLE_HH
#define BEYONDLIGHT_SERIALIZABLE_HH

#include <json.hpp>

namespace bl {
	namespace common {
		namespace pattern {
			class ISerializable {
			public:
				virtual ~ISerializable() = default;
			public:
				virtual nlohmann::json serialize() const = 0;
				virtual common::pattern::ISerializable *deserialize(nlohmann::json const &json) = 0;
			};
		}
	}
}

#endif //BEYONDLIGHT_SERIALIZABLE_HH
