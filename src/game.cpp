#include "game.hpp"
Game::Game(){
    pauseButton.setText("Pause");
    
    quitButton.setText("Quit");

    
}

void Game::newGame(){

}

void Game::pauseGame(){

}

void Game::resumeGame(){

}

int Game::getMovesCount(){
    return moveCount;
}

int Game::getSeconds(){
    return seconds;
}

int Game::getMinutes(){
    return Minutes;
}
