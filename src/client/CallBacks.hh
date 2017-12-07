//
// Created by diguie_t on 11/11/2017.
//

#ifndef CEFOFFSCREEN_CALLBACKS_HH
#define CEFOFFSCREEN_CALLBACKS_HH

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace bl {
	class CallBacks {
	public:
		static void onError(
				int error,
				const char *description
		);
		static void onKeyEvent(
				GLFWwindow *window,
				int key,
				int scancode,
				int action,
				int mods
		);
		static void onMouseEvent(
				GLFWwindow *window,
				int btn,
				int state,
				int mods
		);
		static void onCursorMotion(
				GLFWwindow *window,
				double x,
				double y
		);
		static void onWinResize(
				GLFWwindow *window,
				int w,
				int h
		);
		static void onCharEvent(
				GLFWwindow *window,
				unsigned int codepoint
		);
		static void onScroll(
				GLFWwindow *window,
				double xoffset,
				double yoffset
		);
		static void onCursorEnter(
				GLFWwindow *window,
				int entered
		);
	};
}
#endif //CEFOFFSCREEN_CALLBACKS_HH
