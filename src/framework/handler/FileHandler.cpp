#include "FileHandler.hpp"
#include "filesystem"

void FileHandler::handle(WebSocket *_command_channel, WebSocket *_data_channel, WorkContext *_work_context,
                         std::vector<std::string> _cmd) {
    cmd = _cmd;
    work_context = _work_context;
    if (is_user_logged_in(work_context, logger, work_context->get_work_fd())) {
        if (cmd[0] == PWD_COMMAND) {
            cmd.erase(cmd.begin());
            if (is_valid_command(cmd, 0, 0, logger, work_context->get_work_fd(),
                                 work_context->get_current_user()->get_username())) {
                pwd();
            }
        } else if (cmd[0] == MKDIR_COMMAND) {
            cmd.erase(cmd.begin());
            if (is_valid_command(cmd, 1, 1, logger, work_context->get_work_fd(),
                                 work_context->get_current_user()->get_username())) {
                mkd(cmd[0]);
            }
        } else if (cmd[0] == RM_COMMAND) {
            cmd.erase(cmd.begin());
            if (is_valid_command(cmd, 2, 2, logger, work_context->get_work_fd(),
                                 work_context->get_current_user()->get_username())) {
                rm();
            }
        }
    }
}

FileHandler::FileHandler() {
    logger = LoggerFactory::getLogger("FileHandler");
    work_context = nullptr;
}

void FileHandler::pwd() {
    auto current_dir = work_context->get_current_user()->get_current_directory();
    std::string msg = std::to_string(ftp_error_code::PWD_SUCCESSFUL) + ": " + current_dir->get_path();
    send_message(work_context->get_work_fd(), msg, logger, work_context->get_current_user()->get_username());
}

void FileHandler::mkd(const std::string &_path) {
    if (chdir(work_context->get_current_user()->get_current_directory()->get_path().c_str()) == -1) {
        std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Failed to change directory";
        send_error(work_context->get_work_fd(), msg, logger, work_context->get_current_user()->get_username());
        return;
    }
    if (mkdir(_path.c_str(), ACCESSPERMS) == -1) {
        std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Failed to create directory";
        send_error(work_context->get_work_fd(), msg, logger, work_context->get_current_user()->get_username());
        return;
    }
    std::string msg = std::to_string(ftp_error_code::MKD_SUCCESSFUL) + ": " + _path + " created.";
    send_message(work_context->get_work_fd(), msg, logger, work_context->get_current_user()->get_username());
}

void FileHandler::rm() {
    const auto &[flag, path] = parse_rm_command(cmd);
    if (flag == "-f") {
        if (chdir(work_context->get_current_user()->get_current_directory()->get_path().c_str()) == -1) {
            std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Failed to change directory";
            send_error(work_context->get_work_fd(), msg, logger, work_context->get_current_user()->get_username());
            return;
        }
        if (remove(path.c_str()) == -1) {
            std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Failed to remove file";
            send_error(work_context->get_work_fd(), msg, logger, work_context->get_current_user()->get_username());
            return;
        }
        std::string msg = std::to_string(ftp_error_code::DELETE_SUCCESSFUL) + ": " + path + " deleted.";
        send_message(work_context->get_work_fd(), msg, logger, work_context->get_current_user()->get_username());
    } else if (flag == "-d") {
        if (chdir(work_context->get_current_user()->get_current_directory()->get_path().c_str()) == -1) {
            std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Failed to change directory";
            send_error(work_context->get_work_fd(), msg, logger, work_context->get_current_user()->get_username());
            return;
        }
        if (rmdir(path.c_str()) == -1) {
            std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Failed to remove directory";
            send_error(work_context->get_work_fd(), msg, logger, work_context->get_current_user()->get_username());
            return;
        }
        std::string msg = std::to_string(ftp_error_code::DELETE_SUCCESSFUL) + ": " + path + " deleted.";
        send_message(work_context->get_work_fd(), msg, logger, work_context->get_current_user()->get_username());
    }
}

std::pair<std::string, std::string> FileHandler::parse_rm_command(const std::vector<std::string> &_cmd) {
    std::string flag;
    std::string path;
    if (_cmd[0] == "-f" || _cmd[0] == "-d") {
        flag = _cmd[0];
        path = _cmd[1];
    } else if (_cmd[1] == "-f" || _cmd[1] == "-d") {
        flag = _cmd[1];
        path = _cmd[0];
    } else {
        std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Invalid command";
        send_error(work_context->get_work_fd(), msg, logger, work_context->get_current_user()->get_username());
    }
    return std::make_pair(flag, path);
}
