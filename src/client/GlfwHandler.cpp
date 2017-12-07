//
// Created by diguie_t on 11/11/2017.
//

#include <string>
#include "GlfwHandler.hh"
#include "CallBacks.hh"

namespace bl {
    bool GlfwHandler::initGlfwWindow(int w, int h, const std::string &winName) {
        glfwSetErrorCallback(&CallBacks::onError);
        if (!glfwInit()) {
            return (true);
        }

        GLFWwindow *window = glfwCreateWindow(w, h, winName.c_str(), nullptr,
                                              nullptr);
        if (!window) {
            glfwTerminate();
            return (true);
        }
        glfwMakeContextCurrent(window);
        this->m_win = window;

        return (false);
    }

    void GlfwHandler::shutDownGlfw() {
        glfwDestroyWindow(this->m_win);
        glfwTerminate();
    }

    void GlfwHandler::setupGlfw() {
        glfwSwapInterval(1);
        glfwSetKeyCallback(this->m_win, CallBacks::onKeyEvent);
        glfwSetCharCallback(this->m_win, CallBacks::onCharEvent);
        glfwSetCursorPosCallback(this->m_win, CallBacks::onCursorMotion);
        glfwSetMouseButtonCallback(this->m_win, CallBacks::onMouseEvent);
        glfwSetFramebufferSizeCallback(this->m_win, CallBacks::onWinResize);
        glfwSetScrollCallback(this->m_win, CallBacks::onScroll);
    }

    GlfwHandler::GlfwHandler() {
    }

    void GlfwHandler::setWinSize(unsigned int w, unsigned int h) {
        glViewport(0, 0, w, h);
    }

    void GlfwHandler::setUserPointer(void *pointer) {
        glfwSetWindowUserPointer(this->m_win, pointer);
    }

    void *GlfwHandler::getUserPointer() {
        return (glfwGetWindowUserPointer(this->m_win));
    }

    unsigned int GlfwHandler::getWidth() const {
        unsigned int width;

        glfwGetWindowSize(this->m_win, reinterpret_cast<int *>(&width), nullptr);
        return (width);
    }

    unsigned int GlfwHandler::getHeight() const {
        unsigned int height;

        glfwGetWindowSize(this->m_win, nullptr,
                          reinterpret_cast<int *>(&height));
        return (height);
    }

    bool GlfwHandler::winShouldClose() {
        return (glfwWindowShouldClose(this->m_win));
    }

    std::pair<unsigned int, unsigned int> GlfwHandler::getWinSize() const {
        std::pair<unsigned int, unsigned int> size;
        glfwGetWindowSize(this->m_win, reinterpret_cast<int *>(&size.first),
                          reinterpret_cast<int *>(&size.second));
        return (size);
    }

    void GlfwHandler::swapBuffer() {
        glfwSwapBuffers(this->m_win);
    }

    void GlfwHandler::pollEvents() {
        glfwPollEvents();
    }
}