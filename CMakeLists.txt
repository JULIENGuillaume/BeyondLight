cmake_minimum_required(VERSION 3.9)
project(BeyondLight)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith \
                                        -Wcast-align -Wswitch-enum -Wconversion -Wunreachable-code \
                                        -Wwrite-strings -fstack-check -pipe -ftrapv --std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -Og")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Ofast -s")

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREAD ON)
find_package(Boost COMPONENTS REQUIRED chrono system regex filesystem date_time)

set(SRC_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(NETWORK_SERVER_SRC_DIR "${SRC_BASE_DIR}/network/server")
set(NETWORK_CLIENT_SRC_DIR "${SRC_BASE_DIR}/network/client")

set(NETWORK_SERVER_SRC ${NETWORK_SERVER_SRC_DIR}/main.cpp)
set(NETWORK_CLIENT_SRC ${NETWORK_CLIENT_SRC_DIR}/main.cpp)

add_executable(BeyondLightServer ${NETWORK_SERVER_SRC})
add_executable(BeyondLightClient ${NETWORK_CLIENT_SRC})

target_include_directories(BeyondLightServer PRIVATE ${BOOST_INCLUDE_DIRS})
target_include_directories(BeyondLightClient PRIVATE ${BOOST_INCLUDE_DIRS})
target_link_libraries(BeyondLightServer ${Boost_LIBRARIES})
target_link_libraries(BeyondLightClient ${Boost_LIBRARIES})

find_package(GTest)
IF (GTEST_FOUND)
    message("Google test has been found, setting up test environment")
    set(UNIT_TEST_SRCS test/unittest.cpp)
    add_executable(TestSuit ${UNIT_TEST_SRCS})

    target_include_directories(TestSuit PRIVATE ${GTEST_INCLUDE_DIRS})
    IF (UNIX)
        target_link_libraries(TestSuit ${GTEST_BOTH_LIBRARIES} pthread)
    ELSEIF (WIN32)
        target_link_libraries(TestSuit ${GTEST_BOTH_LIBRARIES})
    ENDIF (UNIX)
ENDIF (GTEST_FOUND)