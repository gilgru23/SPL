//
// Created by gil on 20/11/2019.
//
#include "Watchable.h"
Watchable::Watchable(long id, int length, const std::vector<std::string> &tags):
    id(id),length(length),tags(tags){}

int Watchable::getLength() const {
    return length;


}

long Watchable::getId() const {
    return id;
}



