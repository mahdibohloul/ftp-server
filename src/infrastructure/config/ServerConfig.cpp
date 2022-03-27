//
// Created by mahdi on 24/03/2022.
//

#include "ServerConfig.hpp"


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
        std::vector<Role> roles = {Role::USER};
        if (admin) {
            roles.push_back(Role::ADMIN);
        }
        auto new_user = new User(username, password, size, nullptr, roles);
        this->users.emplace_back(new_user);
    }
    for (const auto &item: json_file["files"]) {
        auto filename = prepare_file_name(item.get<std::string>());
        auto file = new GrantedFile(filename, {Role::ADMIN});
        this->protected_files.push_back(file);
    }
    config_file.close();
}

std::string ServerConfig::prepare_file_name(const std::string &filename) {
    std::string base_dir = get_current_dir_name();
    if (filename[0] != '/') {
        base_dir += "/";
    }
    return base_dir + filename;
}

std::list<User *> ServerConfig::get_users() {
    return this->users;
}

std::list<GrantedFile *> ServerConfig::get_protected_files() {
    return this->protected_files;
}

int ServerConfig::get_command_channel_port() const {
    return this->command_channel_port;
}

int ServerConfig::get_data_channel_port() const {
    return this->data_channel_port;
}
