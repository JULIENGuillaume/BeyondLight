//
// Created by diguie_t on 11/26/2017.
//

#ifndef MVC_TEST_CONTROLLERFACTORY_HH
#define MVC_TEST_CONTROLLERFACTORY_HH

#include <NetworkHandler.hh>
#include "IControllerFactory.hh"

namespace bl {
    namespace mvc {
        template<typename Controller>
        class ControllerFactory : public IControllerFactory {
        public:
            virtual std::shared_ptr<IBaseController>
            build(std::shared_ptr<ModelHandler> modelHandler,
                  std::weak_ptr<WebCore> webCore) override {
                std::shared_ptr<Controller> controller(new Controller());
                controller->setModelHandler(modelHandler);
                controller->setWebCore(webCore);
                return (controller);
            }

        };
    }
}

#endif //MVC_TEST_CONTROLLERFACTORY_HH
