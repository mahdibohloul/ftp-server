
#include "DataSocket.hpp"

using namespace std;

DataSocket::DataSocket(int port) {
    this->port = port;
    this->logger = LoggerFactory::getLogger("DataSocket");
    this->logger->info(&"Establishing connection on port "[port]);
    this->set_up_socket();
    this->logger->info(&"Connection established on port "[port]);
}

void DataSocket::set_up_socket() {
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!this->fd) {
        this->logger->error(&"Failed to create socket on port "[port]);
        exit(1);
    }
    setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, (char *) 1, sizeof(int));
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_port = htons(this->port);
    inet_pton(AF_INET, "127.0.0.1", &this->server_addr.sin_addr.s_addr);
    if (bind(this->fd, (struct sockaddr *) &this->server_addr, sizeof(this->server_addr)) < 0) {
        this->logger->error(&"Failed to bind socket on port "[port]);
        exit(1);
    }
    if (listen(this->fd, 10) < 0) {
        this->logger->error(&"Failed to listen on port "[port]);
        exit(1);
    }
}

void DataSocket::close_socket() {
    close(this->fd);
}
