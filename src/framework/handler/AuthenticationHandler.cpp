#include "AuthenticationHandler.hpp"

using namespace std;

void AuthenticationHandler::handle(WebSocket *_command_channel, WebSocket *_data_channel, WorkContext *_work_context,
                                   std::vector<std::string> _cmd) {
    this->data_channel = _data_channel;
    this->command_channel = _command_channel;
    this->work_context = _work_context;
    this->cmd = _cmd;
    if (cmd[0] == CHECK_USERNAME_COMMAND) {
        cmd.erase(cmd.begin());
        if (is_valid_command(cmd, 1, 1, logger, work_context->get_work_command_fd()))
            check_username(cmd[0]);
    } else if (cmd[0] == CHECK_PASSWORD_COMMAND) {
        cmd.erase(cmd.begin());
        if (is_valid_command(cmd, 1, 1, logger, work_context->get_work_command_fd()))
            check_password(cmd[0]);
    }

}


AuthenticationHandler::AuthenticationHandler() {
    this->waiting_for_password = false;
    data_channel = nullptr;
    command_channel = nullptr;
    work_context = nullptr;
    pending_user = nullptr;
    this->logger = LoggerFactory::getLogger("AuthenticationHandler");
}

void AuthenticationHandler::check_username(const std::string &username) {
    if (work_context->get_current_user() != nullptr) {
        string msg = to_string(ftp_error_code::ALREADY_LOGGED_IN) + ": " +
                     work_context->get_current_user()->get_username() + " are already logged in";
        send_error(work_context->get_work_command_fd(), msg, logger);
        return;
    }
    auto user_service = UserService::getInstance();
    auto user = user_service->find_user(username);
    if (user == nullptr) {
        string msg = to_string(ftp_error_code::INVALID_USERNAME_OR_PASSWORD) + ": Invalid username or password";
        send_error(work_context->get_work_command_fd(), msg, logger);
        return;
    }
    this->waiting_for_password = true;
    this->pending_user = user;
    string msg = to_string(ftp_error_code::USERNAME_OK) + ": User name okay, need password.";
    send_message(work_context->get_work_command_fd(), msg, logger);
}

void AuthenticationHandler::check_password(const string &password) {
    if (!waiting_for_password) {
        string msg = to_string(ftp_error_code::BAD_SEQUENCE_OF_COMMANDS) + ": Bad sequence of commands.";
        send_error(work_context->get_work_command_fd(), msg, logger);
        return;
    }
    if (this->pending_user->get_password() != password) {
        string msg = to_string(ftp_error_code::INVALID_USERNAME_OR_PASSWORD) + ": Invalid username or password";
        send_error(work_context->get_work_command_fd(), msg, logger);
        return;
    }
    this->waiting_for_password = false;
    work_context->set_current_user(pending_user);
    pending_user = nullptr;
    string msg = to_string(ftp_error_code::LOGIN_SUCCESSFUL) + ": User logged in, proceed. Logged out if appropriate.";
    send_message(work_context->get_work_command_fd(), msg, logger, work_context->get_current_user()->get_username());
}

