//
// Created by mahdi on 24/03/2022.
//

#include "UserRepository.hpp"

using namespace std;

UserRepository *UserRepository::instance = nullptr;

UserRepository *UserRepository::getInstance() {
    if (instance == nullptr) {
        instance = new UserRepository();
    }
    return instance;
}

UserRepository::UserRepository() {
    this->store.clear();
}


User *UserRepository::find_by_username(const string &username) {
    for (auto &value: store) {
        auto user = dynamic_cast<User *>(value.second);
        if (user->get_username() == username) {
            return user;
        }
    }
    return nullptr;
}
