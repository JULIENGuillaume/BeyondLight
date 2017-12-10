//
// Created by diguie_t on 12/9/2017.
//

#ifndef BEYONDLIGHT_BUILDINGSCONTROLLER_HH
#define BEYONDLIGHT_BUILDINGSCONTROLLER_HH

#include "../IBaseController.hh"
#include "../../../WebCore.hh"

namespace bl {
	namespace mvc {
		class BuildingsController : public IBaseController {
		public:
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
			static const std::string m_buildingsUrl;
			WebCore *m_webCore;
		};
	}
}

#endif //BEYONDLIGHT_BUILDINGSCONTROLLER_HH
