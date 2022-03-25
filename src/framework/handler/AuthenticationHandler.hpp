#ifndef FTP_SERVER_AUTHENTICATIONHANDLER_HPP
#define FTP_SERVER_AUTHENTICATIONHANDLER_HPP


#include "Handler.hpp"
#include "../../infrastructure/FTPServerErrorCode.hpp"
#include "../../domain/user/services/UserService.hpp"

#define CHECK_USERNAME_COMMAND "user"
#define CHECK_PASSWORD_COMMAND "pass"

class AuthenticationHandler : public Handler {
    void handle(WebSocket *_command_channel, WebSocket *_data_channel, WorkContext *_work_context,
                std::vector<std::string> _cmd) override;


public:
    AuthenticationHandler();

private:
    WorkContext *work_context;
    WebSocket *command_channel;
    WebSocket *data_channel;
    std::vector<std::string> cmd;
    bool waiting_for_password;
    User *pending_user;
    Logger *logger;

    void check_username(const std::string &username);

    void check_password(const std::string &password);
};


#endif //FTP_SERVER_AUTHENTICATIONHANDLER_HPP
