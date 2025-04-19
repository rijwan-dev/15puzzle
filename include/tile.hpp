#ifndef TILE_HPP
#define TILE_HPP

#include <string_view>


class Tile {

   public:
    enum TileID {
        EMPTY, ONE, TWO, THREE, FOUR,
        FIVE, SIX, SEVEN, EIGHT, NINE,
        TEN, ELEVEN, TWELVE, THIRTEEN,
        FOURTEEN, FIFTEEN, MAX,
    };

   private:
    TileID id;  // ID of the tile ie, count
    
    public:
    Tile(TileID tileID); // initialize the tile
    std::string_view getLabel() const;    // return label of the tile
    TileID getID() const; // return tileID
};

#endif
