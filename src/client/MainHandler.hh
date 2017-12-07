//
// Created by diguie_t on 11/11/2017.
//

#ifndef CEFOFFSCREEN_MAINHANDLER_HH
#define CEFOFFSCREEN_MAINHANDLER_HH

#include "include/base/cef_basictypes.h"
#include "WebCoreManager.hh"
#include "WebCore.hh"
#include "GlfwHandler.hh"
#include "mvc/MvcHandler.hh"

namespace bl {
	class MainHandler {
	public:
		MainHandler();
		~MainHandler();
		bool init();
		void createBrowser();
		bool isSizeUpdated();
		void sizeUpdate();
		const GlfwHandler &getGlfwHandler() const;
		bool startMainLoop();
		void destroy();
		void onKeyEvent(
				GLFWwindow *window,
				int key,
				int scancode,
				int action,
				int mods
		);
		void onCharEvent(
				GLFWwindow *window,
				unsigned int codepoint
		);
		void onMouseEvent(
				GLFWwindow *window,
				int btn,
				int state,
				int mods
		);
		void onCursorMotion(
				GLFWwindow *window,
				double x,
				double y
		);
		void onWinResize(
				GLFWwindow *window,
				int w,
				int h
		);
		void onScroll(
				GLFWwindow *window,
				double x,
				double y
		);
		void onCursorEnter(
				GLFWwindow *pWwindow,
				int i
		);
	private:
		std::shared_ptr<network::client::NetworkHandler> m_networkHandler;
		std::weak_ptr<WebCore> m_activeBrowser;
		WebCoreManager m_webCoreManager;
		GlfwHandler m_glfwHandler;
		bool m_sizeUpdated;
		uint64 m_frame;
		double m_lastTickTime;
		bool m_isInput;

	};
}
#endif //CEFOFFSCREEN_MAINHANDLER_HH
