#ifndef FTP_SERVER_USER_HPP
#define FTP_SERVER_USER_HPP

#include "string"
#include "../../directory/models/Directory.hpp"
#include <unistd.h>

class User {
public:
    User(std::string &username, std::string &password, bool admin, double download_capacity,
         Directory *current_directory = nullptr);

    [[nodiscard]] bool is_admin() const;

    void set_id(int _id);

    [[nodiscard]] int get_id() const;

    [[nodiscard]] std::string get_username() const;

    [[nodiscard]] std::string get_password() const;

    [[nodiscard]] double get_download_capacity() const;

    [[nodiscard]] Directory *get_current_directory() const;

private:
    int id;
    std::string username;
    std::string password;
    double download_capacity;
    bool admin;
    Directory *current_directory;

};


#endif //FTP_SERVER_USER_HPP
