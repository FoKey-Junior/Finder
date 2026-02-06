#include "../include/FileManager.h"
#include <iostream>

FileManager::FileManager() {
    scan_directory();
}

void FileManager::scan_directory() {
    const fs::path path = fs::current_path();

    if (!fs::exists(path) || fs::is_empty(path)) {
        std::cout << "Текущая директория пуста или не существует\n";
        return;
    }

    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            if (fs::is_empty(entry))
                folder_empty_names_.push_back({entry.path().filename().string()});
            else
                folder_names_.push_back({entry.path().filename().string()});
        } else if (entry.is_regular_file()) {
            file_names_.push_back({
                entry.path().filename().string(),
                entry.file_size()
            });
        }
    }
}
