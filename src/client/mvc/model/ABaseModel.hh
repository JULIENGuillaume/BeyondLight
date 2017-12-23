//
// Created by diguie_t on 11/28/2017.
//

#ifndef MVC_TEST_ABASEMODEL_HH
#define MVC_TEST_ABASEMODEL_HH

#include <ClientNetworkHandler.hh>
#include "../../../common/event/EventObserver.hh"

namespace bl {
	namespace mvc {
		class ABaseModel : public EventObserver {
		public:
			ABaseModel(std::shared_ptr<network::client::ClientNetworkHandler> networkHandler);
			virtual void update() = 0;
			// todo add getter & setter for uuid ?
		protected:
			std::shared_ptr<network::client::ClientNetworkHandler> m_networkHandler;
		};
	}
}
#endif //MVC_TEST_ABASEMODEL_HH
