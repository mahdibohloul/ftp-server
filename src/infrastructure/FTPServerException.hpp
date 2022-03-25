#ifndef FTP_SERVER_FTPSERVEREXCEPTION_HPP
#define FTP_SERVER_FTPSERVEREXCEPTION_HPP

#include <exception>
#include <utility>
#include "string"

class FTPServerException : public std::exception {
public:
    FTPServerException(std::string message, int error_code) : _message(std::move(message)) {
        this->error_code = error_code;
    }

    int get_error_code() const {
        return error_code;
    }

    std::string to_string() const {
        return std::to_string(error_code) + ": " + _message;
    }

private:
    int error_code;
    std::string _message;
};

#endif //FTP_SERVER_FTPSERVEREXCEPTION_HPP
