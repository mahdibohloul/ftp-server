//
// Created by mahdi on 24/03/2022.
//

#ifndef FTP_SERVER_USERREPOSITORY_HPP
#define FTP_SERVER_USERREPOSITORY_HPP


#include "../models/User.hpp"
#include "list"
#include "map"
//#include "../../../infrastructure/store/InMemoryStore.hpp"
//#include "../../../infrastructure/repository/CRUDRepository.hpp"

//singleton
class UserRepository {
public:
    static UserRepository *getInstance();

    User *insert(User &value);

    User *update(User &value);

    void remove(int id);

    std::list<User> get_all();

private:
    UserRepository();

    int get_next_id();

    static UserRepository *instance;
    std::map<int, User> store;
};


#endif //FTP_SERVER_USERREPOSITORY_HPP
