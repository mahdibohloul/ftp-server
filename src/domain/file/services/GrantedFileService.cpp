//
// Created by mahdi on 27/03/2022.
//

#include "GrantedFileService.hpp"

GrantedFileService *GrantedFileService::instance = nullptr;

GrantedFileService::GrantedFileService() {
    this->granted_file_repository = GrantedFileRepository::getInstance();
}

GrantedFileService *GrantedFileService::getInstance() {
    if (instance == nullptr) {
        instance = new GrantedFileService();
    }
    return instance;
}

void GrantedFileService::insert_files(const std::list<GrantedFile *> &files) {
    for (const auto &item: files) {
        this->granted_file_repository->insert(item);
    }
}

GrantedFile *GrantedFileService::find_by_path(const std::string &path) {
    return this->granted_file_repository->find_by_path(path);
}
