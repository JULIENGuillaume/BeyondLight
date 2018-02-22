//
// Created by diguie_t on 2/18/2018.
//

#include "ChatController.hh"
#include "../../../../common/Toolbox.hh"
#include "LeftMenu.hh"
#include "../../model/ResourcesModel.hh"
#include "../../MvcHandler.hh"

namespace bl {
	namespace mvc {
		const std::string ChatController::m_chatUrl = "file:///" + bl::common::Toolbox::getApplicationDir() + "/../resources/html/chat.html";

		void ChatController::setWebCore(bl::WebCore *webCore) {
			this->m_webCore = webCore;
			this->m_webCore->getBrowser()->GetMainFrame()->LoadURL(m_chatUrl);
		}

		bool ChatController::onQuery(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				int64 query_id,
				const CefString &request,
				bool persistent,
				CefRefPtr<CefMessageRouterBrowserSide::Callback> callback,
				std::string &newRoute
		) {
			std::vector<std::string> requestArgs = bl::common::Toolbox::splitAtMax(request, ":", 1);
			std::cout << "request chat: " << bl::common::Toolbox::toString(request) << std::endl;
			if (!requestArgs.empty()) {
				const std::string &controllerRoute = LeftMenu::getRequestControllerRouter(requestArgs[0]);
				if (controllerRoute.empty()) {
					if (requestArgs[0] == "chat-send-message" && requestArgs.size() == 2) {
						const std::string &result = requestArgs[1];
						auto networkHandler = this->m_webCore->getNetworkHandler();
						networkHandler->send(networkHandler->getApiHelper()->buildNewApiRequest(networkHandler->getApiHelper()->REQUEST_SEND_CHAT_MESSAGE, requestArgs[1]));
						auto msg = networkHandler->getMessage();
						std::cout << msg << std::endl;
						callback->Success("Allan-add-user:" + result);
						return (true);
					} else if (requestArgs[0].find("update-player-resources") == 0 && requestArgs.size() == 1) {
						auto playerResources = this->m_webCore->getMvcHandler()->getModelHandler()->getModel<ResourcesModel>("player-resources");
						playerResources->update();
						const auto resources = playerResources->getResources();
						callback->Success(std::to_string(resources.getIron())
												  + ":" + std::to_string(resources.getCrystal())
												  + ":" + std::to_string(resources.getIridium())
												  + ":" + std::to_string(resources.getAntiMatter())
												  + ":" + std::to_string(resources.getEnergy()));
						return (true);
					}
				} else {
					callback->Success("OK");
					newRoute = controllerRoute;
					return (true);
				}
			}
			return (false);
		}

		void ChatController::onFrameEnd() {
			auto modelHandler = this->m_webCore->getMvcHandler()->getModelHandler();
			{
				auto playerResources = modelHandler->getModel<ResourcesModel>("player-resources");
				playerResources->update();
				const auto resources = playerResources->getResources();
				std::string js = std::string("updateResources(")
						+ std::to_string(resources.getIron()) + ","
						+ std::to_string(resources.getCrystal()) + ","
						+ std::to_string(resources.getIridium()) + ","
						+ std::to_string(resources.getAntiMatter()) + ","
						+ std::to_string(resources.getEnergy()) + ");";
				this->m_webCore->getBrowser()->GetMainFrame()->ExecuteJavaScript(
						js, m_chatUrl, 0);
			}
		}
	}
}