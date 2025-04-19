#ifndef GAME_HPP
#define GAME_HPP

#include "board.hpp"
#include "button.hpp"

class Renderer;

class Game{

    private:
    void reset();

    Board board;
    int Minutes{0};
    int seconds{0};
    Button pauseButton;
    Button quitButton;
    int moveCount{0};

    void newGame();
    void pauseGame();
    void resumeGame();

    public:
    Game();
    friend Renderer;
    int getMovesCount();
    int getSeconds();
    int getMinutes();
    
};

#endif
