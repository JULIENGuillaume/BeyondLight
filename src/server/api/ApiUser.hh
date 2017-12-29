//
// Created by Guillaume on 29/12/2017.
//

#ifndef BEYONDLIGHT_APIUSER_HH
#define BEYONDLIGHT_APIUSER_HH

namespace bl {
	namespace server {
		namespace api {
			class Api;
			class ApiUser {
			public:
				ApiUser(Api &basicApi);
			private:
				Api &basicApi;
			};
		}
	}
}


#endif //BEYONDLIGHT_APIUSER_HH
