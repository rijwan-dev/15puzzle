#include "renderer.hpp"
#include <cstdio>
#include <mutex>
#include <ncurses.h>
#include <cstring>  // For strlen
#include <string>
#include "board.hpp"
#include "button.hpp"
#include "game.hpp"

Renderer::Renderer(Game &game) : m_game(&game) {
    // Start ncurses mode
    initscr();
    cbreak();              // Disable line buffering
    noecho();              // Don't show typed characters
    keypad(stdscr, TRUE);  // Enable reading function keys and arrow keys
    curs_set(0);           // Hide the cursor

    // Enable mouse events including mouse movement reporting
    mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, nullptr);

    // Enable color if supported
    if (has_colors()) {
        start_color();
        // Define color pairs: foreground and background for each state
        init_pair(1, COLOR_WHITE, COLOR_GREEN);  // Normal state
        init_pair(2, COLOR_BLACK, COLOR_WHITE);  // Hovered state
        init_pair(3, COLOR_WHITE, COLOR_BLUE);   // Clicked state
        init_pair(4, COLOR_GREEN, COLOR_CYAN);
    }

    // draw the quit button
    m_game->quitButton.setDemension(14, 1);
    m_game->quitButton.setOrigin(2, 18);
    m_game->quitButton.setText(m_game->quitButton.getLabel() + "(q)");
    drawButton(m_game->quitButton);
    drawBoard();
    mvprintw(16, 3, "Move: %d", m_game->getMovesCount());
    mvprintw(17, 3, "Time %02d:%02d", m_game->Minutes, m_game->seconds);
    refresh();
    startTimer();
    run();
}

Renderer::~Renderer() {
    stopTimer();
    endwin();
}

void Renderer::drawButton(Button button) const {
    int color_pair = 1;

    if (button.getState() == Button::HOVERED) {
        color_pair = 2;
    } else if (button.getState() == Button::CLICKED) {
        color_pair = 3;
    } else if (button.getState() == Button::DISABLED) {
        color_pair = 4;
    }
    // Set the color attributes for the button area
    attron(COLOR_PAIR(color_pair));
    // Fill the button area with spaces (no visible border)
    for (int i = 0; i < button.getHeight(); i++) {
        mvhline(button.getY() + i, button.getX(), ' ', button.getWidth());
    }
    // Calculate position to center the button text
    int text_start =
        button.getX() + (button.getWidth() - button.getLabel().size()) / 2;
    // Draw the button text in the center row of the button
    mvprintw(button.getY() + button.getHeight() / 2, text_start, "%s",
             button.getLabel().c_str());
    attroff(COLOR_PAIR(color_pair));
    refresh();
}

void Renderer::drawBoard() {
    Button tempButton;
    tempButton.setDemension(7, 3);

    for (int i{0}; i < 4; ++i) {
        for (int j{0}; j < 4; ++j) {
            if (m_game->board.getTiles()[i][j].getID() == Tile::EMPTY) {
                tempButton.setState(Button::DISABLED);
            } else if (m_game->board.getTiles()[i][j].getID() ==
                       ((i + 1) + (j * 4))) {
                tempButton.setState(Button::HOVERED);
            } else {
                tempButton.setState(Button::NORMAL);
            }
            tempButton.setText(static_cast<std::string>(
                m_game->board.getTiles()[i][j].getLabel()));
            tempButton.setOrigin((i * 9), j * 4);
            drawButton(tempButton);
        }
    }
}

void Renderer::startTimer() {
    timer_running = true;
    timerThread = std::thread(&Renderer::timer, this);
    timerThread.detach();

}

void Renderer::timer() {
    while (timer_running) {
        std::this_thread::sleep_for(
            std::chrono::seconds(1));  // Wait for 1 second

        std::lock_guard<std::mutex> lock(mutex);
        m_game->seconds++;
        if (m_game->seconds >= 60) {
            m_game->seconds = 0;  // Reset seconds
            m_game->Minutes++;    // Increment minutes
        }

        mvprintw(17, 3, "Time %02d:%02d", m_game->Minutes, m_game->seconds);
        refresh();  // Refresh the screen to show the updated values
    }
}

// Stop the timer
void Renderer::stopTimer() {
    timer_running = false;
    if (timerThread.joinable()) {
        timerThread.join();  // Wait for the thread to finish
    }
}

void Renderer::run() {
    MEVENT event;
    int input{0};

    int x, y;
    int a, b;

    while ((input = getch()) != 'q') {
        if (m_game->board.solved()) {
            stopTimer();
            clear();
            mvprintw(0, 0, "Congratulation: you solved it");
            getch();
            break;
        }
        if (input == KEY_MOUSE) {
            if (getmouse(&event) == OK) {
                // handle the mouse clik event
                if (event.bstate & BUTTON1_PRESSED) {
                    // Handle the mouse input for the main panel
                    for (int i{0}; i < 4; ++i) {
                        for (int j{0}; j < 4; ++j) {
                            if (event.x >= (i * 9) && event.y >= (j * 4) &&
                                event.x < (i * 9 + 7) &&
                                event.y < (j * 4 + 3)) {
                                if (m_game->board.moveTile(i, j)) {
                                    drawBoard();
                                    m_game->moveCount++;
                                    mvprintw(16, 3, "Moves %d",
                                             m_game->getMovesCount());
                                    refresh();
                                }
                                
                            }
                        }
                    }

                    // quit button press detection
                    x = m_game->quitButton.getX();
                    y = m_game->quitButton.getY();
                    a = x + m_game->quitButton.getWidth();
                    b = y + m_game->quitButton.getHeight();
                    if (event.x >= x && event.y >= y && event.x < a &&
                        event.y < b) {
                        m_game->quitButton.setState(Button::CLICKED);
                        drawButton(m_game->quitButton);
                    }

                    mvprintw(15, 15, "%d,%d", event.x, event.y);

                } else if (event.bstate & BUTTON1_RELEASED) {
                    // quit button press detection
                    x = m_game->quitButton.getX();
                    y = m_game->quitButton.getY();
                    a = x + m_game->quitButton.getWidth();
                    b = y + m_game->quitButton.getHeight();
                    if (event.x >= x && event.y >= y && event.x < a &&
                        event.y < b) {
                        m_game->quitButton.setState(Button::NORMAL);
                        drawButton(m_game->quitButton);
                        break;
                    }

                } else {
                }
            }
        }
    }
}
