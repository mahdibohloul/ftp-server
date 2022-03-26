//
// Created by mahdi on 25/03/2022.
//

#ifndef FTP_SERVER_DIRECTORY_HPP
#define FTP_SERVER_DIRECTORY_HPP


#include <string>
#include <vector>
#include <unistd.h>

class Directory {
public:
    explicit Directory(const std::string &path, Directory *parent = nullptr);

    static Directory *get_root();

    [[nodiscard]] std::vector<std::string> get_files() const;

    [[nodiscard]] std::vector<Directory> get_directories() const;

    [[nodiscard]] std::string get_path() const;

    [[nodiscard]] Directory *get_parent() const;

private:
    std::string path;
    std::vector<std::string> files;
    std::vector<Directory> directories;
    Directory *parent;
};


#endif //FTP_SERVER_DIRECTORY_HPP
