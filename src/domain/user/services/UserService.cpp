#include "UserService.hpp"

UserService *UserService::instance = nullptr;

UserService::UserService() {
    this->userRepository = UserRepository::getInstance();
}

UserService *UserService::getInstance() {
    if (instance == nullptr) {
        instance = new UserService();
    }
    return instance;
}

void UserService::insert_users(std::list<User *> users) {
    for (auto item: users) {
        this->userRepository->insert(*item);
    }
}
