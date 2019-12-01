#ifndef ACTION_H_
#define ACTION_H_

#include <string>
#include <iostream>

class Session;

enum ActionStatus{
	PENDING, COMPLETED, ERROR
};


class BaseAction{
public:
	BaseAction();

    BaseAction(const std::string &errorMsg);

    ActionStatus getStatus() const;
	virtual void act(Session& sess)=0;
	virtual std::string toString() const=0;
protected:
	void complete();
	void error(const std::string& errorMsg);
	std::string getErrorMsg() const;
private:
	std::string errorMsg;
	ActionStatus status;
};

class CreateUser  : public BaseAction {
public:
    virtual void act(Session &sess);
    CreateUser();
    CreateUser(std::string &, std::string &);
    virtual std::string toString() const;

private:
    std::string name;
    std::string algo_code;
};

class ChangeActiveUser : public BaseAction {
public:
    ChangeActiveUser();
    ChangeActiveUser(std::string&);
    virtual void act(Session& sess);
	virtual std::string toString() const;
private:
    std::string name;
};

class DeleteUser : public BaseAction {
public:

    DeleteUser();
    DeleteUser(std::string& name);
    virtual void act(Session & sess);
	virtual std::string toString() const;
private:
    std::string name;
};


class DuplicateUser : public BaseAction {
public:
    DuplicateUser(std::string&,std::string&);
	virtual void act(Session & sess);
	virtual std::string toString() const;
private:
    std::string old_name;
    std::string new_name;
};

class PrintContentList : public BaseAction {
public:
	virtual void act (Session& sess);
	virtual std::string toString() const;
};

class PrintWatchHistory : public BaseAction {
public:
	virtual void act (Session& sess);
	virtual std::string toString() const;
};


class Watch : public BaseAction {
public:
    Watch(long contentId);
	virtual void act(Session& sess);
	virtual std::string toString() const;
private:
    long contentId;
};


class PrintActionsLog : public BaseAction {
public:
	virtual void act(Session& sess);
	virtual std::string toString() const;
};

class Exit : public BaseAction {
public:
	virtual void act(Session& sess);
	virtual std::string toString() const;
};
#endif
