//
// Created by diguie_t on 11/11/2017.
//

#ifndef CEFOFFSCREEN_GLFW_HANDLER_HH
#define CEFOFFSCREEN_GLFW_HANDLER_HH

#include "GL/glew.h"
#include "GLFW/glfw3.h"

namespace bl {
	class GlfwHandler {
	public:
		GlfwHandler();
		bool initGlfwWindow(
				int w,
				int h,
				const std::string &winName
		);
		void setupGlfw();
		void setUserPointer(void *pointer);
		void *getUserPointer();
		unsigned int getWidth() const;
		unsigned int getHeight() const;
		void setWinSize(
				unsigned int w,
				unsigned int h
		);
		std::pair<unsigned int, unsigned int> getWinSize() const;
		void shutDownGlfw();
		bool winShouldClose();
		void swapBuffer();
		void pollEvents();
	private:
		GLFWwindow *m_win;
	};
}
#endif //CEFOFFSCREEN_GLFW_HANDLER_HH
