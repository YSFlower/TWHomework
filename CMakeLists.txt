cmake_minimum_required(VERSION 3.6)
project(TWHomework)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
    global.cpp
    global.h
    ground_order.cpp
    ground_order.h
    main.cpp
    user_order.cpp
    user_order.h test.h)

add_executable(TWHomework ${SOURCE_FILES})