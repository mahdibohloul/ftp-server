#ifndef FTP_SERVER_SERVER_HPP
#define FTP_SERVER_SERVER_HPP

#include <string>
#include "../config/ServerConfig.hpp"
#include "data/DataSocket.hpp"
#include "command/CommandSocket.hpp"
#include "../../domain/user/services/UserService.hpp"


class Server {
public:
    static Server *getInstance();

    void bootstrap(const std::string &config_file_path);

    void start();

private:
    Server();

    static Server *instance;
    DataSocket *data_socket;
    CommandSocket *command_socket;
    UserService *user_service;
    Logger *logger;
};


#endif
