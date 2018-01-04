//
// Created by Guillaume on 29/12/2017.
//

#ifndef BEYONDLIGHT_APIUSER_HH
#define BEYONDLIGHT_APIUSER_HH

namespace bl {
	namespace network {
		namespace client {
			class ClientMessage;
		}
	}
	namespace server {
		namespace api {
			class Api;
			class ApiUser {
			public:
				explicit ApiUser(Api &basicApi);
				void execute(network::client::ClientMessage &message);

			private:
				Api &basicApi;
			};
		}
	}
}


#endif //BEYONDLIGHT_APIUSER_HH
