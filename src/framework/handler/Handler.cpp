#include "Handler.hpp"


void
Handler::send_error(int client_fd, const std::string &_error_message, Logger *logger, const std::string &username) {
    logger->error(username + ", " + _error_message);
    send(client_fd, &_error_message[0], _error_message.size(), 0);
}

void Handler::send_message(int client_fd, std::string _message, Logger *logger, const std::string &username) {
    logger->info(username + ", " + _message);
    send(client_fd, &_message[0], _message.size(), 0);
}

void Handler::send_data(int client_fd, std::string _data, Logger *logger, const std::string &username) {
    logger->info(username + ", " + _data);
    send(client_fd, &_data[0], _data.size(), 0);
}

bool Handler::is_valid_command(const std::vector<std::string> &cmd, int minimum_length, int maximum_length,
                               Logger *logger, int client_fd, const std::string &username) {
    if (cmd.size() < minimum_length) {
        std::string msg = std::to_string(ftp_error_code::MISSING_ARGUMENT) + ": No argument provided";
        send_error(client_fd, msg, logger, username);
        return false;
    }
    if (cmd.size() > maximum_length) {
        std::string msg = std::to_string(ftp_error_code::TOO_MANY_ARGUMENTS) + ": Too many arguments";
        send_error(client_fd, msg, logger, username);
        return false;
    }
    return true;
}

bool Handler::is_user_logged_in(WorkContext *work_context, Logger *logger, int client_fd) {
    if (work_context->get_current_user() == nullptr) {
        std::string msg = std::to_string(ftp_error_code::NOT_LOGGED_IN) + ": Need account for login";
        send_error(client_fd, msg, logger);
        return false;
    }
    return true;
}
