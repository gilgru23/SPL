#ifndef USER_H_
#define USER_H_

#include <vector>
#include <string>
#include <unordered_set>
#include <unordered_map>
class Watchable;
class Session;

class User{
public:
    User(const std::string& name);
    virtual User* GetCopy(std::string& name)=0;
    virtual Watchable* getRecommendation(Session& s) = 0;
    std::string getName() const;
    std::vector<Watchable*> get_history() const;
protected:
    std::vector<Watchable*> history;
    virtual User* Copy(User& other);
private:
    const std::string name;

};


class LengthRecommenderUser : public User {
public:
    LengthRecommenderUser(const std::string& name);
    LengthRecommenderUser(const LengthRecommenderUser &);
    LengthRecommenderUser* GetCopy(std::string& name);
    virtual Watchable* getRecommendation(Session& s);
    LengthRecommenderUser(LengthRecommenderUser*);
    int GetHistoAvg();
    std::vector<Watchable*>* UnWatched(Session&);




private:
};

class RerunRecommenderUser : public User {
public:
    RerunRecommenderUser(const std::string& name);
    RerunRecommenderUser(const
                         RerunRecommenderUser(const std::string &name);

     RerunRecommenderUser &);
    RerunRecommenderUser* GetCopy(std::string& name);
    virtual Watchable* getRecommendation(Session& s);
private:
     int RerunIndex;
};
class GenreRecommenderUser : public User {
public:
    GenreRecommenderUser(const std::string& name);
    GenreRecommenderUser(const
                         GenreRecommenderUser(const std::string &name);

    GenreRecommenderUser* GetCopy(std::string& name);
    virtual Watchable* getRecommendation(Session& s);
private:
};

#endif
