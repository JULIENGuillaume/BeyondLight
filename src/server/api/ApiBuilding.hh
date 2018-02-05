//
// Created by Guillaume on 29/12/2017.
//

#ifndef BEYONDLIGHT_APIBUILDING_HH
#define BEYONDLIGHT_APIBUILDING_HH

namespace bl {
	namespace network {
		namespace client {
			class ClientMessage;
		}
	}
	namespace server {
		namespace api {
			class Api;
			class ApiBuilding {
			public:
				explicit ApiBuilding(Api &basicApi);
				void execute(network::client::ClientMessage &message);

			private:
				Api &basicApi;
			};
		}
	}
}


#endif //BEYONDLIGHT_APIBUILDING_HH
