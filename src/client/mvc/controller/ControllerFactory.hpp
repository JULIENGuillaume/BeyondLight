//
// Created by diguie_t on 11/26/2017.
//

#ifndef MVC_TEST_CONTROLLERFACTORY_HH
#define MVC_TEST_CONTROLLERFACTORY_HH

#include <ClientNetworkHandler.hh>
#include "IControllerFactory.hh"

namespace bl {
	namespace mvc {
		template<typename Controller>
		class ControllerFactory : public IControllerFactory {
		public:
			virtual std::shared_ptr<IBaseController>
			build(WebCore *webCore) override {
				std::shared_ptr<Controller> controller(new Controller());
				controller->setWebCore(webCore);
				return (controller);
			}
		};
	}
}
#endif //MVC_TEST_CONTROLLERFACTORY_HH
