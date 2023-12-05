#include "UnorderedMapGraph.h"
#include <iostream>

void UnorderedMapGraph::addGame(const GameInfo& game) {
    adjList[game.console].push_back(game);
}

void UnorderedMapGraph::displayGamesForConsole(const std::string& console) const {
    auto it = adjList.find(console);
    if (it != adjList.end()) {
        std::cout << "Games for " << console << ":" << std::endl;
        for (const auto& game : it->second) {
            std::cout << "- " << game.gameName << " (Rating: " << game.rating << ")" << std::endl;
        }
    } else {
        std::cout << "No games found for " << console << std::endl;
    }
}

void UnorderedMapGraph::displayConsolesWithinBudget(float budget) const {
    std::unordered_map<std::string, int> consoleGameCounts;

    for (const auto& pair : adjList) {
        for (const auto& game : pair.second) {
            if (game.price <= budget) {
                consoleGameCounts[game.console]++;
            }
        }
    }

    if (!consoleGameCounts.empty()) {
        std::cout << "Consoles within budget:" << std::endl;
        for (const auto& pair : consoleGameCounts) {
            std::cout << "- " << pair.first << " (Games available: " << pair.second << ")" << std::endl;
        }
    } else {
        std::cout << "No consoles found within the given budget." << std::endl;
    }
}