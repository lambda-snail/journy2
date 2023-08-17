cmake_minimum_required(VERSION 3.26 FATAL_ERROR)



project(journy2 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

set(wxWidgets_USE_STATIC 1)
set(wxBUILD_SHARED OFF)


include(FetchContent)
FetchContent_Declare(
        wxWidgets
        GIT_REPOSITORY "https://github.com/wxWidgets/wxWidgets.git"
        GIT_TAG v3.2.2.1
)

FetchContent_GetProperties(wxwidgets)
if(NOT wxwidgets_POPULATED)
    FetchContent_Populate(wxwidgets)
    add_subdirectory(${wxwidgets_SOURCE_DIR} ${wxwidgets_BUILD_DIR})
endif()

find_package(unofficial-sqlite3 REQUIRED)

add_executable(journy2 WIN32
    source/main.cpp
    source/ui/journymainframe.cpp include/ui/journymainframe.h
    source/journal/entry.cpp include/journal/entry.h
)

target_include_directories(journy2
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${wxWidgets_SOURCE_DIR}/include)

target_link_libraries(journy2
        PRIVATE
        wx::base
        wx::core
        unofficial::sqlite3::sqlite3
)
