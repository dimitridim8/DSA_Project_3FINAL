#include "UnorderedMapGraph.h"
#include "VectorGraph.h"
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include <limits>

void loadFromCSV(const std::string& filepath, UnorderedMapGraph& umGraph, VectorGraph& vGraph) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return;
    }

    std::string line, temp;
    std::string gameName, console, genre, publisher;
    int year;
    float naSales, euSales, jpSales, otherSales, globalSales;

    std::getline(file, line); // Skipping the header line

    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::getline(ss, temp, ','); // Skip Rank
        std::getline(ss, gameName, ',');
        std::getline(ss, console, ',');
        std::getline(ss, temp, ','); // For Year

        try {
            year = temp.empty() ? 0 : std::stoi(temp);
        } catch (const std::exception& e) {
            year = 0; // Set year to 0 if conversion fails
        }

        std::getline(ss, genre, ',');
        std::getline(ss, publisher, ',');

        // Read and parse sales data
        ss >> naSales >> euSales >> jpSales >> otherSales >> globalSales;

        GameInfo game(gameName, console, genre, publisher, year, 0.0f /*rating*/, 0.0f /*price*/, globalSales, naSales, euSales, jpSales);
        umGraph.addGame(game);
        vGraph.addGame(game);
    }
}


void consoleAdvice(float budget) {
    std::cout << "Consoles within your budget range:" << std::endl;

    if (budget <= 250) {
        std::cout << "- Refurbished Xbox One\n"
                  << "- Refurbished Playstation 4\n"
                  << "- Nintendo Wii\n"
                  << "- Nintendo Wii U\n"
                  << "- Xbox 360\n"
                  << "- Playstation 3\n";
    }
    else if (budget > 250 && budget <= 500) {
        std::cout << "- Xbox Series X/S\n"
                  << "- Playstation 5\n"
                  << "- Nintendo Switch\n"
                  << "- Refurbished Xbox One\n"
                  << "- Refurbished Playstation 4\n"
                  << "- Nintendo Wii\n"
                  << "- Nintendo Wii U\n"
                  << "- Xbox 360\n"
                  << "- Playstation 3\n";
    }
    else {  // budget > 500
        std::cout << "- Any Console\n"
                  << "- PC\n";
    }
}

bool getYesOrNoInput(const std::string& prompt) {
    std::string input;
    while (true) {
        std::cout << prompt << " (yes/no): ";
        std::getline(std::cin, input);

        if (input == "yes") {
            return true;
        } else if (input == "no") {
            return false;
        } else {
            std::cerr << "Invalid input. Please enter 'yes' or 'no'." << std::endl;
        }
    }
}

void gameAdvice(VectorGraph& vGraph) {
    std::string genre, publisher, platform, popularityPreference;
    int year;
    bool globalPopularity;

    std::cout << "Game Selection Preferences\n";

    std::cout << "Enter game genre (Action, Platform, Racing, Role-Playing, Puzzle, Sports, Simulation, Shooter, Misc, Fighting, Adventure): ";
    std::getline(std::cin, genre);

    std::cout << "Enter game publisher (Nintendo, Electronic Arts, Take-Two Interactive, Sony Computer Entertainment, Microsoft Game Studios, Ubisoft, Sega, Activision, Capcom, Atari): ";
    std::getline(std::cin, publisher);

    std::cout << "Enter platform (Wii, NES, DS, GB, GBA, PS2, PS3, PS4, PSP, PC, Xbox 360, XOne, 3DS): ";
    std::getline(std::cin, platform);

    std::cout << "Enter year of release (1980-2023): ";
    std::string yearInput;
    std::getline(std::cin, yearInput);

    try {
        year = std::stoi(yearInput);
        if (year < 1980 || year > 2023) {
            std::cerr << "Year out of range. Please enter a year between 1980 and 2023." << std::endl;
            return; // Exit the function if year is out of range
        }
    } catch (const std::exception& e) {
        std::cerr << "Invalid input for year: " << e.what() << std::endl;
        return; // Exit the function if input is invalid
    }

    auto filteredGames = vGraph.filterGames(genre, publisher, platform, year);

    if (filteredGames.empty()) {
        std::cout << "No games found matching your exact criteria. Expanding search..." << std::endl;
        filteredGames = vGraph.filterGamesFlexibly(genre, publisher, platform, year);
    }

    if (filteredGames.empty()) {
        std::cout << "Sorry, no games found matching your criteria." << std::endl;
    } else {
        vGraph.sortAndDisplayGames(filteredGames, globalPopularity);
    }
}


void combinedAdvice(UnorderedMapGraph& umGraph, VectorGraph& vGraph, float budget) {
    consoleAdvice(budget);  // Pass the budget to consoleAdvice
    gameAdvice(vGraph);     // No change here
}


int main() {
    UnorderedMapGraph umGraph;
    VectorGraph vGraph;

    std::string filepath = "vgsales.csv";
    loadFromCSV(filepath, umGraph, vGraph);

    std::string budgetInput, region, network, preference;
    float budget = 0.0f;

    std::cout << "Welcome to the Video Games Visualizer" << std::endl;

    std::cout << "Please enter your budget: ";
    std::getline(std::cin, budgetInput);

    try {
        budget = std::stof(budgetInput);
    } catch (const std::invalid_argument& e) {
        std::cerr << "Invalid input for budget. Please enter a valid number." << std::endl;
        return 1; // or handle it differently
    } catch (const std::out_of_range& e) {
        std::cerr << "Input for budget is out of range. Please enter a smaller number." << std::endl;
        return 1; // or handle it differently
    }

    std::cout << "What region are you in? (NA, EU, JP): ";
    std::getline(std::cin, region);

    std::cout << "Do you have a preferred network? (Playstation Network, Xbox Live, Nintendo Online, None): ";
    std::getline(std::cin, network);

    std::cout << "Are you looking for a 'console' or 'game' or 'both'? ";
    std::getline(std::cin, preference);

    if (preference == "game") {
        gameAdvice(vGraph);
    } else if (preference == "console") {
        consoleAdvice(budget);
    } else if (preference == "both") {
        combinedAdvice(umGraph, vGraph, budget);
    } else {
        std::cout << "Invalid preference entered." << std::endl;
    }

    return 0;
}