<div align="center">

# Finder

**A Finder-style file manager for macOS built with Qt 6**

[![C++](https://img.shields.io/badge/C++-23-blue.svg)](https://isocpp.org/)
[![Qt](https://img.shields.io/badge/Qt-6-green.svg)](https://www.qt.io/)
[![CMake](https://img.shields.io/badge/CMake-3.26+-orange.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

*Fast, clean, and intuitive—familiar Finder workflows powered by a clean architecture*

</div>

![Demo](https://github.com/user-attachments/assets/89da4759-9917-4298-94ed-196f6e0023c9)

A modern, Finder-like file manager for macOS built with Qt 6. It is designed around fast navigation, a clear structure, and a clean, native-feeling layout.

## Inspiration
This project is inspired by my very first project, [fs, which serves as a replacement for the Unix ls command](https://github.com/FoKey-Junior/fs).

## Features
- Sidebar featuring favorite folders and a directory tree
- Multiple view modes: Icons, List, Columns
- Fluid navigation: Back / Forward / Up, breadcrumbs, and history tracking
- In-folder search functionality
- Contextual actions: Open, Rename, Delete, and New Folder
- Drag & Drop support between directories
- Preview panel for images and text files
- Automatic theme switching matching the system settings (Light/Dark)

## Build Instructions (macOS)

### Prerequisites
- macOS 13+
- Qt 6 (installed from the official website)
- CMake 3.26+
- Xcode Command Line Tools

### Building
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

### Running the Application
```bash
open build/finder.app
```

## Architecture
- `src/MainWindow.cpp` — UI implementation, navigation, contextual actions, and preview panel logic
- `include/MainWindow.h` — Main window interface and declarations
- `CMakeLists.txt` — Build configuration using Qt 6 Widgets
