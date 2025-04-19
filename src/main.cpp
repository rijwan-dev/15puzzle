
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ncurses.h>
#include <sys/select.h>
#include "renderer.hpp"
#include "game.hpp"

int main(){


    Game mygame;
    Renderer renderer(mygame);
    renderer.~Renderer();

    std::cout << "Moves: " << ":" << mygame.getMovesCount() << "\n";
    std::cout << mygame.getMinutes() << ":" << mygame.getSeconds() << "\n";

    return 0;
}
