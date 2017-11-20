cmake_minimum_required(VERSION 3.9)

set(CLIENT_PROJECT_DIR "${CMAKE_SOURCE_DIR}/")
set(CLIENT_PROJECT_NAME beyondlight_client)
set(CLIENT_EXECUTABLE_NAME beyondlight_client)
set(CLIENT_PERF_EXECUTABLE_NAME beyondlight_client_perftest)

set(CMAKE_CONFIGURATION_TYPES Debug Release) # todo debug not working atm

project(${CLIENT_PROJECT_NAME})

set(CMAKE_CXX_STANDARD 11)

set(CEF_ROOT "${CLIENT_PROJECT_DIR}/lib/cef")

list(APPEND CMAKE_MODULE_PATH ${CEF_ROOT}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CLIENT_PROJECT_DIR}/cmake)

set(CMAKE_PREFIX_PATH ${CEF_ROOT})
set(CEF_INCLUDE_DIR ${CEF_ROOT})
set(CEF_LIBRARY ${CEF_ROOT}/Release) #todo handle release and debug
set(GLEW_INCLUDE_DIR ${CLIENT_PROJECT_DIR}/lib/glew/include)
set(GLEW_LIBRARY ${CLIENT_PROJECT_DIR}/lib/glew/lib/Release/Win32) #todo handle release and debug
set(GLM_INCLUDE_DIR ${CLIENT_PROJECT_DIR}/lib/glm)
set(GLFW_INCLUDE_DIR ${CLIENT_PROJECT_DIR}/lib/glfw/include)
set(GLFW_LIBRARIES ${CLIENT_PROJECT_DIR}/lib/glfw)

find_package(CEF REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glew REQUIRED) # todo release version for both release & debug
#find_package(glfw REQUIRED) # todo release version for both release & debug
find_package(glm REQUIRED)

# Determine the platform.
if("${CMAKE_SYSTEM_NAME}" STREQUAL "Darwin")
    set(OS_MACOSX 1)
    set(OS_POSIX 1)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Linux")
    set(OS_LINUX 1)
    set(OS_POSIX 1)
elseif("${CMAKE_SYSTEM_NAME}" STREQUAL "Windows")
    set(OS_WINDOWS 1)
endif()

# Determine the platform.
if(OS_MACOSX)
    # set(CEF_URL https://cefbuilds.s3.amazonaws.com/2272/mac64/41.0.2272.76/cef_binary_3.2272.2077_macosx64.7z)
elseif(OS_LINUX)
    # set(CEF_URL https://cefbuilds.s3.amazonaws.com/2357/linux32/43.0.2357.18/cef_binary_3.2357.1267.g75b5dd4_linux32.7z)
elseif(OS_WINDOWS)
    # set(CEF_URL https://cefbuilds.s3.amazonaws.com/2357/win/43.0.2357.18/cef_binary_3.2357.1267.g75b5dd4_windows32.7z)
endif()

#if(NOT DEFINED CEF_URL)
#    message(FATAL_ERROR "No download URL specified for Chromium Embedded Framework")
#endif()

# Determine the project architecture.
if(NOT DEFINED PROJECT_ARCH)
    if(CMAKE_SIZEOF_VOID_P MATCHES 8)
        set(PROJECT_ARCH "x86_64")
    else()
        set(PROJECT_ARCH "x86")
    endif()
    set(CMAKE_CXX_FLAGS "-m32")
    if(OS_MACOSX)
        # PROJECT_ARCH should be specified on Mac OS X.
        message(WARNING "No PROJECT_ARCH value specified, using ${PROJECT_ARCH}")
    endif()
endif()

# Definition of Macros
add_definitions(
        -DDEBUG
        -DUNICODE
        -D_UNICODE
        -DGLFW_DLL
)

################### Dependencies ##################
# Add Dependencies to project.                    #
###################################################

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    link_directories(${CEF_ROOT}/Debug/ ${GLEW_LIBRARY})
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    link_directories(${CEF_ROOT}/Release/ ${GLEW_LIBRARY})
else()
    message("Unknown build type")
endif()

    ################# Flags ################
# Defines Flags for Windows and Linux. #
########################################

if(MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W3 /Od /Zi /EHsc")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /W3 /Oi /O2 /Gy /Zi /EHsc")
endif(MSVC)
if(NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif()
endif(NOT MSVC)

include_directories(${CEF_ROOT}
        ${GLM_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR})

# Display configuration settings.
PRINT_CEF_CONFIG()

set(CLIENT_SRC
        ${CLIENT_PROJECT_DIR}/BrowserClient.hh
        ${CLIENT_PROJECT_DIR}/BrowserClient.cpp
        ${CLIENT_PROJECT_DIR}/main.cpp
        ${CLIENT_PROJECT_DIR}/RenderHandler.hh
        ${CLIENT_PROJECT_DIR}/RenderHandler.cpp
        ${CLIENT_PROJECT_DIR}/WebCore.cpp
        ${CLIENT_PROJECT_DIR}/WebCore.hh
        ${CLIENT_PROJECT_DIR}/CallBacks.cpp
        ${CLIENT_PROJECT_DIR}/CallBacks.hh
        ${CLIENT_PROJECT_DIR}/GlfwHandler.cpp
        ${CLIENT_PROJECT_DIR}/GlfwHandler.hh
        ${CLIENT_PROJECT_DIR}/MainHandler.cpp
        ${CLIENT_PROJECT_DIR}/MainHandler.hh
        ${CLIENT_PROJECT_DIR}/WebCoreManager.cpp
        ${CLIENT_PROJECT_DIR}/WebCoreManager.hh
        ${CLIENT_PROJECT_DIR}/KeyHandler.cpp
        ${CLIENT_PROJECT_DIR}/KeyHandler.hh
        ${CLIENT_PROJECT_DIR}/Utils.cpp
        ${CLIENT_PROJECT_DIR}/Utils.hh
        ${CLIENT_PROJECT_DIR}/MessageHandler.cpp
        ${CLIENT_PROJECT_DIR}/MessageHandler.hh)
set(PERF_TEST_SRC
        ${CLIENT_PROJECT_DIR}/performance_test.cpp
        ${CLIENT_PROJECT_DIR}/Utils.cpp
        ${CLIENT_PROJECT_DIR}/Utils.hh)

add_executable(${CLIENT_EXECUTABLE_NAME} #WIN32 #todo uncomment if debug build
        ${CLIENT_SRC})

add_executable(${CLIENT_PERF_EXECUTABLE_NAME} ${PERF_TEST_SRC})

target_link_libraries(${CLIENT_EXECUTABLE_NAME} libcef_dll_wrapper libcef opengl32 glew32 ${GLFW_LIBRARIES}/glfw3dll.lib)
target_link_libraries(${CLIENT_PERF_EXECUTABLE_NAME} libcef_dll_wrapper libcef opengl32 glew32 ${GLFW_LIBRARIES}/glfw3dll.lib)