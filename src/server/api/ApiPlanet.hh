//
// Created by Guillaume on 29/12/2017.
//

#ifndef BEYONDLIGHT_APIPLANET_HH
#define BEYONDLIGHT_APIPLANET_HH

namespace bl {
	namespace server {
		namespace api {
			class Api;
			class ApiPlanet {
			public:
				ApiPlanet(Api &basicApi);
			private:
				Api &basicApi;
			};
		}
	}
}


#endif //BEYONDLIGHT_APIPLANET_HH
