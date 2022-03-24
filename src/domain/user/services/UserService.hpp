#ifndef FTP_SERVER_USERSERVICE_HPP
#define FTP_SERVER_USERSERVICE_HPP


#include "../repositories/UserRepository.hpp"

//singleton service
class UserService {
public:
    static UserService *getInstance();

    void insert_users(std::list<User*> users);

private:
    UserService();

    static UserService *instance;
private:
    UserRepository *userRepository;
};


#endif //FTP_SERVER_USERSERVICE_HPP
