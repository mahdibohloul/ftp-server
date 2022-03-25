#include <cstring>
#include "Router.hpp"
#include "../../infrastructure/FTPServerException.hpp"
#include "../../infrastructure/FTPServerErrorCode.hpp"
#include "../handler/AuthenticationHandler.hpp"
#include "../../infrastructure/server/Server.hpp"

Router::Router(int _client_fd, char *_cmd) {
    this->client_fd = _client_fd;
    this->cmd = _cmd;
    this->work_context = new WorkContext(this->client_fd);
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
        Handler::send_error(work_context->get_work_fd(), e.to_string(), logger);
    }

}

void Router::set_up_handlers() {
    auto userHandler = new AuthenticationHandler();
    this->handlers.insert(std::make_pair("user", userHandler));
    this->handlers.insert(std::make_pair("pass", userHandler));
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
