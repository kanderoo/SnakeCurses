#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <unistd.h>

int newfruit() {
    mvprintw(1+(rand() % 14), 1+(rand() % 38), "●");
}

int main() {
    setlocale(LC_ALL, "");
    initscr();
    raw();

    /* draw playing area */
    printw("╔══════════════════════════════════════╗\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("╚══════════════════════════════════════╝\n");

    while(1) {
        newfruit();
        refresh();
        sleep(1);
    }
    endwin();

    return 0;
}
