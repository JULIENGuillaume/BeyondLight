//
// Created by diguie_t on 12/3/2017.
//

#include "LoginController.hh"
#include "../MvcHandler.hh"
#include "../../../common/Toolbox.hh"

namespace bl {
	namespace mvc {
		bool LoginController::onQuery(
			CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			int64 query_id,
			const CefString &request,
			bool persistent,
			CefRefPtr<CefMessageRouterBrowserSide::Callback> callback,
			std::string &newRoute
		) {
			std::string message(request);
			if (message.find("login-connect") == 0) {
				if (this->handleLogin(browser, message.substr(std::string("login-connect").length()), callback)) {
					newRoute = "/overview";
				}
				return (true);
			} else if (message.find("login-register") == 0) {
				this->handleRegister(browser, message.substr(std::string("login-register").length()), callback);
				return (true);
			}
			return (false);
		}

		bool LoginController::handleLogin(
			CefRefPtr<CefBrowser> browser,
			std::string message,
			CefRefPtr<CefMessageRouterBrowserSide::Callback> callback
		) {
			auto networkHandler = this->m_webCore->getNetworkHandler();
			std::vector<std::string> logInfo = common::Toolbox::split(message, ":");
			if (logInfo.size() != 2) {
				callback->Failure(0, "Please enter both your login and password");
			} else {
				//TODO: setup a better login way
				//networkHandler->send("042:" + logInfo[0] + ":" + logInfo[1]);
				networkHandler->send(networkHandler->getApiHelper()->buildNewApiRequest(networkHandler->getApiHelper()->REQUEST_LOGIN, std::vector<std::string>{logInfo[0],
				                                                                                                                                                common::Toolbox::sha512This(logInfo[1])}));
				//networkHandler->send(network::client::ClientMessageType::CLIENT_MESSAGE_TYPE_REQUEST, 42, logInfo[0] + ":" + common::Toolbox::sha512This(logInfo[1]));
				auto msg = networkHandler->getMessage().getBody();
				if (msg.type == network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK) {
					networkHandler->setSessionId(msg.message);
					auto str = networkHandler->getLine();
					networkHandler->swapToUdp(static_cast<unsigned short>(std::stol(str)));
					networkHandler->send(networkHandler->getApiHelper()->buildNewApiRequest(networkHandler->getApiHelper()->REQUEST_VALIDATE_NETWORK));
					msg = networkHandler->getMessage().getBody();
					if (msg.type == network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_OK) {
						callback->Success("Login success");
						return (true);
					}
					callback->Failure(0, msg.message);
				} else {
					callback->Failure(0, msg.message);
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
				if (logInfo[4] != logInfo[5]) {
					callback->Failure(0, "Password must be the sames !");
				} else {
					networkHandler->send(networkHandler->getApiHelper()->buildNewApiRequest(networkHandler->getApiHelper()->REQUEST_REGISTER, std::vector<std::string>{logInfo[0],
					                                                                                                                                                   logInfo[1],
					                                                                                                                                                   logInfo[2],
					                                                                                                                                                   logInfo[3],
					                                                                                                                                                   common::Toolbox::sha512This(logInfo[4]),
					                                                                                                                                                   common::Toolbox::sha512This(logInfo[5])}));
					/*networkHandler->send(network::client::ClientMessageType::CLIENT_MESSAGE_TYPE_REQUEST, 43,
					                     logInfo[0] + ":" + logInfo[1] + ":" + logInfo[2] + ":" +
					                     logInfo[3] + ":" + common::Toolbox::sha512This(logInfo[4]) + ":" + common::Toolbox::sha512This(logInfo[5]));*/
					std::cout << "Send register" << std::endl;
					auto msg = networkHandler->getMessage().getBody();
					std::cout << "Got answer: " << msg << std::endl;
					if (msg.type == network::server::ServerMessageType::SERVER_MESSAGE_TYPE_ANSWER_KO) {
						callback->Failure(0, "The server refused to register you: " + msg.message);
					} else {
						browser->Reload();
					}
				}
			} else {
				callback->Failure(0, "Please fill all the fields!");
			}
		}

		void LoginController::setWebCore(WebCore *webCore) {
			this->m_webCore = webCore;
			this->m_modelHandler = this->m_webCore->getMvcHandler()->getModelHandler();
			std::string url = "file:///" + common::Toolbox::getApplicationDir() + "/../resources/html/login.html";
			this->m_webCore->changeUrl(url);
		}

		void LoginController::onFrameEnd() {
		}
	}
}
