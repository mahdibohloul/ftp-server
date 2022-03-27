//
// Created by mahdi on 24/03/2022.
//

#include "User.hpp"


User::User(std::string &username, std::string &password, double download_capacity, Directory *current_directory,
           std::vector<Role> roles) {
    this->username = username;
    this->password = password;
    this->roles = std::move(roles);
    this->download_capacity = download_capacity;
    this->current_directory = current_directory == nullptr ? Directory::get_root() : current_directory;
}


bool User::is_admin() const {
    return std::any_of(this->roles.begin(), this->roles.end(), [](const Role &role) {
        return role == Role::ADMIN;
    });
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

std::vector<Role> User::get_roles() const {
    return this->roles;
}

void User::decrease_download_capacity(double amount) {
    this->download_capacity -= amount;
}
