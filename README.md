<div align="center">

<img src="https://github.com/FoKey-Junior/Finder/blob/main/assets/demonstration.png?raw=true" alt="Finder" width="450" style="border-radius: 30px; box-shadow: 0 25px 50px rgba(0, 0, 0, 0.3); margin-bottom: 35px; border: 5px solid rgba(0, 0, 0, 0.1); display: block; margin-left: auto; margin-right: auto;"/>

# 🗂 Finder

**Finder‑style файловый менеджер для macOS на Qt 6**

[![C++](https://img.shields.io/badge/C++-23-blue.svg)](https://isocpp.org/)
[![Qt](https://img.shields.io/badge/Qt-6-green.svg)](https://www.qt.io/)
[![CMake](https://img.shields.io/badge/CMake-3.26+-orange.svg)](https://cmake.org/)
[![License](https://img.shields.io/badge/License-MIT-yellow.svg)](LICENSE)

*Быстрый, аккуратный, удобный — привычные сценарии Finder с чистой архитектурой*

<div style="margin-top: 20px; font-style: italic; color: #555; font-size: 0.95em;">
✨ Навигация, просмотр и управление файлами в стиле macOS Finder с чистым Qt 6 интерфейсом ✨ <br><br>

> ⚠️ Проект в активной разработке  
> Функционал может меняться, но уже демонстрирует базовые сценарии работы Finder
</div>
</div>

## 📋 Содержание

- [О проекте](#-о-проекте)
- [Возможности](#-возможности)
- [Архитектура](#-архитектура)
- [Технологии](#-технологии)
- [Сборка](#-сборка-macos)
- [Использование](#-использование)
- [Структура проекта](#-структура-проекта)
- [Вклад в проект](#-вклад-в-проект)
- [Лицензия](#-лицензия)

---

## 🎯 О проекте

**Finder** — современный файловый менеджер для macOS с интерфейсом в стиле Finder.  
Сфокусирован на скорости навигации, ясной структуре и аккуратном дизайне.

### Вдохновение

Проект вдохновлён моим первым проектом [fs — замена unix команды ls](https://github.com/FoKey-Junior/fs).

---

## ✨ Возможности

- **Sidebar** с избранными папками и деревом каталогов  
- **Просмотр файлов**: Icons, List, Columns  
- **Навигация**: Back / Forward / Up, breadcrumbs, history  
- **Поиск** по текущей папке  
- **Контекстные действия**: Open, Rename, Delete, New Folder  
- **Drag & Drop** между папками  
- **Preview‑панель** для изображений и текстовых файлов  
- **Автоматическое переключение темы** по системной (Light/Dark)

---

## 🏗️ Архитектура

┌───────────────────────────────────────────────┐
│ Finder                                        |
├───────────────────────────────────────────────┤
│ src/MainWindow.cpp — UI, навигация,           │ 
│ контекстные действия, preview                 │
│ include/MainWindow.h — интерфейс окна         │
│ CMakeLists.txt — сборка под Qt 6              │
└───────────────────────────────────────────────┘


---

## 🛠️ Технологии

- **C++23** — современный стандарт  
- **Qt 6** — UI и виджеты  
- **CMake 3.26+** — система сборки  
- **macOS 13+** — целевая платформа  

---

## 📦 Сборка (macOS)

### Требования

- macOS 13+  
- Qt 6 (официальный сайт)  
- CMake 3.26+  
- Xcode Command Line Tools  

### Сборка

```bash
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --config Release

🚀 Использование

Навигация по файловой системе
Открытие, создание, переименование и удаление файлов/папок
Drag & Drop файлов между папками
Просмотр изображений и текстовых файлов через Preview‑панель
Поиск по текущей директории

📂 Структура проекта
Finder/
├── include/               # Заголовочные файлы
│   └── MainWindow.h       # Интерфейс главного окна
├── src/                   # Исходный код
│   └── MainWindow.cpp     # UI, логика навигации и preview
├── assets/                # Скриншоты, иконки
├── CMakeLists.txt         # Сборка Qt 6 Widgets
└── README.md              # Документация

🤝 Вклад в проект
Мы приветствуем вклад в развитие проекта! Пожалуйста:
1. Форкните репозиторий
2. Создайте ветку для новой функции (git checkout -b feature/amazing-feature)
3. Закоммитьте изменения (git commit -m 'Add amazing feature')
4. Запушьте в ветку (git push origin feature/amazing-feature)
5. Откройте Pull Request

<div align="center">

Сделано с ❤️ для macOS пользователей и разработчиков Qt

⭐ Поставить звезду

🐛 Сообщить об ошибке

</div> ```
