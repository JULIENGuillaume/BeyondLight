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
		public:
			MvcHandler();
			std::shared_ptr<const ModelHandler> getModelHandler() const;
			std::shared_ptr<const ControllerHandler>
			getControllerHandler() const;
			std::shared_ptr<ModelHandler> getModelHandler();
			std::shared_ptr<ControllerHandler> getControllerHandler();
			void setWebCore(WebCore *webCore);
		private:
			std::shared_ptr<ModelHandler> m_modelHandler;
			std::shared_ptr<ControllerHandler> m_controllerHandler;
			WebCore *m_webCore;
		};
	}
}
#endif //BEYONDLIGHT_MVCHANDLER_HH
