#include "Handler.hpp"


void Handler::send_error(int client_fd, const std::string &_error_message, Logger *logger) {
    logger->error(_error_message);
    send(client_fd, &_error_message[0], _error_message.size(), 0);
}

void Handler::send_message(int client_fd, std::string _message, Logger *logger) {
    logger->info(_message);
    send(client_fd, &_message[0], _message.size(), 0);
}

void Handler::send_data(int client_fd, std::string _data, Logger *logger) {
    logger->info(_data);
    send(client_fd, &_data[0], _data.size(), 0);
}

bool Handler::is_valid_command(const std::vector<std::string> &cmd, int minimum_length, int maximum_length,
                               Logger *logger, int client_fd) {
    if (cmd.size() < minimum_length) {
        std::string msg = std::to_string(ftp_error_code::MISSING_ARGUMENT) + ": No argument provided";
        send_error(client_fd, msg, logger);
        return false;
    }
    if (cmd.size() > maximum_length) {
        std::string msg = std::to_string(ftp_error_code::TOO_MANY_ARGUMENTS) + ": Too many arguments";
        send_error(client_fd, msg, logger);
        return false;
    }
    return true;
}
