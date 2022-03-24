#include "Server.hpp"

#define RUNNING 1
#define RECEIVING 1
#define BUFFER_SIZE 1024

using namespace std;


Server *Server::instance = nullptr;

Server::Server() {
    this->user_service = UserService::getInstance();
    this->logger = LoggerFactory::getLogger("Server");
}

Server *Server::getInstance() {
    if (instance == nullptr) {
        instance = new Server();
    }
    return instance;
}

void Server::bootstrap(const std::string &config_file_path) {
    this->logger->info("Booting up server...");
    auto *server_config = new ServerConfig(config_file_path);
    server_config->read_config_file();
    this->data_socket = new DataSocket(server_config->get_data_channel_port());
    this->command_socket = new CommandSocket(server_config->get_command_channel_port());
    this->user_service->insert_users(server_config->get_users());
    this->logger->info("Server booted up successfully.");
}

void Server::start() {
    struct sockaddr_in client_address;
    char buffer[BUFFER_SIZE];
    while (RUNNING) {
        int client_fd;
        this->logger->info("Starting server...");
        if (!this->command_socket->can_accept_command(client_fd, client_address)) {
            logger->error("Cannot accept command");
            continue;
        }
        this->logger->info("Accepting command...");
        while (RECEIVING) {
            recv(client_fd, buffer, BUFFER_SIZE, 0);

        }
        close(client_fd);
    }
    data_socket->close_socket();
    command_socket->close_socket();
}


