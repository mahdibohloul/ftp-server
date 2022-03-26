//
// Created by mahdi on 24/03/2022.
//

#include "User.hpp"

User::User(std::string &username, std::string &password, bool admin, double download_capacity,
           Directory *current_directory) {
    this->username = username;
    this->password = password;
    this->admin = admin;
    this->download_capacity = download_capacity;
    this->current_directory = current_directory == nullptr ? Directory::get_root() : current_directory;
}

void User::set_id(int _id) {
    this->id = _id;
}

bool User::is_admin() const {
    return this->admin;
}

int User::get_id() const {
    return this->id;
}

std::string User::get_username() const {
    return this->username;
}

std::string User::get_password() const {
    return this->password;
}

double User::get_download_capacity() const {
    return this->download_capacity;
}

Directory *User::get_current_directory() const {
    return this->current_directory;
}

void User::set_current_directory(Directory *_current_directory) {
    this->current_directory = _current_directory;
}
