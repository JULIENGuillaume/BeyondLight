//
// Created by diguie_t on 12/3/2017.
//

#include "MvcHandler.hh"

MvcHandler::MvcHandler(std::shared_ptr<network::client::NetworkHandler> networkHandler) {
    this->_networkHandler = networkHandler;
    this->_modelHandler = std::shared_ptr<ModelHandler>(new ModelHandler());
    this->_controllerHandler = std::shared_ptr<ControllerHandler>(new ControllerHandler(this->_modelHandler, this->_networkHandler));
}

std::shared_ptr<const ModelHandler> MvcHandler::getModelHandler() const {
    return (this->_modelHandler);
}

std::shared_ptr<const ControllerHandler> MvcHandler::getControllerHandler() const {
    return (this->_controllerHandler);
}

std::shared_ptr<ModelHandler> MvcHandler::getModelHandler() {
    return (this->_modelHandler);
}

std::shared_ptr<ControllerHandler> MvcHandler::getControllerHandler() {
    return (this->_controllerHandler);
}
