//
// Created by diguie_t on 11/11/2017.
//

#include <iostream>
#include "CallBacks.hh"
#include "MainHandler.hh"

void CallBacks::onError(int error, const char *description) {
    std::cerr << description << std::endl;
}

void
CallBacks::onKeyEvent(GLFWwindow *window, int key, int scancode, int action,
                      int mods) {
    static_cast<MainHandler *>(glfwGetWindowUserPointer(window))->onKeyEvent
            (window, key, scancode, action, mods);
}

void CallBacks::onMouseEvent(GLFWwindow *window, int btn, int state, int mods) {
    static_cast<MainHandler *>(glfwGetWindowUserPointer(window))
            ->onMouseEvent(window, btn, state, mods);
}

void CallBacks::onCursorMotion(GLFWwindow *window, double x, double y) {
    static_cast<MainHandler *>(glfwGetWindowUserPointer(window))
            ->onCursorMotion(window, x, y);
}

void CallBacks::onWinResize(GLFWwindow *window, int w, int h) {
    static_cast<MainHandler *>(glfwGetWindowUserPointer(window))->onWinResize
            (window, w, h);
}

void CallBacks::onCharEvent(GLFWwindow *window, unsigned int codepoint) {
    static_cast<MainHandler *>(glfwGetWindowUserPointer(window))->onCharEvent
            (window, codepoint);
}

void CallBacks::onScroll(GLFWwindow *window, double xoffset, double yoffset) {
    static_cast<MainHandler *>(glfwGetWindowUserPointer(window))->onScroll
            (window, xoffset, yoffset);
}

void CallBacks::onCursorEnter(GLFWwindow *window, int entered) {
    static_cast<MainHandler *>(glfwGetWindowUserPointer(window))->onCursorEnter
            (window, entered);
}
