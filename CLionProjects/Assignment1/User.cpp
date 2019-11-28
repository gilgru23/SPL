//
// Created by gil on 20/11/2019.
//
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include "User.h"

User::User(const std::string &name):
name(name),history(std::vector<Watchable*>())
{}

std::string User::getName()const
{
    return name;
}
std::vector<Watchable*> User::get_history() const
{
    return history;
}

User *User::Copy(User& other ) {
    std::vector<Watchable*>::iterator ptr;
    for (ptr= other.history.begin();ptr< other.history.end();ptr++)
    {
        history.push_back(*ptr);
    }
}
GenreRecommenderUser* GenreRecommenderUser::GetCopy(std::string &name)
{
    GenreRecommenderUser* temp = new GenreRecommenderUser(name);
    temp->Copy(*this);
    return temp;
}
RerunRecommenderUser* RerunRecommenderUser::GetCopy(std::string &name)
{
    RerunRecommenderUser* temp = new RerunRecommenderUser(name);
    temp->Copy(*this);
    return temp;
}
LengthRecommenderUser* LengthRecommenderUser::GetCopy(std::string &name) {
    LengthRecommenderUser* temp = new LengthRecommenderUser(name);
    temp->Copy(*this);
    return temp;
}
