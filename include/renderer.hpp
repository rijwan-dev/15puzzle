#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <atomic>
#include <thread>
#include "button.hpp"
#include "game.hpp"

class Renderer{

    private:
    void run();

    Game *m_game;

    public:
    Renderer(Game& board);
    ~Renderer();
    void drawButton(Button button) const;
    void drawBoard();

    std::atomic<bool> timer_running; // Flag to indicate if the timer is running
    std::thread timerThread; // Thread for the timer
    void timer();
    void startTimer();
    void stopTimer();
    std::mutex mutex;


};

#endif
