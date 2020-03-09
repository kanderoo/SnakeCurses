#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

enum compass{UP, DOWN, LEFT, RIGHT};
enum compass direction = RIGHT;
int length = 6;
int x = 8;
int y = 7;
int endX = 3;
int endY = 7;

enum compass path[5] = {RIGHT, RIGHT, RIGHT, RIGHT, RIGHT};

int endGame() {
    mvprintw(7,14, "Game Over!"); 
    nodelay(stdscr, FALSE);
    getch();
    endwin();
    exit(0);
}

int newfruit() {
    mvprintw(1+(rand() % 14), 1+(rand() % 38), "●");
    return 0;
}

int moveSnake() {
    mvprintw(endY, endX, " ");
    switch(direction) {
        case LEFT:
            if (x > 1) {
                mvprintw(y, x, "░");
                x--;
                mvprintw(y, x, "▓");
            } else {
                endGame();
            }
            break;
        case DOWN: /*j*/
            mvprintw(y, x, "░");
            if (y < 14) {
                y++;
                mvprintw(y, x, "▓");
            } else {
                endGame();
            }
            break;
        case UP: /*k*/
            mvprintw(y, x, "░");
            if (y > 1) {
                y--;
                mvprintw(y, x, "▓");
            } else {
                endGame();
            }
            break;
        case RIGHT: /*l*/
            mvprintw(y, x, "░");
            if (x < 38) {
                x++;
                mvprintw(y, x, "▓");
            } else {
                endGame();
            }
            break;
    }
    mvprintw(50, 50, "3");
}

int logPath() {
    int i = 0;
    for (; i < 4; i++) {
        path[i] = path[i+1];
    }
    path[4] = direction;
}

int updateEnd() {
    switch(path[0]) {
        case LEFT:
            endX--;
            break;
        case DOWN:
            endY++;
            break;
        case UP:
            endY--;
            break;
        case RIGHT:
            endX++;
            break;
    }
    return(0);
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
        updateEnd();
        logPath();
        refresh();
    }
}
