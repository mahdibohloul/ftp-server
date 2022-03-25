//
// Created by mahdi on 25/03/2022.
//

#ifndef FTP_SERVER_HANDLER_HPP
#define FTP_SERVER_HANDLER_HPP


#include "../../infrastructure/workContext/WorkContext.hpp"
#include "vector"
#include "../../infrastructure/socket/WebSocket.hpp"

class Handler {
public:
    Handler() = default;

    ~Handler() = default;

    virtual void handle(WebSocket *_command_channel, WebSocket *_data_channel, WorkContext *_work_context,
                        std::vector<std::string> _cmd) = 0;

    static void send_error(int client_fd, const std::string &_error_message, Logger *logger);

    static void send_message(int client_fd, std::string _message, Logger *logger);

    static void send_data(int client_fd, std::string _data, Logger *logger);
};


#endif //FTP_SERVER_HANDLER_HPP
