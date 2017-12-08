//
// Created by diguie_t on 12/7/2017.
//

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "KeyMapper.hh"

namespace bl {
	const std::unordered_map<int, CefBrowserHost::MouseButtonType> KeyMapper::m_glfwMouseButtonToCef = {
			{GLFW_MOUSE_BUTTON_LEFT, MBT_LEFT},
			{GLFW_MOUSE_BUTTON_MIDDLE, MBT_MIDDLE},
			{GLFW_MOUSE_BUTTON_RIGHT, MBT_RIGHT}
	};

	const std::unordered_map<CefBrowserHost::MouseButtonType, unsigned int> KeyMapper::m_cefButtonToEventFlag = {
			{CefBrowserHost::MouseButtonType::MBT_LEFT, EVENTFLAG_LEFT_MOUSE_BUTTON},
			{CefBrowserHost::MouseButtonType::MBT_RIGHT, EVENTFLAG_RIGHT_MOUSE_BUTTON},
			{CefBrowserHost::MouseButtonType::MBT_MIDDLE, EVENTFLAG_MIDDLE_MOUSE_BUTTON}
	};
	
	CefBrowserHost::MouseButtonType KeyMapper::glfwMouseButtonToCef(int glfwMouseButton) {
		return (KeyMapper::m_glfwMouseButtonToCef.at(glfwMouseButton));
	}

	unsigned int KeyMapper::cefButtonToEventFlag(CefBrowserHost::MouseButtonType mouseButton) {
		const auto result = KeyMapper::m_cefButtonToEventFlag.find(mouseButton);
		if (result == KeyMapper::m_cefButtonToEventFlag.end()) {
			return (0);
		}
		return (result->second);
	}
}