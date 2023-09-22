# journy2
 A simple application to handle daily journal entries. This is the second incarnation, which is why the name contains a '2'.

This is the experimental branch that contains a re-implementation of the wxWidgets application using ImGui.

## Implemented Features

- Create, update and view markdown documents with a rudimentary set of features.
- Live update of markdown preview as you type
- Saving to the database

## Planned Features

- Ability to switch rendering backend to opengl to support older hardware
- Support for more markdown syntax features
- Filter entries based on a calendar control
- Full text search among entries
- Syntax highlighting (maybe)
- The database will be created and initialized automatically if not found in the user's home directory.
- Build on Linux
- Support more compilers

## Feature Wishlist

- Todo items managed in a kanban board

# Building

The project in the experimental branch is only verified to build on Windows using MSVC. Linux support will come soon.

Dependencies are all managed using vcpkg or CMake.

- sqlite3 and ImGui is downloaded using vcpkg

## Dependencies

- ImGui
- Vulkan
- sqlite3
- marky

### marky

[Marky](https://github.com/lambda-snail/marky) has been incorporated into the experimental branch.

# Credits

This software additionally includes resources or code, or parts of code from the following projects. All credits for these works go to the original authors.

- [IconFontCppHeaders](https://github.com/juliettef/IconFontCppHeaders/tree/main)
- [Google Material Icons](https://github.com/google/material-design-icons)
- Google fonts (Roboto, various)