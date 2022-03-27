//
// Created by mahdi on 27/03/2022.
//

#ifndef FTP_SERVER_GRANTEDFILE_HPP
#define FTP_SERVER_GRANTEDFILE_HPP

#include <vector>
#include "string"
#include <utility>
#include "../../user/models/Role.hpp"
#include "../../../infrastructure/BaseEntity.hpp"

class GrantedFile : public BaseEntity {
public:
    GrantedFile(std::string &path, std::vector<Role> granted_roles);
    std::string get_path();
    std::vector<Role> get_granted_roles();
    bool has_permission(Role role);
private:
    std::string path;
    std::vector<Role> granted_roles;
};


#endif //FTP_SERVER_GRANTEDFILE_HPP
