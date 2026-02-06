<div align="center">

<img src="https://github.com/user-attachments/assets/ff6e45de-9474-43bb-91bd-4621bd649b4c" alt="Finder Demo" width="700" style="border-radius: 24px; box-shadow: 0 25px 50px rgba(0, 0, 0, 0.25); margin-bottom: 24px; border: 1px solid rgba(0, 0, 0, 0.08); display: block; margin-left: auto; margin-right: auto;"/>

# Finder

**Finder‑style файловый менеджер для macOS на Qt 6**

[![C++](https://img.shields.io/badge/C++-14-blue.svg)](https://isocpp.org/)
[![Qt](https://img.shields.io/badge/Qt-6-green.svg)](https://www.qt.io/)
[![CMake](https://img.shields.io/badge/CMake-3.26+-orange.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

*Быстрый, аккуратный, удобный — привычные сценарии Finder с чистой архитектурой.*

</div>

![Demo](https://github.com/FoKey-Junior/Finder/blob/main/assets/demonstration.png?raw=true)

Современный Finder‑подобный файловый менеджер для macOS на Qt 6
Сфокусирован на скорости навигации, ясной структуре и аккуратном дизайне

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

## Roadmap
- Quick Look‑подобный превью для PDF/Video
- Горячие клавиши в стиле Finder (Cmd+Del, Cmd+N, Cmd+Up)
- Сохранение состояния окна и последней директории
- Пакет `.dmg` для дистрибуции

