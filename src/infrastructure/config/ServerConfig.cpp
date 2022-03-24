//
// Created by mahdi on 24/03/2022.
//

#include "ServerConfig.hpp"
#include "iostream"


ServerConfig::ServerConfig(const std::string &config_file_path) {
    this->config_file_path = config_file_path;
}

void ServerConfig::read_config_file() {
    std::ifstream config_file(this->config_file_path);
//    if (config_file.is_open()) {
//        throw FTPServerException("Config file not found", ftp_error_code::INTERNAL_ERROR);
//    }
    nlohmann::json json_file;
    config_file >> json_file;
    this->command_channel_port = json_file["commandChannelPort"].get<int>();
    this->data_channel_port = json_file["dataChannelPort"].get<int>();
    for (auto &user: json_file["users"]) {
        auto username = user["user"].get<std::string>();
        auto password = user["password"].get<std::string>();
        bool admin = user["admin"].get<std::string>() == "true";
        double size = std::stod(user["size"].get<std::string>());
        auto new_user = new User(username, password, admin, size);
        this->users.emplace_back(new_user);
    }
    for (const auto &item: json_file["files"]) {
        this->protected_files.push_back(item.get<std::string>());
    }
    config_file.close();
}

std::list<User *> ServerConfig::get_users() {
    return this->users;
}

std::list<std::string> ServerConfig::get_protected_files() {
    return this->protected_files;
}

int ServerConfig::get_command_channel_port() {
    return this->command_channel_port;
}

int ServerConfig::get_data_channel_port() {
    return this->data_channel_port;
}
