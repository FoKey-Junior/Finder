#ifndef FS_DISPLAY_MANAGER_H
#define FS_DISPLAY_MANAGER_H

#include "FileManager.h"
#include <unordered_map>

class DisplayManager {
public:
    explicit DisplayManager(const FileManager& manager);

    void show_folders() const;
    void show_files() const;

private:
    const FileManager& manager_;

    const std::unordered_map<std::string, std::string> extension_emoji_{
            {"mp4","🎬"},{"mov","🎬"},{"mkv","🎬"},
            {"mp3","🎵"},{"wav","🎵"},{"flac","🎵"},
            {"jpg","🖼️"},{"jpeg","🖼️"},{"png","🖼️"},
            {"txt","📄"},{"md","📝"},{"json","🗃️"},
            {"zip","🗜️"},{"html","🌐"},{"cpp","💻"},{"py","🐍"}
    };
};

#endif
