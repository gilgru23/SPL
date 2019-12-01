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

using string=std::string;
using vectorSt= std::vector<string>;

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

void User::watchContent(Watchable* w) {
    history.push_back(w);
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
    std::vector<Watchable*>* NotSeen = UnWatched(s);//**do it more efficiently
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
        i++;
    }
    return NotSeen->at(OutputI);
}


//Rerun AlgorithmRerunIndex=0
RerunRecommenderUser::RerunRecommenderUser(const std::string &name) : User(name), RerunIndex(0) {}

Watchable *RerunRecommenderUser::getRecommendation(Session &s) {
    Watchable* output=history.at(RerunIndex);
    RerunIndex=(RerunIndex+1)%(history.size());
    return output;
}
//GenreRecommenderUser
GenreRecommenderUser::GenreRecommenderUser(const std::string &name) : User(name),
tagsCount(new  std::map<std::string,int>()) {}

Watchable *GenreRecommenderUser::getRecommendation(Session &s) {

    // find most popular tag in users history
    std::map<std::string,int>::iterator ptr = tagsCount->begin();
    std::string tagName = ptr->first;
    int v=ptr->second;
    ptr++;
    while (ptr!= tagsCount->end())
    {
        if (ptr->second > v)
        {
            v=ptr->second;
            tagName=ptr->first;
        }
        ptr++;
    }

    // find first unwatched content with same tag
    std::vector<Watchable*>  content= *UnWatched(s);
    std::vector<Watchable*>::iterator p;
    for (p=content.begin();p<content.end();p++)
    {
        vectorSt tags = (*p)->getTags();
        vectorSt::iterator itr= tags.begin();
        for(itr;itr<tags.end();itr++)
        {
            if(tagName.compare(*itr)==0)
                return *p;
        }
    }
    return 0;
}

void GenreRecommenderUser::watchContent(Watchable *w) {
    User::watchContent(w);
    std::vector<std::string> tags = w->getTags();
    std::vector<std::string>::iterator ptr;
    for (ptr = tags.begin(); ptr < tags.end(); ptr++)
    {
        try {
            tagsCount->at(*ptr)++;
        }
        catch(const std::out_of_range& oor)
        {
            tagsCount->insert({*ptr,1});
        }
    }
}
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

std::vector<Watchable*>* User::UnWatched(Session& s) {
    std::vector<Watchable *> *output = new std::vector<Watchable *>();
    int i = 0;
    while (s.getContent().at(i) != nullptr) {
        int j = 0;
        bool flag = true;
        while (history.at(j) != nullptr & flag) {
            if (history.at(i)->getId() == i)
                flag = false;
                j++;

        if (flag)
            output->push_back(s.getContent().at(i));
        i++;
    }
    return output;
}
}
