//
// Created by diguie_t on 11/11/2017.
//

#include <iostream>
// GL
#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "glm/glm.hpp"
#include "glm/ext.hpp"

#include "MainHandler.hh"
#include "RenderHandler.hh"
#include "../common/Toolbox.hh"

MainHandler::MainHandler() : _networkHandler(new network::client::NetworkHandler), _webCoreManager(_networkHandler) {
    this->_sizeUpdated = false;
    this->_frame = 0;
}

bool initialize_glew_context() // todo to member func
{
    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        // Problem: glewInit failed, something is seriously wrong
        std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
        return false;
    }
    return true;
}

bool MainHandler::init() {
    unsigned int width = 1280;
    unsigned int height = 720;

    this->_isInput = true;
    int exit_code = 0;
    bool success = this->_webCoreManager.setUp( &exit_code );
    if ( !success ) {
        return (true);
    }

    // create GL context
    if (this->_glfwHandler.initGlfwWindow(width, height, "Beyond Light")) {
        this->_webCoreManager.shutDown();
        return (true);
    }

    // initialize glew context
    bool glew_init_success = initialize_glew_context();
    if (!glew_init_success) {
        this->_webCoreManager.shutDown();
        return (true);
    }

    // setup glfw
    this->_glfwHandler.setupGlfw();
    this->_glfwHandler.setUserPointer(this);

    this->_networkHandler->test = "network is working";

    // init opengl & shader

    return false;
}

void MainHandler::createBrowser() {
    std::string url = "file:///" + common::Toolbox::getApplicationDir() + "/../resources/html/login.html";
    this->_webCore = this->_webCoreManager.createBrowser(url);
    this->_webCore.lock()->reshape(this->_glfwHandler.getWidth(),
                                   this->_glfwHandler.getHeight());
}

bool MainHandler::isSizeUpdated() {
    return (this->_sizeUpdated);
}

void MainHandler::sizeUpdate() {
    this->_sizeUpdated = true;
}

const GlfwHandler &MainHandler::getGlfwHandler() const {
    return (this->_glfwHandler);
}

bool MainHandler::startMainLoop() {
    this->_lastTickTime = glfwGetTime();
    while (!this->_glfwHandler.winShouldClose()) {
        if (this->_sizeUpdated) {
            this->_sizeUpdated = false;
            const std::pair<unsigned int, unsigned int> &size = this->_glfwHandler.getWinSize();
            this->_webCore.lock()->reshape(size.first, size.second);
        }

        const double currentTime = glfwGetTime();
        const double delta = currentTime - this->_lastTickTime;
        ++this->_frame;
        if (delta >= 1.0) {
            /*std::cout << std::to_string(1000.0 / this->_frame) << " ms/frame"
                      << std::endl;*/
            this->_frame = 0;
            this->_lastTickTime += 1.0;
        }

        const double begin = glfwGetTime();
        this->_webCore.lock()->getRenderHandler()->Render();

        // render end
        this->_glfwHandler.swapBuffer();

        // update
        this->_glfwHandler.pollEvents();

        this->_webCoreManager.update();
        const double end = glfwGetTime();
        /*if (delta >= 1.0) {
            std::cout << "it took: " << std::to_string(end - begin)
                      << " to render" << std::endl;
        }*/
    }
    return (false);
}

void MainHandler::destroy() {
    this->_glfwHandler.shutDownGlfw();

    // close cef
    this->_webCoreManager.removeBrowser(this->_webCore);
    this->_webCoreManager.shutDown();
}

void MainHandler::onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
    //if (!this->_isInput) // todo if isinput and key = delete -> send it
    this->_webCore.lock()->keyPress(key, scancode, action, mods);
    if (mods == GLFW_MOD_CONTROL) {
        if (key == GLFW_KEY_C) { // todo improve
            this->_webCore.lock()->copy();
        }
        if (key == GLFW_KEY_V) { // todo improve
            this->_webCore.lock()->paste();
        }
        if (key == GLFW_KEY_Q) { // todo improve
            this->_webCore.lock()->selectAll();
        }
        if (key == GLFW_KEY_X) { // todo improve
            this->_webCore.lock()->cut();
        }
        // todo handle tab
        // todo handle enter
    }
    if (key == GLFW_KEY_F5) {
        this->_webCore.lock()->reload(true); // todo remove debug
    }
}

void MainHandler::onMouseEvent(GLFWwindow *window, int btn, int state, int mods) {
    std::map<int, CefBrowserHost::MouseButtonType> btn_type_map; // todo improve
    btn_type_map[GLFW_MOUSE_BUTTON_LEFT] = MBT_LEFT;
    btn_type_map[GLFW_MOUSE_BUTTON_MIDDLE] = MBT_MIDDLE;
    btn_type_map[GLFW_MOUSE_BUTTON_RIGHT] = MBT_RIGHT;
    CefBrowserHost::MouseButtonType btn_type = btn_type_map[btn];

    this->_webCore.lock()->mouseClick(btn_type, (GLFW_RELEASE == state), mods);
}

void MainHandler::onCursorMotion(GLFWwindow *window, double x, double y) {
    this->_webCore.lock()->mouseMove(x, y, 1);
}

void MainHandler::onWinResize(GLFWwindow *window, int w, int h) {
    this->_glfwHandler.setWinSize(static_cast<unsigned int>(w),
                                  static_cast<unsigned int>(h));
    this->sizeUpdate();
}

void MainHandler::onCharEvent(GLFWwindow *window, unsigned int codepoint) {
    if (this->_isInput)
        this->_webCore.lock()->charPress(codepoint);
}

void MainHandler::onScroll(GLFWwindow *window, double x, double y) {
    this->_webCore.lock()->mouseScroll(x, y);
}

void MainHandler::onCursorEnter(GLFWwindow *window, int entered) {
    double x = 0;
    double y = 0;
    glfwGetCursorPos(window, &x, &y);
    this->_webCore.lock()->mouseMove(x, y, entered);
}

MainHandler::~MainHandler() {
    // todo destroy networkhandler ?
}
