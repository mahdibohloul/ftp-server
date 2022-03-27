//
// Created by mahdi on 27/03/2022.
//

#ifndef FTP_SERVER_REPOSITORY_HPP
#define FTP_SERVER_REPOSITORY_HPP

#include <map>
#include "list"
#include "../BaseEntity.hpp"

class Repository {
public:
    virtual BaseEntity *insert(BaseEntity *value);

    virtual BaseEntity *update(BaseEntity *value);

    virtual void remove(int id);

    virtual std::list<BaseEntity *> get_all();

protected:
    int get_next_id();

    std::map<int, BaseEntity *> store;
};


#endif //FTP_SERVER_REPOSITORY_HPP
