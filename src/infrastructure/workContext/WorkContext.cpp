#include "WorkContext.hpp"

WorkContext::WorkContext(int work_fd) {
    this->work_fd = work_fd;
    this->current_user = nullptr;
}

User *WorkContext::get_current_user() {
    return this->current_user;
}

void WorkContext::set_current_user(User *user) {
    this->current_user = user;
}

std::string WorkContext::get_current_ip() {
    struct sockaddr_in addr;
    socklen_t len = sizeof(struct sockaddr_in);
    getpeername(this->work_fd, (struct sockaddr *) &addr, &len);
    return inet_ntoa(addr.sin_addr);
}

int WorkContext::get_work_fd() {
    return this->work_fd;
}
