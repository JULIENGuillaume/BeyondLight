//
// Created by Guillaume Julien on 22/12/2017.
//

#ifndef BEYONDLIGHT_UNIONCAST_HH
#define BEYONDLIGHT_UNIONCAST_HH

namespace bl {
	namespace common {
		template<class T, class V>
		union UnionCast {
			T inputType;
			V outputType;
		};
	}
}

#endif //BEYONDLIGHT_UNIONCAST_HH
