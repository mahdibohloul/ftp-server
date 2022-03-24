#ifndef FTP_SERVER_SERVERCONFIG_HPP
#define FTP_SERVER_SERVERCONFIG_HPP

#include "fstream"
#include "list"
#include "../../domain/user/models/User.hpp"
#include "../FTPServerException.hpp"
#include "../FTPServerErrorCode.hpp"
#include "../json/json.hpp"


class ServerConfig {
public:
    explicit ServerConfig(const std::string& config_file_path);

    void read_config_file();

    std::list<User *> get_users();

    std::list<std::string> get_protected_files();

    int get_command_channel_port();
    int get_data_channel_port();

private:
    std::string config_file_path;
    std::list<User *> users;
    std::list<std::string> protected_files;
    int command_channel_port;
    int data_channel_port;
};


#endif //FTP_SERVER_SERVERCONFIG_HPP
