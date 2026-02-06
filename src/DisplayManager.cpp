#include "../include/DisplayManager.h"
#include <iostream>
#include <iomanip>

DisplayManager::DisplayManager(const FileManager& manager)
    : manager_(manager) {}

void DisplayManager::show_folders() const {
    for (const auto& folder : manager_.folders()) {
        std::cout << "📁 " << std::setw(25) << std::left << folder.name << '\n';
    }

    for (const auto& folder : manager_.empty_folders()) {
        std::cout << "📂 " << std::setw(25) << std::left << folder.name << '\n';
    }
}

void DisplayManager::show_files() const {
    constexpr std::uintmax_t KB = 1024;
    constexpr std::uintmax_t MB = KB * 1024;
    constexpr std::uintmax_t GB = MB * 1024;

    for (const auto& file : manager_.files()) {
        std::string ext = fs::path(file.name).extension().string();
        if (!ext.empty() && ext.front() == '.')
            ext.erase(0, 1);

        const auto it = extension_emoji_.find(ext);
        const std::string& emoji = (it != extension_emoji_.end()) ? it->second : "📄";

        std::cout << emoji << " " << std::setw(25) << std::left << file.name;

        if (file.size >= GB)
            std::cout << file.size / GB << " GB\n";
        else if (file.size >= MB)
            std::cout << file.size / MB << " MB\n";
        else if (file.size >= KB)
            std::cout << file.size / KB << " KB\n";
        else
            std::cout << file.size << " B\n";
    }
}
