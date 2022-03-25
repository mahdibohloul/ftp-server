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

User *UserRepository::insert(User &value) {
    value.set_id(get_next_id());
    store.insert(pair<int, User>(value.get_id(), value));
    return &value;
}

User *UserRepository::update(User &value) {
    store.insert(pair<int, User>(value.get_id(), value));
    return &value;
}

void UserRepository::remove(int id) {
    this->store.erase(id);
}

int UserRepository::get_next_id() {
    auto users = this->get_all();
    users.sort([](const User &a, const User &b) {
        return a.get_id() < b.get_id();
    });
    if (users.empty()) {
        return 1;
    }
    return users.back().get_id() + 1;
}

std::list<User> UserRepository::get_all() {
    list<User> users;
    for (auto &user: store) {
        users.push_back(user.second);
    }
    return users;
}

User *UserRepository::find_by_username(const string &username) {
    for (auto &user: store) {
        if (user.second.get_username() == username) {
            return &user.second;
        }
    }
    return nullptr;
}
