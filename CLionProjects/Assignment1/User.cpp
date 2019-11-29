//
// Created by gil on 20/11/2019.
//
#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
#include <limits>
#include "User.h"
#include "Session.h"
#include "Watchable.h"

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
//LengthRecommenderUser
LengthRecommenderUser::LengthRecommenderUser(const std::string &name) : User(name) {}

Watchable *LengthRecommenderUser::getRecommendation(Session &s) {
    std::vector<Watchable*>* NotSeen = UnWatched(s);
    int avg =GetHistoAvg();
    int i=0;
    int OutputI=i;
    int output=std::numeric_limits<int>::max();//initialize output with infinity
    while(NotSeen->at(i)!=nullptr)
    {
        int diff=NotSeen->at(i)->getLength()-avg;
        int abs(diff);//Math abs
        if(output>diff) {
            output = diff;
            OutputI=i;
        }

    }
    return NotSeen->at(OutputI);
}


//Rerun Algorithm
RerunRecommenderUser::RerunRecommenderUser(const std::string &name) : User(name) {}

Watchable *RerunRecommenderUser::getRecommendation(Session &s) {

}
//
GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name) {}
//
//aditional

int LengthRecommenderUser::GetHistoAvg() {
    int sum=0;
    int i=0;
    Watchable* temp= history.at(i);
    while(temp!=nullptr)
    {
        sum+=temp->getLength();
        i++;
        temp =history.at(i);
    }
    return sum/i;
}

std::vector<Watchable*>* LengthRecommenderUser::UnWatched(Session& s) {
    std::vector<Watchable *> *output = new std::vector<Watchable *>();
    int i = 0;
    while (s.getContent().at(i) != nullptr) {
        int j = 0;
        bool flag = true;
        while (history.at(j) != nullptr & flag) {
            if (history.at(i)->getId() == i)
                flag = false;
        }
        if (flag)
            output->push_back(s.getContent().at(i));
    }
    return output;
}
}
