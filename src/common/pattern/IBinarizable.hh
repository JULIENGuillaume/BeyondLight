//
// Created by Guillaume Julien on 20/12/2017.
//

#ifndef BEYONDLIGHT_IBINARIZABLE_HH
#define BEYONDLIGHT_IBINARIZABLE_HH

#include <utility>

namespace bl {
	namespace common {
		namespace pattern {
			class IBinarizable {
				virtual std::pair<size_t, char*> getBinaryData() = 0;
				virtual common::pattern::IBinarizable *loadFromBinaryData(std::pair<size_t, char*> const &data) = 0;
			};
		}
	}
}
#endif //BEYONDLIGHT_IBINARIZABLE_HH
