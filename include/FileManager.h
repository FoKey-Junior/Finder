#ifndef FS_FILE_MANAGER_H
#define FS_FILE_MANAGER_H

#include <filesystem>
#include <string>
#include <vector>

namespace fs = std::filesystem;

struct FolderInfo {
    std::string name;
};

struct FileInfo {
    std::string name;
    std::uintmax_t size{};
};

class FileManager {
    std::vector<FolderInfo> folder_names_;
    std::vector<FolderInfo> folder_empty_names_;
    std::vector<FileInfo>   file_names_;
    void scan_directory();

public:
    [[nodiscard]] const std::vector<FolderInfo>& folders() const noexcept { return folder_names_; }
    [[nodiscard]] const std::vector<FolderInfo>& empty_folders() const noexcept { return folder_empty_names_; }
    [[nodiscard]] const std::vector<FileInfo>& files() const noexcept { return file_names_; }
    FileManager();
};

#endif
