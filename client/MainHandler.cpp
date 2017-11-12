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

MainHandler::MainHandler() {
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
    std::cout << "Status: Using GLEW "<< glewGetString(GLEW_VERSION) << std::endl;
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

    // init opengl & shader
    this->_glCore.init(width, height);

    return false;
}

void MainHandler::createBrowser() {
    std::string url = "file:///E:/Desktop/BeyondLight/Git/BeyondLight/client/html/header.html"; // todo fix hard path
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
        ++this->_frame;
        if ((currentTime - this->_lastTickTime) >= 1.0) {
            std::cout << std::to_string(1000.0 / this->_frame) << " ms/frame"
                      << std::endl;
            this->_frame = 0;
            this->_lastTickTime += 1.0;
        }
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(this->_glCore.getProg());

        glm::mat4 mvp = glm::ortho(-1, 1, -1, 1);
        glUniformMatrix4fv(this->_glCore.getMvpLoc(), 1, GL_FALSE, glm::value_ptr(mvp));

        glEnableVertexAttribArray(this->_glCore.getPosLoc());
        glEnableVertexAttribArray(this->_glCore.getTexcoordLoc());

        // bind texture
        glBindTexture(GL_TEXTURE_2D,
                      this->_webCore.lock()->getRenderHandler()->getTex());

        // draw
        glVertexAttribPointer(this->_glCore.getPosLoc(), 3, GL_FLOAT, GL_FALSE, 0, this->_glCore.getVertices());
        glVertexAttribPointer(this->_glCore.getTexcoordLoc(), 2, GL_FLOAT, GL_FALSE, 0, this->_glCore.getTexCoords());
        glDrawElements(GL_TRIANGLES, this->_glCore.getNbIndices(), GL_UNSIGNED_SHORT, this->_glCore.getIndices());

        // render end
        this->_glfwHandler.swapBuffer();

        // update
        this->_glfwHandler.pollEvents();

        this->_webCoreManager.update();
    }
    return (false);
}

void MainHandler::destroy() {
    this->_glfwHandler.shutDownGlfw();
    this->_glCore.destroy();

    // close cef
    this->_webCoreManager.removeBrowser(this->_webCore);
    this->_webCoreManager.shutDown();
}

void MainHandler::onKeyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
    //if (!this->_isInput) // todo if isinput and key = delete -> send it
        this->_webCore.lock()->keyPress(key, scancode, action, mods);
}

void MainHandler::onMouseEvent(GLFWwindow *window, int btn, int state, int mods) {
    int mouse_up = (GLFW_RELEASE == state);

    std::map<int, CefBrowserHost::MouseButtonType> btn_type_map; // todo improve
    btn_type_map[GLFW_MOUSE_BUTTON_LEFT] = MBT_LEFT;
    btn_type_map[GLFW_MOUSE_BUTTON_MIDDLE] = MBT_MIDDLE;
    btn_type_map[GLFW_MOUSE_BUTTON_RIGHT] = MBT_RIGHT;
    CefBrowserHost::MouseButtonType btn_type = btn_type_map[btn];

    this->_webCore.lock()->mouseClick(btn_type, mouse_up);
}

void MainHandler::onCursorMotion(GLFWwindow *window, double x, double y) {
    this->_webCore.lock()->mouseMove(static_cast<int>(x), static_cast<int>(y));
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