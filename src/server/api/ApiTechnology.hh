//
// Created by Guillaume on 29/12/2017.
//

#ifndef BEYONDLIGHT_APITECHNOLOGY_HH
#define BEYONDLIGHT_APITECHNOLOGY_HH

namespace bl {
	namespace network {
		namespace client {
			class ClientMessage;
		}
	}
	namespace server {
		namespace api {
			class Api;
			class ApiTechnology {
			public:
				explicit ApiTechnology(Api &basicApi);
				void execute(network::client::ClientMessage &message);

			private:
				Api &basicApi;
			};
		}
	}
}


#endif //BEYONDLIGHT_APITECHNOLOGY_HH
