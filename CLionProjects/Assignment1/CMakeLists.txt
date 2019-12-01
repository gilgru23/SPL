cmake_minimum_required(VERSION 3.15)
project(Assignment1)

set(CMAKE_CXX_STANDARD 11)
include_directories(.)

add_executable(Assignment1
        Action.h
        json.hpp
        Main.cpp
        Session.h
        User.h
        Watchable.h Watchable.cpp Movie.cpp Episode.cpp Session.cpp User.cpp Action.cpp)

