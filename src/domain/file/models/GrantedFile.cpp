#include "GrantedFile.hpp"

GrantedFile::GrantedFile(std::string &path, std::vector<Role> granted_roles) {
    this->path = path;
    this->granted_roles = std::move(granted_roles);
}

std::string GrantedFile::get_path() {
    return this->path;
}

std::vector<Role> GrantedFile::get_granted_roles() {
    return this->granted_roles;
}

bool GrantedFile::has_permission(Role role) {
    return std::any_of(granted_roles.begin(), granted_roles.end(), [&](Role r) {
        return r == role;
    });
}
