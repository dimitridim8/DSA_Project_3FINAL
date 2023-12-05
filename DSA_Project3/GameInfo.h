#pragma once
#include <string>

class GameInfo {
public:
    std::string gameName;
    std::string console;
    std::string genre;
    std::string publisher;
    int year;
    float rating;
    float price;
    float globalSales; // Sales figure

    // Constructor
    GameInfo(std::string name, std::string cons, std::string gen,
             std::string pub, int yr, float rat, float prc, float gSales)
            : gameName(name), console(cons), genre(gen),
              publisher(pub), year(yr), rating(rat), price(prc), globalSales(gSales) {}
};
