//
// Created by mahdi on 27/03/2022.
//

#include "GrantedFileRepository.hpp"

GrantedFileRepository *GrantedFileRepository::instance = nullptr;

GrantedFileRepository *GrantedFileRepository::getInstance() {
    if (instance == nullptr) {
        instance = new GrantedFileRepository();
    }
    return instance;
}

GrantedFile *GrantedFileRepository::find_by_path(const std::string &path) {
    for (const auto &item: store) {
        auto file = dynamic_cast<GrantedFile *>(item.second);
        if (file->get_path() == path) {
            return file;
        }
    }
    return nullptr;
}

GrantedFileRepository::GrantedFileRepository() = default;
