#include "Action.h"
#include "Session.h"
#include "Watchable.h"
#include "User.h"
using string=std::string;

void BaseAction::complete()
{
    status=ActionStatus::COMPLETED;
}

void BaseAction::error(const std::string &_errorMsg)
{
    status=ActionStatus::ERROR;
    errorMsg=_errorMsg;
}

void CreateUser::act(Session &sess) {
    sess.AddActionToLog(this);
    std::string err= sess.AddUser(name,algo_code);
    if (err.length()==0)
    {
        complete();
    }
    else
    {
        error(err);
    }
}

CreateUser::CreateUser(std::string & name, std::string &algo_code):
        name(name),algo_code(algo_code){}

void ChangeActiveUser::act(Session &sess) {
    sess.AddActionToLog(this);
    std::string err=sess.SwitchUser(name);
    if (err.length()==0)
    {
        complete();
    }
    else
    {
        error(err);
    }
}

ChangeActiveUser::ChangeActiveUser(std::string& name):
        name(name) {}

BaseAction::BaseAction(const std::string &errorMsg):
status(ActionStatus::PENDING){}

DeleteUser::DeleteUser(std::string& name):
        name(name) {}

void DeleteUser::act(Session &sess) {
    sess.AddActionToLog(this);
    std::string err=sess.DeleteUser(name);
    if (err=="")
        complete();
    else
        error(err);
}

DuplicateUser::DuplicateUser(std::string & oldName, std::string & newName):
        old_name(oldName),new_name(newName){}

void DuplicateUser::act(Session &sess) {
    sess.AddActionToLog(this);
    std::string err=sess.DuplicateUser(old_name,new_name);
    if (err=="")
        complete();
    else
        error(err);
}
//Watch
Watch::Watch(long contentId) : contentId(contentId) {}

void Watch::act(Session &sess)
{
    sess.AddActionToLog(this);
    Watchable *w = sess.getContent().at(contentId);
    User*  u = sess.GetActiveUser();
    u->watchContent(w);
    Watchable *nextW = u->getRecommendation(sess);

    string recLine="We recommend watching "+nextW->toString()+", continue watching? [y/n]";
    std::cout<<recLine;

    bool ans=false;
    string input;
    while(ans==false){
        std::cin>>input;
        if (input=="y")
        {
            ans=true;

            Watch* watchNext = new Watch((*nextW).getId());
            watchNext->act(sess);
        }
        else if(input=="n")
        {
            ans=true;
        }
        else
            std::cout<<recLine;
    }
}
