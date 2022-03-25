//
// Created by mahdi on 25/03/2022.
//

#ifndef FTP_SERVER_FILEHANDLER_HPP
#define FTP_SERVER_FILEHANDLER_HPP


#include "Handler.hpp"
#include <sys/stat.h>
#include "filesystem"

#define PWD_COMMAND "pwd"
#define MKDIR_COMMAND "mkd"
#define RM_COMMAND "dele"
#define LS_COMMAND "ls"

class FileHandler : public Handler {
    void handle(WebSocket *_command_channel, WebSocket *_data_channel, WorkContext *_work_context,
                std::vector<std::string> _cmd) override;

public:
    FileHandler();

private:
    void pwd();

    void mkd(const std::string &_path);

    void rm();

    void ls();

    std::pair<std::string, std::string> parse_rm_command(const std::vector<std::string> &_cmd);

private:
    std::vector<std::string> cmd;
    Logger *logger;
    WorkContext *work_context;
};


#endif //FTP_SERVER_FILEHANDLER_HPP
