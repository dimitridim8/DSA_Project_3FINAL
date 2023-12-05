#pragma once
#include "GameInfo.h"
#include <vector>
#include <algorithm>
#include <iostream>

class VectorGraph {
private:
    std::vector<GameInfo> games;

public:
    void addGame(const GameInfo& game);
    void sortGames();
    void displayGames() const;
    void filterAndDisplayTopGames(const std::string& region, bool globalPopularity) const;
    std::vector<GameInfo> filterGames(const std::string& genre, const std::string& publisher,
                                      const std::string& platform, int year) const;
    void sortAndDisplayGames(const std::vector<GameInfo>& filteredGames, bool globalPopularity) const;
    std::vector<GameInfo> filterGamesFlexibly(const std::string& genre, const std::string& publisher,
                                              const std::string& platform, int year) const;
};
