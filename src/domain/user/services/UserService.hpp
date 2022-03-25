#ifndef FTP_SERVER_USERSERVICE_HPP
#define FTP_SERVER_USERSERVICE_HPP


#include "../repositories/UserRepository.hpp"

//singleton service
class UserService {
public:
    static UserService *getInstance();

    void insert_users(const std::list<User *> &users);

    User *find_user(const std::string &username);

private:
    UserService();

    static UserService *instance;
private:
    UserRepository *user_repository;
};


#endif //FTP_SERVER_USERSERVICE_HPP
