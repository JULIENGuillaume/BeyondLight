//
// Created by diguie_t on 11/11/2017.
//

#include <string>
#include "GlfwHandler.hh"
#include "CallBacks.hh"

bool GlfwHandler::initGlfwWindow(int w, int h, const std::string &winName) {
    glfwSetErrorCallback(&CallBacks::onError);
    if (!glfwInit()) {
        return (true);
    }

    GLFWwindow* window = glfwCreateWindow(w, h, winName.c_str(), nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return (true);
    }
    glfwMakeContextCurrent(window);
    this->_win = window;

    return (false);
}

void GlfwHandler::shutDownGlfw() {
    glfwDestroyWindow(this->_win);
    glfwTerminate();
}

void GlfwHandler::setupGlfw() {
    glfwSwapInterval(1);
    glfwSetKeyCallback(this->_win, CallBacks::onKeyEvent);
    glfwSetCharCallback(this->_win, CallBacks::onCharEvent);
    glfwSetCursorPosCallback(this->_win, CallBacks::onCursorMotion);
    glfwSetMouseButtonCallback(this->_win, CallBacks::onMouseEvent);
    glfwSetFramebufferSizeCallback(this->_win, CallBacks::onWinResize);
}

GlfwHandler::GlfwHandler() {
}

void GlfwHandler::setWinSize(unsigned int w, unsigned int h) {
    glViewport(0, 0, w, h);
}

void GlfwHandler::setUserPointer(void *pointer) {
    glfwSetWindowUserPointer(this->_win, pointer);
}

void *GlfwHandler::getUserPointer() {
    return (glfwGetWindowUserPointer(this->_win));
}

unsigned int GlfwHandler::getWidth() const {
    unsigned int width;

    glfwGetWindowSize(this->_win, reinterpret_cast<int *>(&width), nullptr);
    return (width);
}

unsigned int GlfwHandler::getHeight() const {
    unsigned int height;

    glfwGetWindowSize(this->_win, nullptr, reinterpret_cast<int *>(&height));
    return (height);
}

bool GlfwHandler::winShouldClose() {
    return (glfwWindowShouldClose(this->_win));
}

std::pair<unsigned int, unsigned int> GlfwHandler::getWinSize() const {
    std::pair<unsigned int, unsigned int> size;
    glfwGetWindowSize(this->_win, reinterpret_cast<int *>(&size.first),
                      reinterpret_cast<int *>(&size.second));
    return (size);
}

void GlfwHandler::swapBuffer() {
    glfwSwapBuffers(this->_win);
}

void GlfwHandler::pollEvents() {
    glfwPollEvents();
}
