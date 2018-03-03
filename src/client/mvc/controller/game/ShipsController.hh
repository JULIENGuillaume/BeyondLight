//
// Created by diguie_t on 3/3/2018.
//

#ifndef BEYONDLIGHT_SHIPSCONTROLLER_HH
#define BEYONDLIGHT_SHIPSCONTROLLER_HH

#include <string>
#include "../IBaseController.hh"

namespace bl {
	namespace mvc {
		class ShipsController : public IBaseController {
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
			static const std::string m_shipsUrl;
			WebCore *m_webCore;
		};
	}
}


#endif //BEYONDLIGHT_SHIPSCONTROLLER_HH
