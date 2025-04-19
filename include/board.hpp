#ifndef BOARD_HPP
#define BOARD_HPP

#include <ostream>
#include <tile.hpp>
#include <vector>

class Board{
    private:
    static constexpr int ROW{4}; // no. of rows in the panel
    static constexpr int COL{4}; // no. of colomuns in the panel
    const Tile x{Tile::EMPTY}; // an EMPTY tile
    Tile panel[ROW][COL]{
        {x, x, x, x},
        {x, x, x, x},
        {x, x, x, x},
        {x, x, x, x},
    };
    // pannel of 2d-array of tiles
    std::vector<Tile> tempTile; // temprory tiles to aid shuffling
    int toLinear(int row, int col) const;    // return linear index of a 2d array
    bool tileExists(int row, int col)const;  // verify the specified tile exist in the tile
    bool isOccupied(int row, int col) const;  // return false if EMPTY tile


    public:
    Board();
    bool moveTile(int row, int col); // move the [row][col]th tile from the panel
    void suffle();      // reposition the tile randomly
    bool solved();  // return true if puzzle is solved
    bool isAtCorrect(int ROW, int COL) const;  // check if the tile is at correct position
    
    Tile (&getTiles())[ROW][COL] { return panel;}
    int getRows() const { return ROW;}
    int getCols() const { return COL;};
    friend std::ostream& operator<<(std::ostream& output, const Board& board);
    
};

#endif
