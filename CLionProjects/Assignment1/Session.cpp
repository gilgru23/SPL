
#include "Session.h"
#include <iostream>
#include <fstream>
#include "Watchable.h"
#include "json.hpp"
#include "User.h"
using namespace std;
using string=std::string;
using json = nlohmann::json;


Session::Session(const std::string &configFilePath):
        content(std::vector<Watchable*>()),actionsLog(std::vector<BaseAction*>()),
        userMap(std::unordered_map<std::string,User*>())
{
    //check about "activeUser"
    readData();
}

User* Session::GetActiveUser() const  {
    return activeUser;
}

void Session::readData() {
    std::ifstream ifs("config1.json");
    json j = json::parse(ifs);
    /*
    for(int i=3;i>=0;i++)
    {
        content.push_back(new Movie(3-i+1,j["movie"][i]["name"],j["movie"][i]["length"],j["movie"][i]["tags"]));
    }
    content.push_back(new Episode(1,j["tv_series"][0]["name"],j["tv_series"][0]["episode_length"],4,))
**/
    int idx=0;
    while(j["movies"][idx]!=nullptr)
    {
        int tag=0;
        vector<std::string> tags;
        while(j["movies"][idx]["tags"][tag]!= nullptr)
        {
            tags.push_back(j["movies"][idx]["tags"][tag]);
            tag++;
        }
        content.push_back(new Movie(idx,j["movies"][idx]["name"],j["movies"][idx]["length"],tags));
        idx++;
    }
    int inx =0;
    while(j["tv_series"][inx]!=nullptr)
    {
        int tag=0;
        vector<std::string> tags;
        while(j["tv_series"][inx]["tags"][tag]!= nullptr)
        {
            tags.push_back(j["tv_series"][inx]["tags"][tag]);
            tag++;
        }
        string series_name = j["tv_series"][inx]["name"];
        int length = j["tv_series"][inx]["episode_length"];

        Episode* last;
        int season=0;
        while(j["tv_series"][inx]["seasons"][season]!=nullptr)
        {
            int s_size = j["tv_series"][inx]["seasons"][season];
            for(int e=0;e<s_size;e++)
            {
                last = new Episode(idx,series_name,length,season,e,tags);
               idx++;
            }
            season++;
        }
        inx++;
        if(last != nullptr)
            last->SetNextEpId(-1);
    }
}

void Session::AddActionToLog(BaseAction * action) {
    actionsLog.push_back(action);
}

std::string Session::AddUser( std::string & name, std::string & algo) {
    std::string err="";
    if(FindUser(name)!= nullptr)
    {
        if(algo.compare("len")==0)
            userMap.insert({name,new LengthRecommenderUser(name)});
        if(algo.compare("rer")==0)
            userMap.insert({name,new RerunRecommenderUser(name)});
        if(algo.compare("gen")==0)
            userMap.insert({name,new GenreRecommenderUser(name)});
        else
        {
            err="ERROR: illegal recommendation algorithem code";
        }
    }
    else
        err="ERROR:name is already used";
    return err;
}

const User *Session::FindUser(std::string & name) {
    User* output= nullptr;
    try
    {
        output = userMap.at(name);
    }
    catch (const out_of_range &e)
    {}
    return output;
}

std::string Session::SwitchUser(std::string & name) {
    std::string err="";
    User* temp= nullptr;
    try
    {
        temp = userMap.at(name);
    }
    catch (const out_of_range &e)
    {}
    if (temp!= nullptr)
    {
        activeUser=temp;
    }
    else
        err="ERROR: no such user ["+name+"]";
    return err;
}

std::string Session::DeleteUser(std::string & name) {
    std::string err="";
    if(userMap.erase(name)==0)
        err ="ERROR: The Deletion failed";
    return err;
}

std::string Session::DuplicateUser(std::string &original_name, std::string &new_name) {
    std::string err="";
    User* new_user= nullptr;
    try
    {
        new_user = userMap.at(original_name)->GetCopy(new_name);
        userMap.insert({new_name,new_user});
    }
    catch (const out_of_range &e)
    {
        err="ERROR: no such user ["+original_name+"]";
    }
    return err;
}



