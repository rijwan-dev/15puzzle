#include "tile.hpp"
#include <stdexcept>
#include <string_view>
Tile::Tile(TileID tileID): id(tileID){
    if( tileID < EMPTY || tileID > MAX){
        throw std::out_of_range("TileID is expected between EMPTY to FIFTEEN!");
    }
}

Tile::TileID Tile::getID() const {
    return id;
}

std::string_view Tile::getLabel() const {
    // Create a static lookup table. It must match the order of your enum.
    static constexpr std::string_view labels[] = {
        " ",  "1",  "2",  "3",  "4",
        "5",  "6",  "7",  "8",  "9",
        "10", "11", "12", "13", "14",
        "15"
    };


    return labels[id];
}

