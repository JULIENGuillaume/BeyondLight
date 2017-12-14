//
// Created by diguie_t on 11/28/2017.
//

#ifndef MVC_TEST_ABASEMODEL_HH
#define MVC_TEST_ABASEMODEL_HH

#include <NetworkHandler.hh>
#include "../../../common/event/EventObserver.hh"

namespace bl {
	namespace mvc {
		class ABaseModel : public EventObserver {
		public:
			ABaseModel(std::shared_ptr<network::client::NetworkHandler> networkHandler);
			virtual void markForUpdate() = 0;
			virtual bool needUpdate() = 0;
			virtual void markToCommitChange() = 0;
			virtual bool hasChange() = 0;
			// todo add getter & setter for uuid ?
		protected:
			std::shared_ptr<network::client::NetworkHandler> m_networkHandler;
		};
	}
}
#endif //MVC_TEST_ABASEMODEL_HH
