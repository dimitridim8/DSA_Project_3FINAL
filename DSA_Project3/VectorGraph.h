#pragma once
#include "GameInfo.h"
#include <vector>
#include <string>

class VectorGraph {
private:
    std::vector<GameInfo> games;

public:
    void addGame(const GameInfo& game);
    void sortGames(); // Method to sort games

    // Method to filter games based on criteria
    std::vector<GameInfo> filterGames(const std::string& genre, const std::string& publisher,
                                      const std::string& platform, int year) const;

    // Method for flexible filtering
    std::vector<GameInfo> filterGamesFlexibly(const std::string& genre, const std::string& publisher,
                                              const std::string& platform, int year) const;

    // Method to sort and display games
    void sortAndDisplayGames(const std::vector<GameInfo>& games, bool globalPopularity) const;
};
