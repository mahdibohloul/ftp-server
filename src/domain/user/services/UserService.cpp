#include "UserService.hpp"

UserService *UserService::instance = nullptr;

UserService::UserService() {
    this->user_repository = UserRepository::getInstance();
}

UserService *UserService::getInstance() {
    if (instance == nullptr) {
        instance = new UserService();
    }
    return instance;
}

void UserService::insert_users(const std::list<User *> &users) {
    for (auto item: users) {
        this->user_repository->insert(item);
    }
}

User *UserService::find_user(const std::string &username) {
    return user_repository->find_by_username(username);
}
