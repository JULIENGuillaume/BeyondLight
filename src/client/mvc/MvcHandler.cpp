//
// Created by diguie_t on 12/3/2017.
//

#include "MvcHandler.hh"

namespace bl {
    namespace mvc {

        MvcHandler::MvcHandler(std::weak_ptr<WebCore> webCore) {
            this->_webCore = webCore;
            this->_modelHandler = std::shared_ptr<ModelHandler>(
                    new ModelHandler());
            this->_controllerHandler = std::shared_ptr<ControllerHandler>(
                    new ControllerHandler(this->_modelHandler, this->_webCore));
        }

        std::shared_ptr<const ModelHandler>
        MvcHandler::getModelHandler() const {
            return (this->_modelHandler);
        }

        std::shared_ptr<const ControllerHandler>
        MvcHandler::getControllerHandler() const {
            return (this->_controllerHandler);
        }

        std::shared_ptr<ModelHandler> MvcHandler::getModelHandler() {
            return (this->_modelHandler);
        }

        std::shared_ptr<ControllerHandler> MvcHandler::getControllerHandler() {
            return (this->_controllerHandler);
        }

    }
}