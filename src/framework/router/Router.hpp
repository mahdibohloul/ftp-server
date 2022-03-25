#ifndef FTP_SERVER_ROUTER_HPP
#define FTP_SERVER_ROUTER_HPP

#include "vector"
#include <cstring>
#include "../../infrastructure/FTPServerException.hpp"
#include "../handler/AuthenticationHandler.hpp"
#include "../../infrastructure/server/Server.hpp"
#include "../handler/FileHandler.hpp"

class Router {
public:
    Router(int _client_fd, char *_cmd);

    void execute();

private:
    void set_up_handlers();

    static std::vector<std::string> split_cmd(std::string cmd);

private:
    typedef std::map<std::string, Handler *> router_map;


    int client_fd;
    char *cmd;
    WorkContext *work_context;
    Logger *logger;
    router_map handlers;
    WebSocket *command_channel;
    WebSocket *data_channel;
};


#endif //FTP_SERVER_ROUTER_HPP
