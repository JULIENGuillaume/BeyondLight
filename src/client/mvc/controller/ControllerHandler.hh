//
// Created by diguie_t on 11/26/2017.
//

#ifndef MVC_TEST_CONTROLLERHANDLER_HH
#define MVC_TEST_CONTROLLERHANDLER_HH

#include <unordered_map>
#include "include/wrapper/cef_message_router.h"
#include "IBaseController.hh"
#include "IControllerFactory.hh"
#include "../DataHandler.hpp"

namespace bl {
	namespace mvc {
		class ControllerHandler : public DataHandler<std::string, std::shared_ptr<IControllerFactory>> {
		public:
			ControllerHandler() = delete;
			explicit ControllerHandler(WebCore *webCore);
			void changeRoute(const std::string &route);
			void onFrameEnd();
			bool onQuery(
					CefRefPtr<CefBrowser> browser,
					CefRefPtr<CefFrame> frame,
					int64 query_id,
					const CefString &request,
					bool persistent,
					CefRefPtr<CefMessageRouterBrowserSide::Callback> callback
			);
		private:
			std::string m_curBaseRoute;
			std::shared_ptr<IBaseController> m_currentController;
			std::shared_ptr<ModelHandler> m_modelHandler;
			WebCore *m_webCore;
			std::shared_ptr<IControllerFactory>
			getRouteControllerFactory(const std::string &route);
		};
	}
}
#endif //MVC_TEST_CONTROLLERHANDLER_HH
