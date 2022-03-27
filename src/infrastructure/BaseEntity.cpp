#include "BaseEntity.hpp"

void BaseEntity::set_id(int _id) {
    this->id = _id;
}

int BaseEntity::get_id() const {
    return this->id;
}
