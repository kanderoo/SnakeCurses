#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

enum compass{UP, DOWN, LEFT, RIGHT};
enum compass direction = RIGHT;
int length = 6;
int x = 8;
int y = 7;

int newfruit() {
    mvprintw(1+(rand() % 14), 1+(rand() % 38), "●");
    return 0;
}

int moveSnake() {
    switch(direction) {
        case LEFT:
            mvprintw(y, x, "░");
            if (x > 1)
                x--;
            mvprintw(y, x, "▓");
            break;
        case DOWN: /*j*/
            mvprintw(y, x, "░");
            if (y < 14)
                y++;
            mvprintw(y, x, "▓");
            break;
        case UP: /*k*/
            mvprintw(y, x, "░");
            if (y > 1)
                y--;
            mvprintw(y, x, "▓");
            break;
        case RIGHT: /*l*/
            mvprintw(y, x, "░");
            if (x < 38)
                x++;
            mvprintw(y, x, "▓");
            break;
    }
}

int main() {
    setlocale(LC_ALL, "");

    /* init curses window */
    initscr();
    noecho();
    cbreak();
    raw();
    curs_set(0);
    nodelay(stdscr, TRUE);

    /* draw playing area */
    printw("╔══════════════════════════════════════╗\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║  ░░░░░▓                              ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("╚══════════════════════════════════════╝\n");

    int ch;
    while(1) {
        nanosleep((const struct timespec[]){{0, 80000000L}}, NULL);
        ch = getch();
        switch(ch) {
            case 104: /*h*/
                if (direction != RIGHT)
                    direction = LEFT;
                break;
            case 106: /*j*/
                if (direction != UP)
                    direction = DOWN;
                break;
            case 107: /*k*/
                if (direction != DOWN)
                    direction = UP;
                break;
            case 108: /*l*/
                if (direction != LEFT)
                    direction = RIGHT;
                break;
            case 3: /*CTRL+C*/
                endwin();
                return(0);
        }
        moveSnake();
        refresh();
    }
}
