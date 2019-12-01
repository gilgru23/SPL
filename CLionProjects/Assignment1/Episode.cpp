#include "Watchable.h"
#include "Session.h"


Episode::Episode(long id, const std::string& seriesName, int length, int season, int episode , const std::vector<std::string>& tags):
    Watchable(id,length,tags),seriesName(seriesName),season(season),
    episode(episode),nextEpisodeId(id+1){}


std::string Episode::toString() const
{
    std::string s = std::to_string(season);
    std::string e = std::to_string(episode);
    return seriesName+" S"+s+"E"+e;
}
Watchable* Episode::getNextWatchable(Session &s) const {
    return s.GetActiveUser()->getRecommendation(s);
}
 