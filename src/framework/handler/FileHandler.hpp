//
// Created by mahdi on 25/03/2022.
//

#ifndef FTP_SERVER_FILEHANDLER_HPP
#define FTP_SERVER_FILEHANDLER_HPP


#include "Handler.hpp"
#include <sys/stat.h>
#include "filesystem"
#include "../../domain/file/services/GrantedFileService.hpp"

#define PWD_COMMAND "pwd"
#define MKDIR_COMMAND "mkd"
#define RM_COMMAND "dele"
#define LS_COMMAND "ls"
#define CD_COMMAND "cwd"
#define RENAME_COMMAND "rename_file"
#define DOWNLOAD_COMMAND "retr"

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

    void cd(const std::string &_path = "");

    void rename_file(const std::string &_old_name, const std::string &_new_name);

    void download(const std::string &_file_name);

    static bool is_path_exist(const std::string &_path);

    static bool is_path_directory(const std::string &_path);

    std::pair<std::string, std::string> parse_rm_command(const std::vector<std::string> &_cmd);

    bool is_file_accessible(const std::string &_path);

private:
    std::vector<std::string> cmd;
    Logger *logger;
    WorkContext *work_context;
    GrantedFileService *granted_file_service;
};


#endif //FTP_SERVER_FILEHANDLER_HPP
