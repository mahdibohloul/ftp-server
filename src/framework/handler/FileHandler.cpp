#include "FileHandler.hpp"

namespace fs = std::filesystem;

void FileHandler::handle(WebSocket *_command_channel, WebSocket *_data_channel, WorkContext *_work_context,
                         std::vector<std::string> _cmd) {
    cmd = _cmd;
    work_context = _work_context;
    if (is_user_logged_in(work_context, logger, work_context->get_work_command_fd())) {
        if (cmd[0] == PWD_COMMAND) {
            cmd.erase(cmd.begin());
            if (is_valid_command(cmd, 0, 0, logger, work_context->get_work_command_fd(),
                                 work_context->get_current_user()->get_username())) {
                pwd();
            }
        } else if (cmd[0] == MKDIR_COMMAND) {
            cmd.erase(cmd.begin());
            if (is_valid_command(cmd, 1, 1, logger, work_context->get_work_command_fd(),
                                 work_context->get_current_user()->get_username())) {
                mkd(cmd[0]);
            }
        } else if (cmd[0] == RM_COMMAND) {
            cmd.erase(cmd.begin());
            if (is_valid_command(cmd, 2, 2, logger, work_context->get_work_command_fd(),
                                 work_context->get_current_user()->get_username())) {
                rm();
            }
        } else if (cmd[0] == LS_COMMAND) {
            cmd.erase(cmd.begin());
            if (is_valid_command(cmd, 0, 0, logger, work_context->get_work_command_fd(),
                                 work_context->get_current_user()->get_username())) {
                ls();
            }
        } else if (cmd[0] == CD_COMMAND) {
            cmd.erase(cmd.begin());
            if (is_valid_command(cmd, 0, 1, logger, work_context->get_work_command_fd(),
                                 work_context->get_current_user()->get_username())) {
                std::string path = cmd.size() == 1 ? cmd[0] : "";
                cd(path);
            }
        } else if (cmd[0] == RENAME_COMMAND) {
            cmd.erase(cmd.begin());
            if (is_valid_command(cmd, 2, 2, logger, work_context->get_work_command_fd(),
                                 work_context->get_current_user()->get_username())) {
                rename_file(cmd[0], cmd[1]);
            }
        } else if (cmd[0] == DOWNLOAD_COMMAND) {
            cmd.erase(cmd.begin());
            if (is_valid_command(cmd, 1, 1, logger, work_context->get_work_command_fd(),
                                 work_context->get_current_user()->get_username())) {
                download(cmd[0]);
            }
        }
    }
}

FileHandler::FileHandler() {
    logger = LoggerFactory::getLogger("FileHandler");
    work_context = nullptr;
    granted_file_service = GrantedFileService::getInstance();
}

void FileHandler::pwd() {
    auto current_dir = work_context->get_current_user()->get_current_directory();
    std::string msg = std::to_string(ftp_error_code::PWD_SUCCESSFUL) + ": " + current_dir->get_path();
    send_message(work_context->get_work_command_fd(), msg, logger, work_context->get_current_user()->get_username());
}

void FileHandler::mkd(const std::string &_path) {
    if (chdir(work_context->get_current_user()->get_current_directory()->get_path().c_str()) == -1) {
        std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Failed to change directory";
        send_error(work_context->get_work_command_fd(), msg, logger, work_context->get_current_user()->get_username());
        return;
    }
    if (mkdir(_path.c_str(), ACCESSPERMS) == -1) {
        std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Failed to create directory";
        send_error(work_context->get_work_command_fd(), msg, logger, work_context->get_current_user()->get_username());
        return;
    }
    std::string msg = std::to_string(ftp_error_code::MKD_SUCCESSFUL) + ": " + _path + " created.";
    send_message(work_context->get_work_command_fd(), msg, logger, work_context->get_current_user()->get_username());
}

void FileHandler::rm() {
    const auto &[flag, path] = parse_rm_command(cmd);
    if (flag == "-f") {
        if (chdir(work_context->get_current_user()->get_current_directory()->get_path().c_str()) == -1) {
            std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Failed to change directory";
            send_error(work_context->get_work_command_fd(), msg, logger,
                       work_context->get_current_user()->get_username());
            return;
        }
        if (remove(path.c_str()) == -1) {
            std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Failed to remove file";
            send_error(work_context->get_work_command_fd(), msg, logger,
                       work_context->get_current_user()->get_username());
            return;
        }
        std::string msg = std::to_string(ftp_error_code::DELETE_SUCCESSFUL) + ": " + path + " deleted.";
        send_message(work_context->get_work_command_fd(), msg, logger,
                     work_context->get_current_user()->get_username());
    } else if (flag == "-d") {
        if (chdir(work_context->get_current_user()->get_current_directory()->get_path().c_str()) == -1) {
            std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Failed to change directory";
            send_error(work_context->get_work_command_fd(), msg, logger,
                       work_context->get_current_user()->get_username());
            return;
        }
        if (rmdir(path.c_str()) == -1) {
            std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Failed to remove directory";
            send_error(work_context->get_work_command_fd(), msg, logger,
                       work_context->get_current_user()->get_username());
            return;
        }
        std::string msg = std::to_string(ftp_error_code::DELETE_SUCCESSFUL) + ": " + path + " deleted.";
        send_message(work_context->get_work_command_fd(), msg, logger,
                     work_context->get_current_user()->get_username());
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
        send_error(work_context->get_work_command_fd(), msg, logger, work_context->get_current_user()->get_username());
    }
    return std::make_pair(flag, path);
}

void FileHandler::ls() {
    auto path = work_context->get_current_user()->get_current_directory()->get_path();
    std::stringstream ss;
    ss << "." << " " << ".." << " ";
    for (const auto &entry: fs::directory_iterator(path)) {
        ss << entry.path().filename() << " ";
    }

    std::string msg = std::to_string(ftp_error_code::SEND_DATA_SUCCESSFUL) + ": List transfer done";
    send_message(work_context->get_work_command_fd(), msg, logger, work_context->get_current_user()->get_username());
    send_data(work_context->get_work_data_fd(), ss.str(), logger, work_context->get_current_user()->get_username());
}

void FileHandler::cd(const std::string &_path) {
    std::string path = _path;
    if (path.empty()) {
        work_context->get_current_user()->set_current_directory(Directory::get_root());
        std::string msg = std::to_string(ftp_error_code::CD_SUCCESSFUL) + ": Successfully changed.";
        send_message(work_context->get_work_command_fd(), msg, logger,
                     work_context->get_current_user()->get_username());
        return;
    } else if (path == "..") {
        if (work_context->get_current_user()->get_current_directory()->get_parent() == nullptr) {
            std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Failed to change directory";
            send_error(work_context->get_work_command_fd(), msg, logger,
                       work_context->get_current_user()->get_username());
            return;
        }
        work_context->get_current_user()->set_current_directory(
                work_context->get_current_user()->get_current_directory()->get_parent());
        std::string msg = std::to_string(ftp_error_code::CD_SUCCESSFUL) + ": Successfully changed.";
        send_message(work_context->get_work_command_fd(), msg, logger,
                     work_context->get_current_user()->get_username());
        return;
    } else if (path == ".") {
        std::string msg = std::to_string(ftp_error_code::CD_SUCCESSFUL) + ": Successfully changed.";
        send_message(work_context->get_work_command_fd(), msg, logger,
                     work_context->get_current_user()->get_username());
        return;
    } else {
        path = work_context->get_current_user()->get_current_directory()->get_path() + "/" + path;
        if (is_path_exist(path)) {
            if (is_path_directory(path)) {
                work_context->get_current_user()->set_current_directory(
                        new Directory(path, work_context->get_current_user()->get_current_directory()));
                std::string msg = std::to_string(ftp_error_code::CD_SUCCESSFUL) + ": Successfully changed.";
                send_message(work_context->get_work_command_fd(), msg, logger,
                             work_context->get_current_user()->get_username());
                return;
            }
            std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Failed to change directory";
            send_error(work_context->get_work_command_fd(), msg, logger,
                       work_context->get_current_user()->get_username());
            return;
        }
    }
}

bool FileHandler::is_path_exist(const std::string &_path) {
    struct stat st;
    return (stat(_path.c_str(), &st) == 0);
}

void FileHandler::rename_file(const std::string &_old_name, const std::string &_new_name) {
    std::string old_name_path = work_context->get_current_user()->get_current_directory()->get_path() + "/" + _old_name;
    if (!is_file_accessible(old_name_path)) {
        std::string msg = std::to_string(ftp_error_code::ACCESS_DENIED) + ": File unavailable";
        send_error(work_context->get_work_command_fd(), msg, logger,
                   work_context->get_current_user()->get_username());
        return;
    }
    std::string current_dir(get_current_dir_name());
    chdir(work_context->get_current_user()->get_current_directory()->get_path().c_str());
    int ret = rename(_old_name.c_str(), _new_name.c_str());
    chdir(current_dir.c_str());
    if (ret == 0) {
        std::string msg = std::to_string(ftp_error_code::RENAME_SUCCESSFUL) + ": Successfully change.";
        send_message(work_context->get_work_command_fd(), msg, logger,
                     work_context->get_current_user()->get_username());
        return;
    } else {
        std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Failed to rename file";
        send_error(work_context->get_work_command_fd(), msg, logger,
                   work_context->get_current_user()->get_username());
        return;
    }
}

bool FileHandler::is_file_accessible(const std::string &_path) {
    auto granted_file = granted_file_service->find_by_path(_path);
    if (granted_file == nullptr)
        return true;
    return std::any_of(work_context->get_current_user()->get_roles().begin(),
                       work_context->get_current_user()->get_roles().end(), [&](const Role role) {
                return granted_file->has_permission(role);
            });
}

void FileHandler::download(const std::string &_file_name) {
    auto path = work_context->get_current_user()->get_current_directory()->get_path() + "/" + _file_name;
    auto remaining_capacity = work_context->get_current_user()->get_download_capacity();
    if (!is_file_accessible(path)) {
        std::string msg = std::to_string(ftp_error_code::ACCESS_DENIED) + ": File unavailable";
        send_error(work_context->get_work_command_fd(), msg, logger,
                   work_context->get_current_user()->get_username());
        return;
    }

    std::ifstream target_file(path);
    if (!target_file.is_open()) {
        std::string msg = std::to_string(ftp_error_code::INTERNAL_ERROR) + ": Failed to open file";
        send_error(work_context->get_work_command_fd(), msg, logger,
                   work_context->get_current_user()->get_username());
        return;
    }

    std::stringstream buffer;
    buffer << target_file.rdbuf();
    std::string file_content = buffer.str();
    target_file.close();
    double file_size = file_content.size();
    if (remaining_capacity < file_size) {
        target_file.close();
        std::string msg = std::to_string(ftp_error_code::CANNOT_OPEN_DATA_CONNECTION) + ": Can't open data connection";
        send_error(work_context->get_work_command_fd(), msg, logger,
                   work_context->get_current_user()->get_username());
        return;
    }
    work_context->get_current_user()->decrease_download_capacity(file_size);
    std::string msg = std::to_string(ftp_error_code::SEND_DATA_SUCCESSFUL) + ": Successful Download.";
    send_message(work_context->get_work_command_fd(), msg, logger,
                 work_context->get_current_user()->get_username());
    send_data(work_context->get_work_data_fd(), file_content, logger,
              work_context->get_current_user()->get_username());
}

bool FileHandler::is_path_directory(const std::string &_path) {
    return fs::is_directory(_path);

}