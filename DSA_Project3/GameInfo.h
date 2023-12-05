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
    float globalSales; // Added
    float naSales;     // Added
    float euSales;     // Added
    float jpSales;     // Added

    // Update constructor accordingly
    GameInfo(std::string name, std::string cons, std::string gen,
             std::string pub, int yr, float rat, float prc,
             float gSales, float na, float eu, float jp)
            : gameName(name), console(cons), genre(gen),
              publisher(pub), year(yr), rating(rat), price(prc),
              globalSales(gSales), naSales(na), euSales(eu), jpSales(jp) {}
};