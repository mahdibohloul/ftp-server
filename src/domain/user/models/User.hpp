#ifndef FTP_SERVER_USER_HPP
#define FTP_SERVER_USER_HPP

#include "string"

class User {
public:
    User(std::string& username, std::string& password, bool admin, double download_capacity);
    bool is_admin() const;
    void set_id(int _id);
    int get_id() const;
private:
    int id;
    std::string username;
    std::string password;
    double download_capacity;
    bool admin;

};


#endif //FTP_SERVER_USER_HPP
