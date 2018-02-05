//
// Created by diguie_t on 12/7/2017.
//

#include "KeyMapper.hh"
#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace bl {
	const std::unordered_map<int, CefBrowserHost::MouseButtonType> KeyMapper::m_glfwMouseButtonToCef = {
			{GLFW_MOUSE_BUTTON_LEFT,   MBT_LEFT},
			{GLFW_MOUSE_BUTTON_MIDDLE, MBT_MIDDLE},
			{GLFW_MOUSE_BUTTON_RIGHT,  MBT_RIGHT}
	};
	const std::unordered_map<CefBrowserHost::MouseButtonType, unsigned int> KeyMapper::m_cefButtonToEventFlag = {
			{CefBrowserHost::MouseButtonType::MBT_LEFT,   EVENTFLAG_LEFT_MOUSE_BUTTON},
			{CefBrowserHost::MouseButtonType::MBT_RIGHT,  EVENTFLAG_RIGHT_MOUSE_BUTTON},
			{CefBrowserHost::MouseButtonType::MBT_MIDDLE, EVENTFLAG_MIDDLE_MOUSE_BUTTON}
	};
	const std::unordered_map<int, unsigned int> KeyMapper::m_glfwKeyToNative = {
			{GLFW_KEY_BACKSPACE, VK_BACK},
			{GLFW_KEY_PAGE_UP,   VK_PRIOR},
			{GLFW_KEY_PAGE_DOWN, VK_NEXT},
			{GLFW_KEY_TAB,       VK_TAB},
			{GLFW_KEY_ENTER,     VK_RETURN}
	};
	static const std::unordered_map<int, cef_key_event_type_t> m_glfwActionToCef = {
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

	unsigned int KeyMapper::glfwKeyToNative(int glfwKey) {
		const auto result = KeyMapper::m_glfwKeyToNative.find(glfwKey);
		if (result == KeyMapper::m_glfwKeyToNative.end()) {
			return (0);
		}
		return (result->second);
	}

	cef_key_event_type_t KeyMapper::glfwActionToCef(int action) {
		if (action == GLFW_PRESS) {
			return (KEYEVENT_RAWKEYDOWN);
		} else {
			return (KEYEVENT_KEYUP);
		}
	}
}