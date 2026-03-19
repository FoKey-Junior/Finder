<div align="center">

# Finder

**Finder‑style файловый менеджер для macOS на Qt 6**

[![C++](https://img.shields.io/badge/C++-23-blue.svg)](https://isocpp.org/)
[![Qt](https://img.shields.io/badge/Qt-6-green.svg)](https://www.qt.io/)
[![CMake](https://img.shields.io/badge/CMake-3.26+-orange.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

*Быстрый, аккуратный, удобный — привычные сценарии Finder с чистой архитектурой*

</div>

![Demo](https://github.com/user-attachments/assets/89da4759-9917-4298-94ed-196f6e0023c9)

Современный Finder‑подобный файловый менеджер для macOS на Qt 6
Сфокусирован на скорости навигации, ясной структуре и аккуратном дизайне

## Вдохновение
Проект вдохновлён моим первым проектом [fs который является заменой unix команды ls](https://github.com/FoKey-Junior/fs)

## Возможности
- Sidebar с избранными папками и деревом каталогов
- Просмотр: Icons, List, Columns
- Навигация: Back / Forward / Up, breadcrumbs, history
- Поиск по текущей папке
- Контекстные действия: Open, Rename, Delete, New Folder
- Drag & Drop между папками
- Preview‑панель для изображений и текстовых файлов
- Автоматическое переключение темы по системной (Light/Dark)

## Сборка (macOS)
Требования:
- macOS 13+
- Qt 6 (установлен с официального сайта)
- CMake 3.26+
- Xcode Command Line Tools

Сборка:
```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release
```

Запуск:
```bash
open build/finder.app
```

## Архитектура
- `src/MainWindow.cpp` — UI, навигация, контекстные действия, preview
- `include/MainWindow.h` — интерфейс окна
- `CMakeLists.txt` — сборка под Qt 6 Widgets
