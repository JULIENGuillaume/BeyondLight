#include <iostream>
#include <include/cef_app.h>
#include "GL/glew.h"
#include "MainHandler.hh"

int main(int ac, char *av[]) {
//int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    MainHandler mainHandler;

    if (mainHandler.init()) {
        std::cerr << "initialization failed!" << std::endl;
        return (1);
    }

    mainHandler.createBrowser();
    mainHandler.startMainLoop();

    mainHandler.destroy();

    return (0);
}