#include "board.hpp"
#include <algorithm>
#include <iostream>
#include <ncurses.h>
#include <random>
#include <stdexcept>
#include <utility>
#include <vector>
#include "tile.hpp"

Board::Board(){
    suffle();
}


// suffle the tiles and place it the 2d array
void Board::suffle(){
    std::vector<Tile::TileID> id;
    for (int i{0}; i < 16; i++) {
        id.push_back( static_cast<Tile::TileID>( i ) );
    }

    std::random_device rd;
    std::mt19937 eng( rd() );
    std::shuffle(id.begin(), id.end(), eng);

    std::cout << id.size();
   
    if( id.size() != (ROW * COL)){
        throw std::runtime_error("Failed to generate temprory tile objects to suffle");
    }
    
    for (int i{0}; i < ROW; ++i) {
       for (int j(0); j < COL; ++j){
            panel[i][j] = id.back();
            id.pop_back();
       }
    }
}

bool Board::moveTile(int row, int col){
    if ( !tileExists(row, col)) {
        throw std::out_of_range("invalid tile! valid row and col is between 0 - 3.\n");
    }

    if (tileExists(row - 1,col) && !isOccupied(row - 1, col)) {
        // upper tile
        std::swap(panel[row][col], panel[row-1][col]);
        return true;

    }else if ( tileExists(row + 1,col) && !isOccupied(row + 1, col) ) {
        // lower tile
        std::swap(panel[row][col], panel[row+1][col]);
        return true;

    }else if ( tileExists(row, col-1) && !isOccupied(row, col-1)) {
        // left tile
        std::swap(panel[row][col], panel[row][col-1]);
        return true;

    }else if ( tileExists(row, col+1) && !isOccupied(row, col+1) ) {
        // right tile
        std::swap(panel[row][col], panel[row][col+1]);
        return true;

    }else {
        // unable to move
    }
    return false;
}


bool Board::solved(){
    bool status{false};
    for (int i{0}; i < ROW; ++i) {
        for (int j{0}; j < COL-1 ; ++j) {
            if( isAtCorrect(i, j) && isOccupied(i, j) ){
               status = true;
            }else {
                status = false;
            }
        }
    }
    return status;
}

bool Board::isAtCorrect(int row, int col) const{
    if( panel[row][col].getID() == toLinear(row, col)){
        return true;
    }
    return false;
}

// not a member of Board class
std::ostream& operator<<(std::ostream& output, const Board& board){

    for (int i{0}; i < board.ROW; ++i) {
        for (int j{0}; j < board.COL; ++j) {
            if(board.isAtCorrect(i,j)){

                output << "*" << board.panel[i][j].getLabel() << '\t';
            }else {
                output << board.panel[i][j].getLabel() << '\t';
            }
        }
        output << '\n';
    }
    output << '\n';

    return output;
}

int Board::toLinear(int row, int col) const {
    // convert 2d array index into linear index
    return (col+1) + (row*4);
}

bool Board::isOccupied(int row, int col) const {
    
    if( !tileExists(row, col) ){
       throw std::out_of_range("Out of range acess! valid tile (0-3) col and row\n");
    }

    if( panel[row][col].getID() == Tile::EMPTY ){
        return false;
        // tile is EMPTY
    }else {
        return true;
    }
}

bool Board::tileExists(int row, int col)const {
    if (row < ROW && col < COL && col >= 0 && row >= 0) {
        return true;
    }
    return false;
}
