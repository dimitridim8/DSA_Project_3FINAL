#include "VectorGraph.h"

void VectorGraph::addGame(const GameInfo& game) {
    games.push_back(game);
}

void VectorGraph::sortGames() {
    std::sort(games.begin(), games.end(), [](const GameInfo& a, const GameInfo& b) {
        return a.rating > b.rating; // Sorting in descending order of rating
    });
}

void VectorGraph::displayGames() const {
    for (const auto& game : games) {
        std::cout << "Game: " << game.gameName << ", Console: " << game.console
                  << ", Rating: " << game.rating << std::endl;
    }
}

void VectorGraph::filterAndDisplayTopGames(const std::string& region, bool globalPopularity) const {
    std::vector<GameInfo> sortedGames = games;

    std::sort(sortedGames.begin(), sortedGames.end(), [&region, globalPopularity](const GameInfo& a, const GameInfo& b) {
        if (globalPopularity) {
            return a.globalSales > b.globalSales;
        } else {
            if (region == "NA") {
                return a.naSales > b.naSales;
            } else if (region == "EU") {
                return a.euSales > b.euSales;
            } else if (region == "JP") {
                return a.jpSales > b.jpSales;
            }
            return false;
        }
    });

    const size_t topN = 10; 
    for (size_t i = 0; i < std::min(topN, sortedGames.size()); ++i) {
        const auto& game = sortedGames[i];
        std::cout << "Game: " << game.gameName << ", Console: " << game.console
                  << ", Year: " << game.year << ", Rating: " << game.rating << std::endl;
    }
}

std::vector<GameInfo> VectorGraph::filterGames(const std::string& genre, const std::string& publisher,
                                               const std::string& platform, int year) const {
    std::vector<GameInfo> filteredGames;
    for (const auto& game : games) {
        if ((genre.empty() || game.genre == genre) &&
            (publisher.empty() || game.publisher == publisher) &&
            (platform.empty() || game.console == platform) &&
            (year == 0 || game.year == year)) {
            filteredGames.push_back(game);
        }
    }
    return filteredGames;
}

void VectorGraph::sortAndDisplayGames(const std::vector<GameInfo>& filteredGames, bool globalPopularity) const {
    std::vector<GameInfo> sortedGames = filteredGames;

    std::sort(sortedGames.begin(), sortedGames.end(), [globalPopularity](const GameInfo& a, const GameInfo& b) {
        if (globalPopularity) {
            return a.globalSales > b.globalSales;
        } else {
            return (a.naSales + a.euSales + a.jpSales) > (b.naSales + b.euSales + b.jpSales);
        }
    });

    const size_t topN = 10; 
    for (size_t i = 0; i < std::min(topN, sortedGames.size()); ++i) {
        const auto& game = sortedGames[i];
        std::cout << "Game: " << game.gameName << ", Console: " << game.console
                  << ", Year: " << game.year << std::endl;
    }
}

std::vector<GameInfo> VectorGraph::filterGamesFlexibly(const std::string& genre, const std::string& publisher,
                                                       const std::string& platform, int year) const {
    std::vector<GameInfo> filteredGames = filterGames(genre, publisher, platform, year);

    if (filteredGames.empty() && year != 0) {
        std::cout << "Expanding search to include all years..." << std::endl;
        filteredGames = filterGames(genre, publisher, platform, 0);
    }

    return filteredGames;
}
