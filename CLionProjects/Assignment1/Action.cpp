//
// Created by gil on 27/11/2019.
//

#include "Action.h"
#include "Session.h"

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

