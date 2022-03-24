//
// Created by mahdi on 24/03/2022.
//

#ifndef FTP_SERVER_COMMANDSOCKET_HPP
#define FTP_SERVER_COMMANDSOCKET_HPP


#include "../../logger/Logger.hpp"
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "../../logger/LoggerFactory.hpp"

class CommandSocket {
public:
    explicit CommandSocket(int port);
    bool can_accept_command(int client_fd, sockaddr_in client_addr);
    void close_socket();

private:
    void set_up_socket();

private:
    int port;
    int fd;
    Logger *logger;
    struct sockaddr_in server_addr;
};


#endif //FTP_SERVER_COMMANDSOCKET_HPP
