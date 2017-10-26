cmake_minimum_required(VERSION 3.9)
project(BeyondLight)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -W -Wall -Wextra -Wfloat-equal -Wshadow -Wpointer-arith \
                                        -Wcast-align -Wswitch-enum -Wconversion -Wunreachable-code \
                                        -Wwrite-strings -fstack-check -pipe -ftrapv --std=c++11")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g3 -Og")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3 -Ofast -s")

set(NETWORK_SERVER_SRC)
set(UNIT_TEST_SRCS test/unittest.cpp)

find_package(GTest REQUIRED)

set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREAD ON)  # enable multithreading
find_package (Boost COMPONENTS REQUIRED chrono system)

add_executable(BeyondLight main.cpp)
add_executable(TestSuit ${UNIT_TEST_SRCS})

target_include_directories(TestSuit PRIVATE ${GTEST_INCLUDE_DIRS})
target_link_libraries(TestSuit ${GTEST_BOTH_LIBRARIES} pthread)
