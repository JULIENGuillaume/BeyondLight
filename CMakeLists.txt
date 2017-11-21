cmake_minimum_required(VERSION 3.9)
project(BeyondLight)

##
##  CMake initialization, with flags and cpp standard version
##

set(CMAKE_CXX_STANDARD 17)

if(${MINGW})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith \
                                        -Wcast-align -Wswitch-enum -Wconversion -Wunreachable-code \
                                        -Wwrite-strings -fstack-check -pipe -ftrapv --std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -Og")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Ofast -s")
endif()

##
##  BOOST setup
##

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREAD ON)
set(BOOST_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/libs/Boost)
find_package(Boost 1.65 COMPONENTS REQUIRED chrono system regex date_time)

##
##  Set path to source directories
##

set(SRC_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(CLIENT_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/client)
set(NETWORK_SERVER_SRC_DIR "${SRC_BASE_DIR}/network/server")
set(NETWORK_CLIENT_SRC_DIR "${SRC_BASE_DIR}/network/client")
set(NETWORK_SOCKET_SRC_DIR "${SRC_BASE_DIR}/network/socket")
set(USER_SRC_DIR "${SRC_BASE_DIR}/server/user")
set(COMMON_SRC_DIR "${SRC_BASE_DIR}/common")

##
##  Common sources
##

set(COMMON_SRC src/common/Toolbox.cpp src/common/Toolbox.hh)

##
##  Game client sources
##

set(CLIENT_SRC
        ${CLIENT_PROJECT_DIR}/BrowserClient.hh
        ${CLIENT_PROJECT_DIR}/BrowserClient.cpp
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
        ${CLIENT_PROJECT_DIR}/MessageHandler.hh src/common/NetworkWrapper.hh)

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

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    link_directories(${CEF_ROOT}/Debug/ ${GLEW_LIBRARY})
elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
    link_directories(${CEF_ROOT}/Release/ ${GLEW_LIBRARY})
else()
    message("Unknown build type")
endif()

include_directories(${CEF_ROOT}
        ${GLM_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR})

##
##  Network sources
##

set(NETWORK_SOCKET_SRC ${NETWORK_SOCKET_SRC_DIR}/UdpSslAsyncBoostSocket.cpp)
set(NETWORK_SERVER_SRC ${NETWORK_SERVER_SRC_DIR}/AServerUdp.cpp ${NETWORK_SERVER_SRC_DIR}/BeyondLightServer.cpp ${NETWORK_SERVER_SRC_DIR}/BeyondLightServer.hh)
set(NETWORK_CLIENT_SRC ${NETWORK_CLIENT_SRC_DIR}/AClientUdp.cpp ${NETWORK_CLIENT_SRC_DIR}/BeyondLightClient.cpp ${NETWORK_CLIENT_SRC_DIR}/BeyondLightClient.hh)

set(NETWORK_INCLUDE_DIRS ${SRC_BASE_DIR}/network/socket ${SRC_BASE_DIR}/network/client
        ${SRC_BASE_DIR}/network/factories ${SRC_BASE_DIR}/network/server)

##
##  User sources
##

set(USER_SRC src/server/user/User.cpp src/server/user/User.hh src/server/user/AuthSystem.cpp src/server/user/AuthSystem.hh src/server/user/RegisteredUsers.cpp src/server/user/RegisteredUsers.hh src/network/socket/SocketMessage.cpp src/network/socket/SocketMessage.hh)

add_executable(BeyondLightServer ${NETWORK_SERVER_SRC_DIR}/main.cpp ${NETWORK_SERVER_SRC} ${NETWORK_SOCKET_SRC} ${USER_SRC} ${COMMON_SRC})
add_executable(BeyondLightClient ${NETWORK_CLIENT_SRC_DIR}/main.cpp ${NETWORK_CLIENT_SRC} ${NETWORK_SOCKET_SRC} ${COMMON_SRC} ${CLIENT_SRC})

target_include_directories(BeyondLightServer PRIVATE ${Boost_INCLUDE_DIRS} ${NETWORK_INCLUDE_DIRS})
target_include_directories(BeyondLightClient PRIVATE ${Boost_INCLUDE_DIRS} ${NETWORK_INCLUDE_DIRS})

IF (UNIX)
    target_link_libraries(BeyondLightServer ${Boost_LIBRARIES} pthread)
    target_link_libraries(BeyondLightClient ${Boost_LIBRARIES} pthread)
ELSE ()

    include(${CLIENT_PROJECT_DIR}/CMakeLists.txt)

  target_link_libraries(BeyondLightServer ${Boost_LIBRARIES} ws2_32)
  target_link_libraries(BeyondLightClient ${Boost_LIBRARIES} ws2_32 libcef_dll_wrapper libcef opengl32 glew32 ${GLFW_LIBRARIES}/glfw3dll.lib)
ENDIF (UNIX)

##
##  Compile the test environment with Google test, optionnal
##

find_package(GTest)
IF (GTEST_FOUND)
    message("-- Google test has been found, setting up test environment")
    set(UNIT_TEST_SRCS test/unittest.cpp  ${NETWORK_SERVER_SRC} ${NETWORK_CLIENT_SRC} ${NETWORK_SOCKET_SRC})
    add_executable(TestSuit ${UNIT_TEST_SRCS} ${COMMON_SRC})

    target_include_directories(TestSuit PRIVATE ${GTEST_INCLUDE_DIRS} ${NETWORK_INCLUDE_DIRS})
    IF (UNIX)
        target_link_libraries(TestSuit ${Boost_LIBRARIES} ${GTEST_BOTH_LIBRARIES} pthread)
    ELSEIF (WIN32)
        target_link_libraries(TestSuit ${Boost_LIBRARIES} ${GTEST_BOTH_LIBRARIES})
    ENDIF (UNIX)
ENDIF (GTEST_FOUND)