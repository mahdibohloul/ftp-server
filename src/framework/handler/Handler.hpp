//
// Created by mahdi on 25/03/2022.
//

#ifndef FTP_SERVER_HANDLER_HPP
#define FTP_SERVER_HANDLER_HPP


#include "../../infrastructure/workContext/WorkContext.hpp"
#include "../../infrastructure/FTPServerErrorCode.hpp"
#include "vector"
#include "../../infrastructure/socket/WebSocket.hpp"

class Handler {
public:
    Handler() = default;

    ~Handler() = default;

    virtual void handle(WebSocket *_command_channel, WebSocket *_data_channel, WorkContext *_work_context,
                        std::vector<std::string> _cmd) = 0;

    static void
    send_error(int client_fd, const std::string &_error_message, Logger *logger, const std::string& username = "unknown");

    static void send_message(int client_fd, std::string _message, Logger *logger, const std::string& username = "unknown");

    static void send_data(int client_fd, std::string _data, Logger *logger, const std::string& username = "unknown");

    static bool
    is_valid_command(const std::vector<std::string> &cmd, int minimum_length, int maximum_length,
                     Logger *logger, int client_fd, const std::string& username = "unknown");

    static bool is_user_logged_in(WorkContext *work_context, Logger *logger, int client_fd);

};


#endif //FTP_SERVER_HANDLER_HPP
