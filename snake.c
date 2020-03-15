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
int fruitX = 29;
int fruitY = 7;
int arraySize = 5;

int* path;

int checkMemory() {
    if (length-2 == arraySize) {
        arraySize += 10;
        int* newPath = realloc(path, arraySize * sizeof(int));
        path = newPath;
    }
}

int endGame() {
    mvprintw(7, 15, "Game Over!"); 
    mvprintw(8, 10, "Press CTRL+C to quit");
    nodelay(stdscr, FALSE);
    while(getch() != 3) {}
    free(path);
    endwin();
    exit(0);
}

int newFruit() {
    fruitX = 1+(rand() % 38);
    fruitY = 1+(rand() % 14);
    mvprintw(fruitY, fruitX, "●");
    return 0;
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

int shiftPath() {
    int i = 0;
    for (; i < (length-2); i++) {
        path[i] = path[i+1];
    }
    path[length-2] = direction;
}

int moveSnake() {
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
            if (y < 14) {
                mvprintw(y, x, "░");
                y++;
                mvprintw(y, x, "▓");
            } else {
                endGame();
            }
            break;
        case UP: /*k*/
            if (y > 1) {
                mvprintw(y, x, "░");
                y--;
                mvprintw(y, x, "▓");
            } else {
                endGame();
            }
            break;
        case RIGHT: /*l*/
            if (x < 38) {
                mvprintw(y, x, "░");
                x++;
                mvprintw(y, x, "▓");
            } else {
                endGame();
            }
            break;
    }
}


int main() {

    path = (int*)malloc(arraySize * sizeof(int));
    for (int i = 0; i < arraySize; i++) {
        path[i] = RIGHT;
    }

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
    printw("║  ░░░░░▓                    ●         ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("║                                      ║\n");
    printw("╚══════════════════════════════════════╝\n");

    int ch;
    mvprintw(16, 0, "Length: 6");
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
                free(path);
                endwin();
                return(0);
        }
        if (x == fruitX && y == fruitY) {
            length++;
            mvprintw(16, 0, "Length: %d", length);
            newFruit();
            path[length-2] = direction;
        } else {
            mvprintw(endY, endX, " ");
            updateEnd();
            shiftPath();
        }
        moveSnake();
        checkMemory();

        refresh();
    }
}
