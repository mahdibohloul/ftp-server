#ifndef FTP_SERVER_DATASOCKET_HPP
#define FTP_SERVER_DATASOCKET_HPP


#include "../../logger/Logger.hpp"
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include "../../logger/LoggerFactory.hpp"

class DataSocket {
public:
    explicit DataSocket(int port);
    void close_socket();

private:
    void set_up_socket();

private:
    int port;
    int fd;
    Logger *logger;
    struct sockaddr_in server_addr;
};


#endif //FTP_SERVER_DATASOCKET_HPP
