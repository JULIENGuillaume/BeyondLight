//
// Created by Guillaume on 29/12/2017.
//

#ifndef BEYONDLIGHT_APITECHNOLOGY_HH
#define BEYONDLIGHT_APITECHNOLOGY_HH

namespace bl {
	namespace server {
		namespace api {
			class Api;
			class ApiTechnology {
			public:
				ApiTechnology(Api &basicApi);
			private:
				Api &basicApi;
			};
		}
	}
}


#endif //BEYONDLIGHT_APITECHNOLOGY_HH
