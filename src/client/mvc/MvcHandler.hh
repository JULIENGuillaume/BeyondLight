//
// Created by diguie_t on 12/3/2017.
//

#ifndef BEYONDLIGHT_MVCHANDLER_HH
#define BEYONDLIGHT_MVCHANDLER_HH


#include <memory>
#include "controller/ControllerHandler.hh"

namespace bl {
    namespace mvc {
        class MvcHandler {
        private:
            std::shared_ptr<ModelHandler> _modelHandler;
            std::shared_ptr<ControllerHandler> _controllerHandler;
            std::weak_ptr<WebCore> _webCore;

        public:
            MvcHandler(std::weak_ptr<WebCore> webCore);

            std::shared_ptr<const ModelHandler> getModelHandler() const;

            std::shared_ptr<const ControllerHandler>
            getControllerHandler() const;

            std::shared_ptr<ModelHandler> getModelHandler();

            std::shared_ptr<ControllerHandler> getControllerHandler();
        };
    }
}


#endif //BEYONDLIGHT_MVCHANDLER_HH
