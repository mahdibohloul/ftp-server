#include "Router.hpp"


Router::Router(int _client_command_fd, int _client_data_fd, char *_cmd) {
    this->client_command_fd = _client_command_fd;
    this->client_data_fd = _client_data_fd;
    this->cmd = _cmd;
    this->work_context = new WorkContext(this->client_command_fd, this->client_data_fd);
    command_channel = Server::getInstance()->get_command_channel();
    data_channel = Server::getInstance()->get_data_channel();
    logger = LoggerFactory::getLogger("Router");
    set_up_handlers();
}

void Router::execute() {
    try {
        auto splitted_cmd = split_cmd(cmd);
        if (splitted_cmd.empty()) {
            throw FTPServerException("Invalid command", ftp_error_code::INTERNAL_ERROR);
        }
        auto handler = handlers[splitted_cmd[0]];
        if (handler == nullptr) {
            throw FTPServerException("Invalid command", ftp_error_code::INTERNAL_ERROR);
        }
        handler->handle(command_channel, data_channel, work_context, splitted_cmd);
    } catch (FTPServerException &e) {
        Handler::send_error(work_context->get_work_command_fd(), e.to_string(), logger);
    }

}

void Router::set_up_handlers() {
    auto user_handler = new AuthenticationHandler();
    auto file_handler = new FileHandler();
    this->handlers.insert(std::make_pair(CHECK_USERNAME_COMMAND, user_handler));
    this->handlers.insert(std::make_pair(CHECK_PASSWORD_COMMAND, user_handler));
    this->handlers.insert(std::make_pair(PWD_COMMAND, file_handler));
    this->handlers.insert(std::make_pair(MKDIR_COMMAND, file_handler));
    this->handlers.insert(std::make_pair(RM_COMMAND, file_handler));
    this->handlers.insert(std::make_pair(LS_COMMAND, file_handler));
    this->handlers.insert(std::make_pair(CD_COMMAND, file_handler));
}

std::vector<std::string> Router::split_cmd(std::string cmd) {
    std::vector<std::string> cmd_list;
    char *token = strtok(&cmd[0], " ");
    while (token != nullptr) {
        cmd_list.emplace_back(token);
        token = strtok(nullptr, " ");
    }
    return cmd_list;
}
