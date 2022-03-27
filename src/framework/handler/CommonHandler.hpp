//
// Created by mahdi on 27/03/2022.
//

#ifndef FTP_SERVER_COMMONHANDLER_HPP
#define FTP_SERVER_COMMONHANDLER_HPP


#include "Handler.hpp"
#include <sstream>

#define HELP_COMMAND "help"

class CommonHandler : public Handler {
    void handle(WebSocket *_command_channel, WebSocket *_data_channel, WorkContext *_work_context,
                std::vector<std::string> _cmd) override;

public:
    CommonHandler();

private:
    void help();

private:
    WorkContext *work_context;
    std::vector<std::string> cmd;
    Logger *logger;
};


#endif //FTP_SERVER_COMMONHANDLER_HPP
