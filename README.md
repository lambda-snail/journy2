# journy2
 A simple application to handle daily journal entries. This is the second incarnation, which is why the name contains a '2'.

## Implemented Features

- Create, update and view markdown documents with a rudimentary set of features.
- Live update of markdown preview as you type
- The database will be created and initialized automatically if not found in the user's home directory.
- Saving to the database
- Filter entries based on a calendar control

## Planned Features

- Support for more markdown syntax features
- Full text search among entries
- Syntax highlighting (maybe)

## Feature Wishlist

- Todo items managed in a kanban board

# Building

The project currently build on Linux (tested on Fedora 38 using clang) and Windows (currently only build using MingW).

Dependencies are all managed using vcpkg or CMake.
- wxWidgets and the markdown processor are downloaded automatically using fetch content
- sqlite3 is downloaded using vcpkg

## Dependencies

- wxWidgets
- sqlite3
- marky

### marky

[Marky](https://github.com/lambda-snail/marky) is a bare-bones markdown processor that parses markdown and produces html. It has been created for journy2 but is deployed as a separate project to facilitate re-use in other projects.

# Credits

This software includes resources or code, or parts of code from the following projects. All credits for these works go to the original authors.

- [IconFontCppHeaders](https://github.com/juliettef/IconFontCppHeaders/tree/main)
- [Google Material Icons](https://github.com/google/material-design-icons)