//
// Created by mahdi on 25/03/2022.
//

#include "Directory.hpp"


Directory::Directory(const std::string &path, Directory *parent) {
    this->path = path;
    this->parent = parent;
}

std::vector<std::string> Directory::get_files() const {
    return files;
}

std::vector<Directory> Directory::get_directories() const {
    return directories;
}

std::string Directory::get_path() const {
    return path;
}

Directory *Directory::get_parent() const {
    return parent;
}

Directory *Directory::get_root() {
    return new Directory(get_current_dir_name(), nullptr);
}

bool Directory::is_root() const {
    return parent == nullptr;
}
