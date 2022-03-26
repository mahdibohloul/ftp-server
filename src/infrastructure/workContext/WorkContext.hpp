#ifndef FTP_SERVER_WORKCONTEXT_HPP
#define FTP_SERVER_WORKCONTEXT_HPP


#include "../../domain/user/models/User.hpp"
#include <netinet/in.h>
#include <arpa/inet.h>

class WorkContext {
public:
    explicit WorkContext(int work_command_fd, int work_data_fd);

    User *get_current_user();

    void set_current_user(User *user);

    std::string get_current_ip() const;

    int get_work_command_fd() const;

    int get_work_data_fd() const;

private:
    User *current_user;
    int work_command_fd;
    int work_data_fd;
};


#endif //FTP_SERVER_WORKCONTEXT_HPP
