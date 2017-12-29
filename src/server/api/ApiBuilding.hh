//
// Created by Guillaume on 29/12/2017.
//

#ifndef BEYONDLIGHT_APIBUILDING_HH
#define BEYONDLIGHT_APIBUILDING_HH

namespace bl {
	namespace server {
		namespace api {
			class Api;
			class ApiBuilding {
			public:
				ApiBuilding(Api &basicApi);
			private:
				Api &basicApi;
			};
		}
	}
}


#endif //BEYONDLIGHT_APIBUILDING_HH
