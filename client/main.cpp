#include <iostream>
#include <include/cef_app.h>
#include "GL/glew.h"
#include "MainHandler.hh"

std::string GetApplicationDir()
{
    HMODULE hModule = GetModuleHandleW(NULL);
    WCHAR   wpath[MAX_PATH];

    GetModuleFileNameW(hModule, wpath, MAX_PATH);
    std::wstring wide(wpath);

    std::string path = CefString(wide);
    path = path.substr( 0, path.find_last_of("\\/") );
    return path;
}


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