#ifndef FTP_SERVER_SERVER_HPP
#define FTP_SERVER_SERVER_HPP

#include <string>
#include "../config/ServerConfig.hpp"
#include "../../domain/user/services/UserService.hpp"
#include "../socket/WebSocket.hpp"
#include "../../domain/file/services/GrantedFileService.hpp"


class Server {
public:
    static Server *getInstance();

    void bootstrap(const std::string &config_file_path);

    WebSocket *get_command_channel();

    WebSocket *get_data_channel();

    void start();

private:
    Server();

    static Server *instance;
    WebSocket *data_socket;
    WebSocket *command_socket;
    UserService *user_service;
    GrantedFileService *file_service;
    Logger *logger;
};


#endif
