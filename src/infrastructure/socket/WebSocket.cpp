#include "WebSocket.hpp"

WebSocket::WebSocket(int port) {
    this->port = port;
    this->logger = LoggerFactory::getLogger("WebSocket");
    std::string msg = "Establishing connection on port " + std::to_string(port) + "...";
    this->logger->info(&msg[0]);
    this->set_up_socket();
    msg = "Connection established on port " + std::to_string(port) + ".";
    this->logger->info(&msg[0]);
}

void WebSocket::set_up_socket() {
    this->fd = socket(AF_INET, SOCK_STREAM, 0);
    if (!this->fd) {
        std::string msg = "Failed to create socket on port " + std::to_string(this->port) + ".";
        this->logger->error(&msg[0]);
        exit(1);
    }
    setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, (char *) 1, sizeof(int));
    this->server_addr.sin_family = AF_INET;
    this->server_addr.sin_port = htons(this->port);
    inet_pton(AF_INET, "127.0.0.1", &this->server_addr.sin_addr.s_addr);
    if (bind(this->fd, (struct sockaddr *) &this->server_addr, sizeof(this->server_addr)) < 0) {
        std::string msg = "Failed to bind socket on port " + std::to_string(this->port) + ".";
        this->logger->error(&msg[0]);
        exit(1);
    }
    if (listen(this->fd, 10) < 0) {
        std::string msg = "Failed to listen on socket on port " + std::to_string(this->port) + ".";
        this->logger->error(&msg[0]);
        exit(1);
    }
}

void WebSocket::close_socket() {
    close(this->fd);
}

int WebSocket::get_socket_fd() {
    return this->fd;
}
