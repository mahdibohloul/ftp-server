//
// Created by mahdi on 24/03/2022.
//

#include "LoggerFactory.hpp"

using namespace std;

Logger *LoggerFactory::default_logger = nullptr;
map<string, Logger *> LoggerFactory::logger_map;

Logger *LoggerFactory::getInstance() {
    if (default_logger == nullptr) {
        default_logger = new Logger("default");
    }
    return default_logger;
}

Logger *LoggerFactory::getInstance(const std::string &name) {
    if (logger_map.find(name) == logger_map.end()) {
        logger_map[name] = new Logger(name);
    }
    return logger_map[name];
}

Logger *LoggerFactory::getLogger() {
    return getInstance();
}

Logger *LoggerFactory::getLogger(const std::string &name) {
    return getInstance(name);
}

LoggerFactory::~LoggerFactory() {
    for (auto &logger: logger_map) {
        delete logger.second;
    }
    delete default_logger;
}
