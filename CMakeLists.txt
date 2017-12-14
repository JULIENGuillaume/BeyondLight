# to build on visual studio
#cmake .. -G "Visual Studio 15"
#cmake .. -G "Visual Studio 15" -DCMAKE_BUILD_TYPE="Release"

cmake_minimum_required(VERSION 3.9)
project(BeyondLight)

##
##  CMake initialization, with flags and cpp standard version
##

set(CMAKE_CXX_STANDARD 17)

set(CLIENT_PERF_EXECUTABLE_NAME BeyondLightClientPerfTest)

if (WIN32)
    add_definitions(-D_WIN32_WINNT=0x0A00)
endif ()

# Determine the project architecture.
if (NOT DEFINED PROJECT_ARCH)
    if (CMAKE_SIZEOF_VOID_P MATCHES 8)
        set(PROJECT_ARCH "x86_64")
    else ()
        set(PROJECT_ARCH "x86")
    endif ()
    if (NOT MSVC)
        set(CMAKE_CXX_FLAGS "-m32")
    endif ()
    if (OS_MACOSX)
        # PROJECT_ARCH should be specified on Mac OS X.
        message(WARNING "No PROJECT_ARCH value specified, using ${PROJECT_ARCH}")
    endif ()
endif ()

if (${MINGW})
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith \
                                        -Wcast-align -Wswitch-enum -Wconversion -Wunreachable-code \
                                        -Wwrite-strings -fstack-check -pipe -ftrapv --std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -Og")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Ofast -s")
endif ()

################# Flags ################
# Defines Flags for Windows and Linux. #
########################################

if (MSVC)
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /W3 /Od /Zi /EHsc")
    set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} /W3 /Oi /O2 /Gy /Zi /EHsc")
endif (MSVC)
if (NOT MSVC)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11") # todo remove overwriting flags
    if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++")
    endif ()
endif (NOT MSVC)

# Definition of Macros
add_definitions(
        -DDEBUG
        #        -DUNICODE
        #        -D_UNICODE
        #        -DGLFW_DLL
)

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
set(CLIENT_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/client)
set(CLIENT_TEST_PROJECT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src/client-test)
set(NETWORK_SERVER_SRC_DIR "${SRC_BASE_DIR}/network/server")
set(NETWORK_CLIENT_SRC_DIR "${SRC_BASE_DIR}/network/client")
set(NETWORK_SOCKET_SRC_DIR "${SRC_BASE_DIR}/network/socket")
set(USER_SRC_DIR "${SRC_BASE_DIR}/server/user")
set(GAME_SRC_DIR "${SRC_BASE_DIR}/server/game")
set(COMMON_SRC_DIR "${SRC_BASE_DIR}/common")

##
##  Common sources
##

set(COMMON_SRC src/common/Toolbox.cpp src/common/Toolbox.hh src/common/pattern/ISerializable.hh)

##
##  Game Client perf test
##
set(PERF_TEST_SRC
        ${CLIENT_TEST_PROJECT_DIR}/performance_test.cpp
        src/common/Toolbox.cpp
        src/common/Toolbox.hh
        )

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
        ${CLIENT_PROJECT_DIR}/MessageHandler.cpp
        ${CLIENT_PROJECT_DIR}/MessageHandler.hh
        ${CLIENT_PROJECT_DIR}/KeyMapper.cpp
        ${CLIENT_PROJECT_DIR}/KeyMapper.hh
        ${CLIENT_PROJECT_DIR}/ImageLoader.cpp
        ${CLIENT_PROJECT_DIR}/ImageLoader.hh
        src/common/NetworkWrapper.hh
        src/common/Toolbox.cpp
        src/common/Toolbox.hh
        src/common/game/Resources.cpp
        src/common/game/Resources.hh
        src/network/client/NetworkHandler.cpp
        src/network/client/NetworkHandler.hh
        src/common/event/IEventObserver.hh
        src/common/event/EventObserver.cpp
        src/common/event/EventObserver.hh
        src/common/pattern/Observator.hpp
        ${CLIENT_PROJECT_DIR}/mvc/DataHandler.hpp
        ${CLIENT_PROJECT_DIR}/mvc/controller/IBaseController.hh
        ${CLIENT_PROJECT_DIR}/mvc/controller/ControllerHandler.cpp
        ${CLIENT_PROJECT_DIR}/mvc/controller/ControllerHandler.hh
        ${CLIENT_PROJECT_DIR}/mvc/controller/ControllerFactory.hpp
        ${CLIENT_PROJECT_DIR}/mvc/controller/IControllerFactory.hh
        ${CLIENT_PROJECT_DIR}/mvc/model/ModelHandler.cpp
        ${CLIENT_PROJECT_DIR}/mvc/model/ModelHandler.hh
        ${CLIENT_PROJECT_DIR}/mvc/model/ABaseModel.cpp
        ${CLIENT_PROJECT_DIR}/mvc/model/ABaseModel.hh
        ${CLIENT_PROJECT_DIR}/mvc/model/BuildingModel.cpp
        ${CLIENT_PROJECT_DIR}/mvc/model/BuildingModel.hh
        ${CLIENT_PROJECT_DIR}/mvc/MvcHandler.cpp
        ${CLIENT_PROJECT_DIR}/mvc/MvcHandler.hh
        ${CLIENT_PROJECT_DIR}/mvc/controller/LoginController.cpp
        ${CLIENT_PROJECT_DIR}/mvc/controller/LoginController.hh
        ${CLIENT_PROJECT_DIR}/mvc/controller/game/OverviewController.cpp
        ${CLIENT_PROJECT_DIR}/mvc/controller/game/OverviewController.hh
        ${CLIENT_PROJECT_DIR}/mvc/controller/game/BuildingsController.cpp
        ${CLIENT_PROJECT_DIR}/mvc/controller/game/BuildingsController.hh
        ${CLIENT_PROJECT_DIR}/mvc/controller/game/TechnologiesController.cpp
        ${CLIENT_PROJECT_DIR}/mvc/controller/game/TechnologiesController.hh
        ${CLIENT_PROJECT_DIR}/mvc/controller/game/LeftMenu.cpp
        ${CLIENT_PROJECT_DIR}/mvc/controller/game/LeftMenu.hh
        libs/stb/stb_image.h
        )

set(CEF_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/libs/cef")

list(APPEND CMAKE_MODULE_PATH ${CEF_ROOT}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)
list(APPEND CMAKE_MODULE_PATH ${CLIENT_PROJECT_DIR}/cmake)

set(CMAKE_PREFIX_PATH ${CEF_ROOT})
set(CEF_INCLUDE_DIR ${CEF_ROOT})
if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CEF_LIBRARY ${CEF_ROOT}/Debug)
    set(GLEW_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/lib/Release/Win32) #todo add debug for glew
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(CEF_LIBRARY ${CEF_ROOT}/Release)
    set(GLEW_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/lib/Release/Win32)
else ()
    set(CEF_LIBRARY ${CEF_ROOT}/Release)
    set(GLEW_LIBRARY ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/lib/Release/Win32)
endif ()
set(GLEW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/glew/include)
set(GLM_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/glm)
set(GLFW_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw/include)
set(GLFW_LIBRARIES ${CMAKE_CURRENT_SOURCE_DIR}/libs/glfw)
set(JSON_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/libs/json/include)
set(USE_SANDBOX OFF)
find_package(CEF REQUIRED)
find_package(OpenGL REQUIRED)
find_package(glew REQUIRED)
#find_package(glfw REQUIRED)
find_package(glm REQUIRED)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    link_directories(${CEF_ROOT}/Debug/ ${GLEW_LIBRARY})
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    link_directories(${CEF_ROOT}/Release/ ${GLEW_LIBRARY})
else ()
    link_directories(${CEF_ROOT}/Release/ ${GLEW_LIBRARY})
    message("Unknown build type")
endif ()

include_directories(${CEF_ROOT}
        ${GLM_INCLUDE_DIR}
        ${GLEW_INCLUDE_DIR}
        ${GLFW_INCLUDE_DIR}
        )

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

set(USER_SRC
        src/server/user/User.cpp
        src/server/user/User.hh
        src/server/user/AuthSystem.cpp
        src/server/user/AuthSystem.hh
        src/server/user/RegisteredUsers.cpp
        src/server/user/RegisteredUsers.hh
        src/network/socket/SocketMessage.cpp
        src/network/socket/SocketMessage.hh)

##
##  Game sources
##

set(GAME_SRC
        src/server/game/building/ABuilding.cpp
        src/server/game/building/ABuilding.hh
        src/server/game/building/IBuilding.hh
        src/server/game/resource/IResource.hh
        src/server/game/technology/ITechnology.hh
        src/server/game/resource/UpgradeCost.cpp
        src/server/game/resource/UpgradeCost.hh
        src/server/game/building/IronMine.cpp
        src/server/game/building/IronMine.hh
        src/server/game/planet/Planet.cpp src/server/game/planet/Planet.hh src/server/UniqueObject.cpp src/server/UniqueObject.hh)

add_executable(BeyondLightServer ${NETWORK_SERVER_SRC_DIR}/main.cpp ${NETWORK_SERVER_SRC} ${NETWORK_SOCKET_SRC} ${USER_SRC} ${COMMON_SRC} ${GAME_SRC})
add_executable(BeyondLightClient ${NETWORK_CLIENT_SRC_DIR}/main.cpp ${NETWORK_CLIENT_SRC} ${NETWORK_SOCKET_SRC} ${COMMON_SRC} ${CLIENT_SRC})  # todo add WIN32 if debug build
add_executable(${CLIENT_PERF_EXECUTABLE_NAME} ${PERF_TEST_SRC})

target_include_directories(BeyondLightServer PRIVATE ${Boost_INCLUDE_DIRS} ${NETWORK_INCLUDE_DIRS} ${JSON_INCLUDE_DIR})
target_include_directories(BeyondLightClient PRIVATE ${Boost_INCLUDE_DIRS} ${NETWORK_INCLUDE_DIRS} ${JSON_INCLUDE_DIR} libcef_dll_wrapper libcef opengl32 glew32 ${GLFW_LIBRARIES}/glfw3dll.lib)
target_link_libraries(${CLIENT_PERF_EXECUTABLE_NAME} libcef_dll_wrapper libcef opengl32 glew32 ${GLFW_LIBRARIES}/glfw3dll.lib)

IF (UNIX)
    target_link_libraries(BeyondLightServer ${Boost_LIBRARIES} pthread)
    target_link_libraries(BeyondLightClient ${Boost_LIBRARIES} pthread)
ELSE ()

    #include(${CLIENT_PROJECT_DIR}/CMakeLists.txt)

    target_link_libraries(BeyondLightServer ${Boost_LIBRARIES} ws2_32)
    target_link_libraries(BeyondLightClient ${Boost_LIBRARIES} ws2_32 libcef_dll_wrapper libcef opengl32 glew32 ${GLFW_LIBRARIES}/glfw3dll.lib)
ENDIF (UNIX)

##
##  Compile the test environment with Google test, optionnal
##

find_package(GTest)
IF (GTEST_FOUND)
    message("-- Google test has been found, setting up test environment")
    set(UNIT_TEST_SRCS test/unittest.cpp ${NETWORK_SERVER_SRC} ${NETWORK_CLIENT_SRC} ${NETWORK_SOCKET_SRC})
    add_executable(TestSuit ${UNIT_TEST_SRCS} ${COMMON_SRC})

    target_include_directories(TestSuit PRIVATE ${GTEST_INCLUDE_DIRS} ${NETWORK_INCLUDE_DIRS})
    IF (UNIX)
        target_link_libraries(TestSuit ${Boost_LIBRARIES} ${GTEST_BOTH_LIBRARIES} pthread)
    ELSEIF (WIN32)
        target_link_libraries(TestSuit ${Boost_LIBRARIES} ${GTEST_BOTH_LIBRARIES})
    ENDIF (UNIX)
ENDIF (GTEST_FOUND)

##
##  Copy static elements in the target root directory
##

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_custom_command(TARGET BeyondLightClient PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/static/win32/debug
            $<TARGET_FILE_DIR:BeyondLightClient>)
elseif (CMAKE_BUILD_TYPE STREQUAL "Release")
    add_custom_command(TARGET BeyondLightClient PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/static/win32/release
            $<TARGET_FILE_DIR:BeyondLightClient>)
else ()
    add_custom_command(TARGET BeyondLightClient PRE_BUILD
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_CURRENT_SOURCE_DIR}/libs/static/win32/release
            $<TARGET_FILE_DIR:BeyondLightClient>)
endif ()

add_custom_command(TARGET BeyondLightClient PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_CURRENT_SOURCE_DIR}/resources/static/
        $<TARGET_FILE_DIR:BeyondLightClient>)