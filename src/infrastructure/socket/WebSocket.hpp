//
// Created by mahdi on 25/03/2022.
//

#ifndef FTP_SERVER_WEBSOCKET_HPP
#define FTP_SERVER_WEBSOCKET_HPP

#include "../logger/Logger.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../logger/LoggerFactory.hpp"


class WebSocket {
public:
    explicit WebSocket(int port);

    void close_socket();

    int get_socket_fd();

private:
    void set_up_socket();

private:
    int port;
    int fd;
    Logger *logger;
    struct sockaddr_in server_addr;

};


#endif //FTP_SERVER_WEBSOCKET_HPP
