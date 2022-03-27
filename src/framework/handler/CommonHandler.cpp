//
// Created by mahdi on 27/03/2022.
//

#include "CommonHandler.hpp"

void CommonHandler::handle(WebSocket *_command_channel, WebSocket *_data_channel, WorkContext *_work_context,
                           std::vector<std::string> _cmd) {
    this->work_context = _work_context;
    this->cmd = _cmd;
    if (is_user_logged_in(work_context, logger, work_context->get_work_command_fd())) {
        if (cmd[0] == HELP_COMMAND) {
            cmd.erase(cmd.begin());
            if (is_valid_command(cmd, 0, 0, logger, work_context->get_work_command_fd(),
                                 work_context->get_current_user()->get_username())) {
                help();
            }
        }
    }
}

CommonHandler::CommonHandler() {
    logger = LoggerFactory::getLogger("CommonHandler");
    work_context = nullptr;
}

void CommonHandler::help() {
    std::ifstream help_file("./help.txt");
    std::stringstream ss;
    ss << help_file.rdbuf();
    std::string help_text = ss.str();
    help_file.close();
    send_message(work_context->get_work_command_fd(), help_text, logger,
                 work_context->get_current_user()->get_username());
}
