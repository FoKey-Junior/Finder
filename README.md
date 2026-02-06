# Finder

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

## Скриншоты
Добавь сюда изображения интерфейса после первого релиза:
- `assets/preview-light.png`
- `assets/preview-dark.png`

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

## Лицензия
MIT
