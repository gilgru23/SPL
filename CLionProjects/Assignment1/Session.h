#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <unordered_map>
#include <string>
#include "Action.h""

class User;
class Watchable;

class Session{
public:
    Session(const std::string &configFilePath);
    ~Session();
    void start();
    User* GetActiveUser() const;
    void AddActionToLog(BaseAction*);
    std::string& AddUser(std::string&, std::string&);
    const User* FindUser(std::string&);
    std::string& SwitchUser(std::string&);
    std::string& DeleteUser(std::string&);
    std::string& DuplicateUser(std::string&,std::string& new_name);


private:
    std::vector<Watchable*> content;
    std::vector<BaseAction*> actionsLog;
    std::unordered_map<std::string,User*> userMap;
    User* activeUser;
    void readData();
};
#endif
