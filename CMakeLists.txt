#cmake_minimum_required(VERSION 3.26)
#project(imgui_test)
#
#set(CMAKE_CXX_STANDARD 20)
#
#find_package(Vulkan REQUIRED)
#find_package(glfw3 CONFIG REQUIRED)
#find_package(imgui CONFIG REQUIRED)
#
#add_executable(imgui_test
#        source/main.cpp
#        include/ui/themes.h
#        include/config.h)
#
#target_include_directories(imgui_test
#        PRIVATE
#        ${CMAKE_SOURCE_DIR}/include
#)
#
#target_link_libraries(imgui_test PRIVATE imgui::imgui glfw Vulkan::Vulkan)

cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

set(PROJECT_VERSION_FILE ${CMAKE_SOURCE_DIR}/include/version.h)

project(journy2 LANGUAGES CXX VERSION 0.1.0)
file(WRITE ${PROJECT_VERSION_FILE} "#pragma once\n#ifndef JOURNY_VERSION\n#define JOURNY_VERSION \"${CMAKE_PROJECT_VERSION}\"\n#endif")

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(unofficial-sqlite3 REQUIRED)

#include(CMakeDependencies.txt)

add_executable(journy2
    source/main.cpp
    include/ui/themes.h

    include/journal/entry.h source/journal/entry.cpp
    include/journal/databasemanager.h source/journal/databasemanager.cpp

    source/Application.cpp include/Application.h
)

target_include_directories(journy2
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include

        ${marky_ANTLR_INCLUDE_DIRS}
        ${marky_SOURCE_DIR}/include
)

target_link_libraries(journy2
        PRIVATE
        imgui::imgui
        glfw

        unofficial::sqlite3::sqlite3
        #marky
)
