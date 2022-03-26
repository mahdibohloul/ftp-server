#include "WorkContext.hpp"

WorkContext::WorkContext(int work_command_fd, int work_data_fd) {
    this->work_command_fd = work_command_fd;
    this->work_data_fd = work_data_fd;
    this->current_user = nullptr;
}

User *WorkContext::get_current_user() {
    return this->current_user;
}

void WorkContext::set_current_user(User *user) {
    this->current_user = user;
}

std::string WorkContext::get_current_ip() const {
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr_in);
    getpeername(this->work_command_fd, (struct sockaddr *) &addr, &len);
    return inet_ntoa(addr.sin_addr);
}

int WorkContext::get_work_command_fd() const {
    return this->work_command_fd;
}

int WorkContext::get_work_data_fd() const {
    return this->work_data_fd;
}
