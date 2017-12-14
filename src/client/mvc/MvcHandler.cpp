//
// Created by diguie_t on 12/3/2017.
//

#include "MvcHandler.hh"

namespace bl {
	namespace mvc {
		MvcHandler::MvcHandler() {
			this->m_controllerHandler = nullptr;
			this->m_modelHandler = nullptr;
		}

		std::shared_ptr<const ModelHandler>
		MvcHandler::getModelHandler() const {
			return (this->m_modelHandler);
		}

		std::shared_ptr<const ControllerHandler>
		MvcHandler::getControllerHandler() const {
			return (this->m_controllerHandler);
		}

		std::shared_ptr<ModelHandler> MvcHandler::getModelHandler() {
			return (this->m_modelHandler);
		}

		std::shared_ptr<ControllerHandler> MvcHandler::getControllerHandler() {
			return (this->m_controllerHandler);
		}

		void MvcHandler::setWebCore(WebCore *webCore) {
			this->m_webCore = webCore;
			this->m_modelHandler = std::shared_ptr<ModelHandler>(new ModelHandler(this->m_webCore->getNetworkHandler()));
			this->m_controllerHandler = std::shared_ptr<ControllerHandler>(new ControllerHandler(this->m_webCore));
		}
	}
}