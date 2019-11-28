//
// Created by gil on 22/11/2019.
//
#include <fstream>
#include "Watchable.h";

Movie::Movie(long id, const std::string& name, int length, const std::vector<std::string>& tags):
        name(name),Watchable(id,length,tags)
{}
std::string Movie::toString() const
{
    return name;
}
Watchable* getNextWatchable(Session&)
{

}
