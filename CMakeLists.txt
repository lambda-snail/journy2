cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

set(PROJECT_VERSION_FILE ${CMAKE_SOURCE_DIR}/include/version.h)

project(journy2 LANGUAGES CXX VERSION 0.1.0)
file(WRITE ${PROJECT_VERSION_FILE} "#pragma once\n#ifndef JOURNY_VERSION\n#define JOURNY_VERSION \"${CMAKE_PROJECT_VERSION}\"\n#endif")

set(CMAKE_CXX_STANDARD 20 FORCE)

include(CMakeDependencies.txt)
find_package(unofficial-sqlite3 REQUIRED)

if(WIN32)
    set(wxUSE_RC_MANIFEST 1)
    set(MAYBE_WIN_MANIFEST ${CMAKE_SOURCE_DIR}/resources/win_manifest.rc)
endif()

add_executable(journy2
    source/main.cpp
    source/ui/journymainframe.cpp include/ui/journymainframe.h
    source/journal/entry.cpp include/journal/entry.h
    source/journal/databasemanager.cpp include/journal/databasemanager.h

    source/config_strings.cpp include/config_strings.h

    ${PROJECT_VERSION_FILE}
    include/ui/icons.h
    ${MAYBE_WIN_MANIFEST}
)

target_include_directories(journy2
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include
        ${wxWidgets_SOURCE_DIR}/include

        ${marky_ANTLR_INCLUDE_DIRS}
        ${marky_SOURCE_DIR}/include
)

if(LINUX)
    set(LINUX_LINK_LIBS X11)
endif()

target_link_libraries(journy2
        PRIVATE
        wx::base
        wx::core
        wx::webview # https://forums.wxwidgets.org/viewtopic.php?t=43828
        ${LINUX_LINK_LIBS}
        unofficial::sqlite3::sqlite3
        marky
)
