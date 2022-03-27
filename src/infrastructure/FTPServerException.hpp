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

    [[nodiscard]] int get_error_code() const {
        return error_code;
    }

    [[nodiscard]] std::string to_string() const {
        return std::to_string(error_code) + ": " + _message;
    }

private:
    int error_code;
    std::string _message;
};

class QuitException : public FTPServerException {
public:
    explicit QuitException(std::string message) : FTPServerException(std::move(message), 0) {}
};

#endif //FTP_SERVER_FTPSERVEREXCEPTION_HPP
