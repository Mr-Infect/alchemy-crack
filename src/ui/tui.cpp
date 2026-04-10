#include "ui/tui.hpp"
#include <ncurses.h>

void start_ui() {
    initscr();
    noecho();
    curs_set(0);
}

void update_ui(long long attempts) {
    clear();
    mvprintw(2, 2, "Alchemy Crack Engine");
    mvprintw(4, 2, "Attempts: %lld", attempts);
    mvprintw(6, 2, "Status: Running...");
    refresh();
}

void stop_ui() {
    endwin();
}
