#ifndef FTP_SERVER_WORKCONTEXT_HPP
#define FTP_SERVER_WORKCONTEXT_HPP


#include "../../domain/user/models/User.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>

class WorkContext {
public:
    explicit WorkContext(int work_fd);

    User *get_current_user();

    void set_current_user(User *user);

    std::string get_current_ip();

    int get_work_fd();

private:
    User *current_user;
    int work_fd;
};


#endif //FTP_SERVER_WORKCONTEXT_HPP
