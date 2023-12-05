#include "GameInfo.h"
#include <unordered_map>
#include <list>
#include <string>

class UnorderedMapGraph {
private:
    std::unordered_map<std::string, std::list<GameInfo>> adjList;

public:
    void addGame(const GameInfo& game);
    void displayGamesForConsole(const std::string& console) const;
    void displayConsolesWithinBudget(float budget) const;
};
