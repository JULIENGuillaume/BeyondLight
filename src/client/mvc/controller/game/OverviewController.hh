//
// Created by diguie_t on 12/3/2017.
//

#ifndef BEYONDLIGHT_INDEXCONTROLLER_HH
#define BEYONDLIGHT_INDEXCONTROLLER_HH

#include <string>
#include "../IBaseController.hh"
#include "../../../WebCore.hh"

namespace bl {
	namespace mvc {
		class OverviewController : public IBaseController {
		public:
			OverviewController();
			void setWebCore(WebCore *webCore) override;
			std::string onQuery(
					CefRefPtr<CefBrowser> browser,
					CefRefPtr<CefFrame> frame,
					int64 query_id,
					const CefString &request,
					bool persistent,
					CefRefPtr<CefMessageRouterBrowserSide::Callback> callback
			) override;
			void onFrameEnd() override;
		private:
			WebCore *m_webCore;
		};
	}
}
#endif //BEYONDLIGHT_INDEXCONTROLLER_HH