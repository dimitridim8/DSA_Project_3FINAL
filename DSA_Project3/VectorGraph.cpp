#include "VectorGraph.h"
#include <algorithm>
#include <iostream>
// Helper function to filter games based on criteria

void VectorGraph::addGame(const GameInfo& game) {
    games.push_back(game);
}

std::vector<GameInfo> VectorGraph::filterGames(const std::string& genre, const std::string& publisher,
                                               const std::string& platform, int year) const {
    std::vector<GameInfo> filtered;

    for (const auto& game : games) {
        if ((genre.empty() || game.genre == genre) &&
            (publisher.empty() || game.publisher == publisher) &&
            (platform.empty() || game.console == platform) &&
            (year == 0 || game.year == year)) {
            filtered.push_back(game);
        }
    }

    return filtered;
}

// Helper function for flexible filtering
std::vector<GameInfo> VectorGraph::filterGamesFlexibly(const std::string& genre, const std::string& publisher,
                                                       const std::string& platform, int year) const {
    std::vector<GameInfo> filtered = filterGames(genre, publisher, platform, year);

    // If no exact matches, relax criteria
    if (filtered.empty()) {
        for (const auto& game : games) {
            if ((genre.empty() || game.genre == genre) ||
                (publisher.empty() || game.publisher == publisher) ||
                (platform.empty() || game.console == platform) ||
                (year == 0 || game.year == year)) {
                filtered.push_back(game);
            }
        }
    }

    return filtered;
}

void VectorGraph::sortAndDisplayGames(const std::vector<GameInfo>& filteredGames, bool globalPopularity) const {
    // Make a copy of the vector to sort
    std::vector<GameInfo> gamesToSort = filteredGames;

    // Sorting the games based on the specified criteria
    if (globalPopularity) {
        std::sort(gamesToSort.begin(), gamesToSort.end(),
                  [](const GameInfo& a, const GameInfo& b) {
                      return a.globalSales > b.globalSales; // Sorting in descending order of global sales
                  });
    }

    // Displaying the top 15 sorted games
    const size_t topN = 15; // Limit to top 15 games
    for (size_t i = 0; i < std::min(topN, gamesToSort.size()); ++i) {
        const auto& game = gamesToSort[i];
        std::cout << "Game: " << game.gameName << ", Console: " << game.console
                  << ", Year: " << game.year << std::endl;
    }
}

