#include "Server.hpp"
#include "../../framework/router/Router.hpp"

#define RUNNING 1
#define RECEIVING 1
#define BUFFER_SIZE 1024

using namespace std;


Server *Server::instance = nullptr;

Server::Server() {
    this->user_service = UserService::getInstance();
    this->file_service = GrantedFileService::getInstance();
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
    this->data_socket = new WebSocket(server_config->get_data_channel_port());
    this->command_socket = new WebSocket(server_config->get_command_channel_port());
    this->user_service->insert_users(server_config->get_users());
    this->file_service->insert_files(server_config->get_protected_files());
    this->logger->info("Server booted up successfully.");
}

void Server::start() {
    struct sockaddr_in client_address;
    char buffer[BUFFER_SIZE];
    this->logger->info("Starting server...");
    while (RUNNING) {
        int client_command_fd;
        int client_data_fd;
        int client_length = sizeof(client_address);
        if (!(client_command_fd = accept(this->command_socket->get_socket_fd(),
                                         (struct sockaddr *) &client_address,
                                         (socklen_t *) &client_length))) {
            logger->error("Cannot accept command");
            continue;
        }
        if (!(client_data_fd = accept(this->data_socket->get_socket_fd(),
                                      (struct sockaddr *) &client_address,
                                      (socklen_t *) &client_length))) {
            logger->error("Cannot accept data");
            continue;
        }
        this->logger->info("Client connected.");
        auto router = new Router(client_command_fd, client_data_fd, buffer);
        while (RECEIVING) {
            recv(client_command_fd, buffer, BUFFER_SIZE, 0);
            try {
                router->execute();
            } catch (QuitException &e) {
                break;
            } catch (std::exception &e) {
                this->logger->error(e.what());
                break;
            }
        }
        close(client_command_fd);
        close(client_data_fd);
        this->logger->info("Client disconnected.");
    }
    data_socket->close_socket();
    command_socket->close_socket();
    this->logger->info("Server stopped.");
}

WebSocket *Server::get_command_channel() {
    return this->command_socket;
}

WebSocket *Server::get_data_channel() {
    return this->data_socket;
}


