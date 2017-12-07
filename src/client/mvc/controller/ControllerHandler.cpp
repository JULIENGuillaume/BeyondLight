//
// Created by diguie_t on 11/26/2017.
//

#include "ControllerFactory.hpp"
#include "ControllerHandler.hh"
#include "LoginController.hh"
#include "../MvcHandler.hh"
#include "IndexController.hh"

namespace bl {
	namespace mvc {
		std::shared_ptr<IControllerFactory>
		ControllerHandler::getRouteControllerFactory(const std::string &route) {
			auto pair = this->getData(route);
			if (pair.first) {
				return (pair.second);
			}
			return (nullptr);
		}

		void ControllerHandler::changeRoute(
				const std::string &baseRoute,
				const std::string &subRoute
		) {
			std::shared_ptr<IControllerFactory> pFactory = this->getRouteControllerFactory(
					baseRoute);
			if (pFactory == nullptr) {
				std::cerr << "invalid route: " << baseRoute << std::endl;
			}
			this->m_currentController.reset();
			this->m_currentController = nullptr;
			this->m_curBaseRoute = baseRoute;
			this->m_curSubRoute = subRoute;
			this->m_currentController = pFactory->build(this->m_webCore);
		}

		ControllerHandler::ControllerHandler(WebCore *webCore) {
			this->m_webCore = webCore;
			this->m_modelHandler = webCore->getMvcHandler()->getModelHandler();
			this->m_currentController = nullptr;
			this->m_data = {
					{"/login", std::shared_ptr<ControllerFactory<LoginController>>(new ControllerFactory<LoginController>())},
					{"/index", std::shared_ptr<ControllerFactory<IndexController>>(new ControllerFactory<IndexController>())}
			};
			this->changeRoute("/login", "");
		}

		void ControllerHandler::onQuery(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				int64 query_id,
				const CefString &request,
				bool persistent,
				CefRefPtr<CefMessageRouterBrowserSide::Callback> callback
		) {
			// todo check message path
			if (this->m_currentController ==
					nullptr /* or is invalid controller */) {
				callback->Failure(0, "Invalid route");
			} else {
				auto newRoute = this->m_currentController->onQuery(browser,
																   frame,
																   query_id,
																   request,
																   persistent,
																   callback);
				if (!newRoute.empty()) {
					this->changeRoute(newRoute, "");
				}
			}
		}

		void ControllerHandler::onFrameEnd() {
			if (this->m_currentController != nullptr) {
				this->m_currentController->onFrameEnd();
			}
		}
	}
}