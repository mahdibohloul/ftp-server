//
// Created by mahdi on 24/03/2022.
//

#include "Logger.hpp"


using namespace std;

Logger::Logger(const string &name) {
    this->log_file_name = "../log.txt";
    this->name = name;
}

Logger::Logger(const std::string &logFile, const std::string &name) {
    this->log_file_name = logFile;
    this->name = name;
}

void Logger::info(const char *message) {
    ofstream log_file(this->log_file_name, ios_base::app);
    string msg = "[INFO] " + this->name + " " + TimeService::get_current_date_time() + ": " + message + "\n";
    cout << msg;
    log_file << msg;
    log_file.close();
}

void Logger::error(const char *message) {
    ofstream log_file(this->log_file_name, ios_base::app);
    string msg = "[ERROR] " + this->name + " " + TimeService::get_current_date_time() + ": " + message + "\n";
    cout << msg;
    log_file << msg;
    log_file.close();
}

void Logger::info(const string &message) {
    info(&message[0]);
}

void Logger::error(const std::string &message) {
    error(&message[0]);
}
