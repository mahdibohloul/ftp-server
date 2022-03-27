#ifndef FTP_SERVER_SERVERCONFIG_HPP
#define FTP_SERVER_SERVERCONFIG_HPP

#include "fstream"
#include "list"
#include "../../domain/user/models/User.hpp"
#include "../FTPServerException.hpp"
#include "../FTPServerErrorCode.hpp"
#include "../json/json.hpp"
#include "../../domain/file/models/GrantedFile.hpp"
#include "iostream"


class ServerConfig {
public:
    explicit ServerConfig(const std::string &config_file_path);

    void read_config_file();

    std::list<User *> get_users();

    std::list<GrantedFile *> get_protected_files();

    int get_command_channel_port() const;

    int get_data_channel_port() const;

private:
    static std::string prepare_file_name(const std::string &filename);

private:
    std::string config_file_path;
    std::list<User *> users;
    std::list<GrantedFile *> protected_files;
    int command_channel_port;
    int data_channel_port;
};


#endif //FTP_SERVER_SERVERCONFIG_HPP
