//
// Created by mahdi on 24/03/2022.
//

#ifndef FTP_SERVER_USERREPOSITORY_HPP
#define FTP_SERVER_USERREPOSITORY_HPP


#include "../models/User.hpp"
#include "list"
#include "map"
#include "../../../infrastructure/repository/Repository.hpp"

//singleton
class UserRepository : public Repository {
public:
    static UserRepository *getInstance();

    User *find_by_username(const std::string &username);

private:
    UserRepository();

    static UserRepository *instance;
};


#endif //FTP_SERVER_USERREPOSITORY_HPP
