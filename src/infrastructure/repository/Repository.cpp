#include <algorithm>
#include "Repository.hpp"

BaseEntity *Repository::insert(BaseEntity *value) {
    value->set_id(get_next_id());
    store.insert(std::make_pair(value->get_id(), value));
    return value;
}

BaseEntity *Repository::update(BaseEntity *value) {
    store.insert(std::make_pair(value->get_id(), value));
    return value;
}

void Repository::remove(int id) {
    store.erase(id);
}

std::list<BaseEntity *> Repository::get_all() {
    std::list<BaseEntity *> result;
    for (auto &item: store) {
        result.push_back(item.second);
    }
    return result;
}

int Repository::get_next_id() {
    auto values = get_all();
    if (values.empty()) {
        return 1;
    }
    auto max = std::max_element(values.begin(), values.end(), [](const BaseEntity *a,
                                                                 const BaseEntity *b) {
        return a->get_id() < b->get_id();
    });
    return (*max)->get_id() + 1;
}
