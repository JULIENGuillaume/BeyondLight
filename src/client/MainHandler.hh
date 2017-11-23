//
// Created by diguie_t on 11/11/2017.
//

#ifndef CEFOFFSCREEN_MAINHANDLER_HH
#define CEFOFFSCREEN_MAINHANDLER_HH

#include "include/base/cef_basictypes.h"
#include "WebCoreManager.hh"
#include "WebCore.hh"
#include "GlfwHandler.hh"

class MainHandler {
private:
    std::shared_ptr<network::client::NetworkHandler> _networkHandler;
    std::weak_ptr<WebCore> _webCore;
    WebCoreManager _webCoreManager;
    GlfwHandler _glfwHandler;
    bool _sizeUpdated;
    uint64 _frame;
    double _lastTickTime;
    bool _isInput;
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
    void onKeyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
    void onCharEvent(GLFWwindow* window, unsigned int codepoint);
    void onMouseEvent(GLFWwindow* window, int btn, int state, int mods);
    void onCursorMotion(GLFWwindow* window, double x, double y);
    void onWinResize(GLFWwindow* window, int w, int h);
    void onScroll(GLFWwindow* window, double x, double y);

    void onCursorEnter(GLFWwindow *pWwindow, int i);
};


#endif //CEFOFFSCREEN_MAINHANDLER_HH
