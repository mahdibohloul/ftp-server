#ifndef FTP_SERVER_USER_HPP
#define FTP_SERVER_USER_HPP

#include "string"
#include "../../directory/models/Directory.hpp"
#include "Role.hpp"
#include "../../../infrastructure/BaseEntity.hpp"
#include <utility>
#include <unistd.h>

class User : public BaseEntity {
public:
    User(std::string &username, std::string &password, double download_capacity,
         Directory *current_directory = nullptr, std::vector<Role> roles = {Role::USER});

    [[nodiscard]] bool is_admin() const;

    std::vector<Role> get_roles() const;

    [[nodiscard]] std::string get_username() const;

    [[nodiscard]] std::string get_password() const;

    [[nodiscard]] double get_download_capacity() const;

    [[nodiscard]] Directory *get_current_directory() const;

    void set_current_directory(Directory *_current_directory);

private:
    std::string username;
    std::string password;
    double download_capacity;
    Directory *current_directory;
    std::vector<Role> roles;
};


#endif //FTP_SERVER_USER_HPP
