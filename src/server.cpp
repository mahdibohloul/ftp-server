#include "infrastructure/server/Server.hpp"

int main() {
    auto *server = Server::getInstance();
    server->bootstrap("./config.json");
    server->start();
    return 0;
}