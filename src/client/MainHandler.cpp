//
// Created by diguie_t on 11/11/2017.
//

#include <iostream>
#include <iomanip>
// GL
#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "glm/ext.hpp"
#include "MainHandler.hh"
#include "RenderHandler.hh"
#include "KeyMapper.hh"

namespace bl {
	MainHandler::MainHandler() :
			m_networkHandler(new network::client::NetworkHandler("127.0.0.1", 8080)),
			m_webCoreManager(m_networkHandler),
			m_winName("BeyondLight") {
		this->m_sizeUpdated = false;
		this->m_frame = 0;
		unsigned int width = 1280;
		unsigned int height = 720;
		this->m_isInput = true;

		// create GL context
		if (this->m_glfwHandler.createGlfwWindow(width, height, m_winName)) {
			throw (std::runtime_error("Error while setting up glfw handler"));
		}

		// initialize glew context
		bool glew_init_success = initializeGlewContext();
		if (!glew_init_success) {
			throw (std::runtime_error("Error while setting up glew context"));
		}

		// setup glfw
		this->m_glfwHandler.setUserPointer(this);
	}

	bool MainHandler::initializeGlewContext() {
		GLenum err = glewInit();
		if (GLEW_OK != err) {
			// Problem: glewInit failed, something is seriously wrong
			std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
			return false;
		}
		return true;
	}

	void MainHandler::createBrowser() {
		this->m_activeBrowser = this->m_webCoreManager.createBrowser(std::string());
		this->m_activeBrowser.lock()->reshape(this->m_glfwHandler.getWidth(), this->m_glfwHandler.getHeight());
	}

	bool MainHandler::isSizeUpdated() {
		return (this->m_sizeUpdated);
	}

	void MainHandler::sizeUpdate() {
		this->m_sizeUpdated = true;
	}

	const GlfwHandler &MainHandler::getGlfwHandler() const {
		return (this->m_glfwHandler);
	}

	bool MainHandler::startMainLoop() {
		while (!this->m_glfwHandler.winShouldClose()) {
			if (this->m_sizeUpdated) {
				this->m_sizeUpdated = false;
				const std::pair<unsigned int, unsigned int> &size = this->m_glfwHandler.getWinSize();
				this->m_activeBrowser.lock()->reshape(size.first, size.second);
			}
			++this->m_frame;
			this->m_activeBrowser.lock()->getRenderHandler()->Render();

			// render end
			this->m_glfwHandler.swapBuffer();

			// update
			this->m_glfwHandler.pollEvents();
			this->m_webCoreManager.update();
			this->updateMsFrameWinTitle();
		}
		return (false);
	}

	void MainHandler::onKeyEvent( // todo improve
			GLFWwindow *window,
			int key,
			int scancode,
			int action,
			int mods
	) {
		//if (!this->m_isInput) // todo if isinput and key = delete -> send it
		this->m_activeBrowser.lock()->keyPress(key, scancode, action, mods);
		if (mods == GLFW_MOD_CONTROL) {
			if (key == GLFW_KEY_C) {
				this->m_activeBrowser.lock()->copy();
			}
			if (key == GLFW_KEY_V) {
				this->m_activeBrowser.lock()->paste();
			}
			if (key == GLFW_KEY_Q) {
				this->m_activeBrowser.lock()->selectAll();
			}
			if (key == GLFW_KEY_X) {
				this->m_activeBrowser.lock()->cut();
			}
		}
		if (key == GLFW_KEY_F5) {
			this->m_activeBrowser.lock()->reload(true); // todo remove debug
		}
	}

	void MainHandler::onMouseEvent(
			GLFWwindow *window,
			int btn,
			int state,
			int mods
	) {
		this->m_activeBrowser.lock()->mouseClick(KeyMapper::glfwMouseButtonToCef(btn), (GLFW_RELEASE == state), mods);
	}

	void MainHandler::onCursorMotion(
			GLFWwindow *window,
			double x,
			double y
	) {
		this->m_activeBrowser.lock()->mouseMove(x, y, 1);
	}

	void MainHandler::onWinResize(
			GLFWwindow *window,
			int w,
			int h
	) {
		this->m_glfwHandler.setWinSize(static_cast<unsigned int>(w), static_cast<unsigned int>(h));
		this->sizeUpdate();
	}

	void MainHandler::onCharEvent(
			GLFWwindow *window,
			unsigned int codepoint
	) {
		if (this->m_isInput) {
			this->m_activeBrowser.lock()->charPress(codepoint);
		}
	}

	void MainHandler::onScroll(
			GLFWwindow *window,
			double x,
			double y
	) {
		this->m_activeBrowser.lock()->mouseScroll(x, y);
	}

	void MainHandler::onCursorEnter(
			GLFWwindow *window,
			int entered
	) {
		double x = 0;
		double y = 0;
		glfwGetCursorPos(window, &x, &y);
		this->m_activeBrowser.lock()->mouseMove(x, y, entered);
	}

	MainHandler::~MainHandler() {
		// close cef
		this->m_webCoreManager.removeBrowser(this->m_activeBrowser);
		this->m_networkHandler = nullptr;
	}

	void MainHandler::updateMsFrameWinTitle() {
		double msFrame = this->m_activeBrowser.lock()->getRenderHandler()->getAverageFrameCallTime();
		if (msFrame != this->m_avgFrameCallTime) {
			this->m_avgFrameCallTime = msFrame;
			std::stringstream frameMs;
			frameMs << std::fixed << std::setprecision(2) << this->m_avgFrameCallTime;
			this->m_glfwHandler.setWinTitle(this->m_winName + " " + frameMs.str() + " CEF ms/Frame");
		}
	}
}