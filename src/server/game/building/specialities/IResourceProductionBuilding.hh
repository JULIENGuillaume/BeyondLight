//
// Created by Guillaume Julien on 15/12/2017.
//

#ifndef BEYONDLIGHT_IRESSOURCEPRODUCTIONBUILDING_HH
#define BEYONDLIGHT_IRESSOURCEPRODUCTIONBUILDING_HH

namespace bl {
	namespace server {
		namespace game {
			namespace building {
				namespace specialities {
					class IResourceProductionBuilding {
					public:
						virtual ~IResourceProductionBuilding() = default;
					public:
						virtual void updateResource() = 0;
					};
				}
			}
		}
	}
}

#endif //BEYONDLIGHT_IRESSOURCEPRODUCTIONBUILDING_HH
