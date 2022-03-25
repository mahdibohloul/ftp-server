//
// Created by mahdi on 25/03/2022.
//

#ifndef FTP_SERVER_FILEHANDLER_HPP
#define FTP_SERVER_FILEHANDLER_HPP


#include "Handler.hpp"

class FileHandler : public Handler {
    void handle(WebSocket *_command_channel, WebSocket *_data_channel, WorkContext *_work_context,
                std::vector<std::string> _cmd) override;

public:
    FileHandler();

private:
    void pwd();

private:
    std::vector<std::string> cmd;
    Logger *logger;
    WorkContext *work_context;
};


#endif //FTP_SERVER_FILEHANDLER_HPP
