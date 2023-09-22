cmake_minimum_required(VERSION 3.26 FATAL_ERROR)

include(FetchContent)

set(PROJECT_VERSION_FILE ${CMAKE_SOURCE_DIR}/include/version.h)

project(journy2 LANGUAGES CXX VERSION 0.1.0)
file(WRITE ${PROJECT_VERSION_FILE} "#pragma once\n#ifndef JOURNY_VERSION\n#define JOURNY_VERSION \"${CMAKE_PROJECT_VERSION}\"\n#endif")

set(CMAKE_CXX_STANDARD 20)

find_package(Vulkan REQUIRED)
find_package(glfw3 CONFIG REQUIRED)
find_package(imgui CONFIG REQUIRED)
find_package(unofficial-sqlite3 REQUIRED)
find_package(antlr4-runtime CONFIG REQUIRED)

add_executable(journy2
    source/main.cpp

    include/journal/entry.h source/journal/entry.cpp
    include/journal/databasemanager.h source/journal/databasemanager.cpp

    source/Application.cpp include/Application.h
    include/markdown/markdowntovector.h source/markdown/markdowntovector.cpp

    # Ui
    include/ui/markdowneditor.h source/ui/markdowneditor.cpp
    include/ui/fonthelpers.h source/ui/fonthelpers.cpp
    include/ui/datepicker/datepicker.h source/ui/datepicker/datepicker.cpp
    source/ui/themes.cpp include/ui/themes.h
    include/ui/font/iconsmaterialdesign.h

    # Markdown parser
    include/markdown/parser/MarkdownBaseListener.h
    include/markdown/parser/MarkdownBaseVisitor.h
    include/markdown/parser/MarkdownLexer.h
    include/markdown/parser/MarkdownListener.h
    include/markdown/parser/MarkdownParser.h
    include/markdown/parser/MarkdownVisitor.h

    source/markdown/generated/MarkdownBaseListener.cpp
    source/markdown/generated/MarkdownBaseVisitor.cpp
    source/markdown/generated/MarkdownLexer.cpp
    source/markdown/generated/MarkdownListener.cpp
    source/markdown/generated/MarkdownParser.cpp
    source/markdown/generated/MarkdownVisitor.cpp
    include/markdown/backend/html_backend.h source/markdown/backend/html_backend.cpp
    include/markdown/Marky.h source/markdown/Marky.cpp
        include/applicationstrings.h
)

target_include_directories(journy2
        PRIVATE
        ${CMAKE_SOURCE_DIR}/include

        ${ANTLR4_INCLUDE_DIR}
)

target_link_libraries(journy2
        PRIVATE
        imgui::imgui
        glfw

        PUBLIC
        unofficial::sqlite3::sqlite3
        antlr4_shared
)

FILE(COPY resources DESTINATION "${CMAKE_BINARY_DIR}/")


# Useful for debugging
#get_cmake_property(_variableNames VARIABLES)
#list (SORT _variableNames)
#foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
#endforeach()
