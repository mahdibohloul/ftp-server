//
// Created by mahdi on 27/03/2022.
//

#ifndef FTP_SERVER_GRANTEDFILESERVICE_HPP
#define FTP_SERVER_GRANTEDFILESERVICE_HPP


#include "../repositories/GrantedFileRepository.hpp"

//singleton
class GrantedFileService {
public:
    static GrantedFileService *getInstance();

    void insert_files(const std::list<GrantedFile *> &files);

    GrantedFile* find_by_path(const std::string &path);


private:
    GrantedFileService();

    static GrantedFileService *instance;

    GrantedFileRepository *granted_file_repository;
};


#endif //FTP_SERVER_GRANTEDFILESERVICE_HPP
