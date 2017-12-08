//
// Created by diguie_t on 12/7/2017.
//

#ifndef BEYONDLIGHT_KEYMAPPER_HH
#define BEYONDLIGHT_KEYMAPPER_HH

#include <include/cef_browser.h>
#include <unordered_map>

namespace bl {
	class KeyMapper {
	public:
		static CefBrowserHost::MouseButtonType glfwMouseButtonToCef(int glfwMouseButton);
		static unsigned int cefButtonToEventFlag(CefBrowserHost::MouseButtonType mouseButton);
	private:
		static const std::unordered_map<int, CefBrowserHost::MouseButtonType> m_glfwMouseButtonToCef;
		static const std::unordered_map<CefBrowserHost::MouseButtonType, unsigned int> m_cefButtonToEventFlag;
	};
}

#endif //BEYONDLIGHT_KEYMAPPER_HH
