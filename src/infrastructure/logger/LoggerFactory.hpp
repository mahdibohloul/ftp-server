//
// Created by mahdi on 24/03/2022.
//

#ifndef FTP_SERVER_LOGGERFACTORY_HPP
#define FTP_SERVER_LOGGERFACTORY_HPP


#include "Logger.hpp"
#include "map"

class LoggerFactory {
public:
    static Logger *getLogger();

    static Logger *getLogger(const std::string &name);

private:
    static Logger *getInstance();

    ~LoggerFactory();

    static Logger *getInstance(const std::string &name);

    static Logger *default_logger;
    static std::map<std::string, Logger *> logger_map;
};


#endif //FTP_SERVER_LOGGERFACTORY_HPP
