//
// Created by mahdi on 27/03/2022.
//

#ifndef FTP_SERVER_GRANTEDFILEREPOSITORY_HPP
#define FTP_SERVER_GRANTEDFILEREPOSITORY_HPP


#include <list>
#include <map>
#include "../models/GrantedFile.hpp"
#include "../../../infrastructure/repository/Repository.hpp"

class GrantedFileRepository : public Repository {
public:
    static GrantedFileRepository *getInstance();

    GrantedFile *find_by_path(const std::string &path);

private:
    GrantedFileRepository();

    static GrantedFileRepository *instance;
};


#endif //FTP_SERVER_GRANTEDFILEREPOSITORY_HPP
