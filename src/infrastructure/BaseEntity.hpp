//
// Created by mahdi on 27/03/2022.
//

#ifndef FTP_SERVER_BASEENTITY_HPP
#define FTP_SERVER_BASEENTITY_HPP


class BaseEntity {
public:
    virtual void set_id(int _id);

    [[nodiscard]] virtual int get_id() const;

protected:
    int id = 0;
};


#endif //FTP_SERVER_BASEENTITY_HPP
