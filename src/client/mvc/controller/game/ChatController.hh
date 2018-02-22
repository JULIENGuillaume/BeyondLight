//
// Created by diguie_t on 2/18/2018.
//

#ifndef BEYONDLIGHT_CHATCONTROLLER_HH
#define BEYONDLIGHT_CHATCONTROLLER_HH

#include "../IBaseController.hh"
#include "../../../WebCore.hh"

namespace bl {
	namespace mvc {
		class ChatController : public IBaseController {
		public:
			void setWebCore(WebCore *webCore) override;
			bool onQuery(
					CefRefPtr<CefBrowser> browser,
					CefRefPtr<CefFrame> frame,
					int64 query_id,
					const CefString &request,
					bool persistent,
					CefRefPtr<CefMessageRouterBrowserSide::Callback> callback,
					std::string &newRoute
			) override;
			void onFrameEnd() override;
		private:
			static const std::string m_chatUrl;
			WebCore *m_webCore;
		};
	}
}

#endif //BEYONDLIGHT_CHATCONTROLLER_HH
