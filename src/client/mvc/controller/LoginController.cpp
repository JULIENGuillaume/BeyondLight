//
// Created by diguie_t on 12/3/2017.
//

#include "LoginController.hh"
#include "../MvcHandler.hh"
#include "../../../common/Toolbox.hh"

namespace bl {
	namespace mvc {
		std::string LoginController::onQuery(
				CefRefPtr<CefBrowser> browser,
				CefRefPtr<CefFrame> frame,
				int64 query_id,
				const CefString &request,
				bool persistent,
				CefRefPtr<CefMessageRouterBrowserSide::Callback> callback
		) {
			std::string message(request);
			if (message.find("login-connect") == 0) {
				if (this->handleLogin(browser, message.substr(
						std::string("login-connect").length()), callback)) {
					return ("/index");
				}
			} else if (message.find("login-register") == 0) {
				this->handleRegister(browser, message.substr(
						std::string("login-register").length()), callback);
				browser->ReloadIgnoreCache();
				//frame->ExecuteJavaScript();
			} else {
				callback->Failure(0, "Unknown route");
			}
			return (std::string());
		}

		bool LoginController::handleLogin(
				CefRefPtr<CefBrowser> browser,
				std::string message,
				CefRefPtr<CefMessageRouterBrowserSide::Callback> callback
		) {
			auto networkHandler = this->m_webCore->getNetworkHandler();
			std::vector<std::string> logInfo = common::Toolbox::split(message,
																	  ":");
			if (logInfo.size() != 2) {
				callback->Failure(0,
								  "Please enter both your login and password");
			} else {
				std::cout << "Sending" << std::endl;
				networkHandler->send("042:" + logInfo[0] + ":" + logInfo[1]);
				std::cout << "GetLine" << std::endl;
				auto future = networkHandler->asyncGetLine();
				std::cout << "Waiting" << std::endl;
				future.wait();
				std::cout << "Spliting" << std::endl;
				auto toks = common::Toolbox::split(future.get(), ":");
				if (!toks.empty() && std::atoi(toks[0].c_str()) == 123) {
					callback->Success("Login success");
					return (true);
				} else {
					callback->Failure(0, "Bad login or password");
				}
			}
			return (false);
		}

		void LoginController::handleRegister(
				CefRefPtr<CefBrowser> browser,
				std::string message,
				CefRefPtr<CefMessageRouterBrowserSide::Callback> callback
		) {
			auto networkHandler = this->m_webCore->getNetworkHandler();
			std::vector<std::string> logInfo = common::Toolbox::split(message,
																	  ":");
			if (logInfo.size() == 6) {
				networkHandler->send(
						"043:" + logInfo[0] + ":" + logInfo[1] + ":" +
								logInfo[2] + ":" + logInfo[3] + ":" + logInfo[4] + ":" +
								logInfo[5]);
				auto future = networkHandler->asyncGetLine();
				future.wait();
				auto toks = common::Toolbox::split(future.get(), ":");
				//std::cout << "Received " << toks[0] << " " << toks[1] << std::endl;
				//TODO: redirect to login page
			}
		}

		void LoginController::setWebCore(WebCore *webCore) {
			this->m_webCore = webCore;
			this->m_modelHandler = this->m_webCore->getMvcHandler()->getModelHandler();
		}

		void LoginController::onFrameEnd() {
		}
	}
}
