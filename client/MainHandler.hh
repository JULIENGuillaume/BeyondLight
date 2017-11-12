//
// Created by diguie_t on 11/11/2017.
//

#ifndef CEFOFFSCREEN_MAINHANDLER_HH
#define CEFOFFSCREEN_MAINHANDLER_HH

#include "include/base/cef_basictypes.h"
#include "WebCoreManager.hh"
#include "WebCore.hh"
#include "GlfwHandler.hh"
#include "GLCore.hh"

class MainHandler {
private:
    std::weak_ptr<WebCore> _webCore;
    WebCoreManager _webCoreManager;
    GlfwHandler _glfwHandler;
    GLCore _glCore;
    bool _sizeUpdated;
    uint64 _frame;
    double _lastTickTime;
    bool _isInput;
public:
    MainHandler();
    bool init();
    void createBrowser();
    bool isSizeUpdated();
    void sizeUpdate();
    const GlfwHandler &getGlfwHandler() const;
    bool startMainLoop();
    void destroy();
    void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
    void onCharEvent(GLFWwindow* window, unsigned int codepoint);
    void onMouseEvent(GLFWwindow* window, int btn, int state, int mods);
    void onCursorMotion(GLFWwindow* window, double x, double y);
    void onWinResize(GLFWwindow* window, int w, int h);

};


#endif //CEFOFFSCREEN_MAINHANDLER_HH
