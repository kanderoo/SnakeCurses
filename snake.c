#include <ncurses.h>
#include <locale.h>
#include <stdlib.h>
#include <time.h>

enum compass{UP, DOWN, LEFT, RIGHT};
enum compass direction;
int length;
int x;
int y;
int endX;
int endY;
int arraySize;


int* path;

int initGame() {
    /* init variables */
    length = 6;
    x = 8;
    y = 7;
    endX = 3;
    endY = 7;
    arraySize = 5;

    /* init path array */
    path = (int*)malloc(arraySize * sizeof(int));
    for (int i = 0; i < arraySize; i++) {
        path[i] = RIGHT;
    }

    direction = RIGHT;

    /* draw playing area */
    mvprintw(0, 0,  "╔══════════════════════════════════════╗\n");
    mvprintw(1, 0,  "║                                      ║\n");
    mvprintw(2, 0,  "║                                      ║\n");
    mvprintw(3, 0,  "║                                      ║\n");
    mvprintw(4, 0,  "║                                      ║\n");
    mvprintw(5, 0,  "║                                      ║\n");
    mvprintw(6, 0,  "║                                      ║\n");
    mvprintw(7, 0,  "║  ░░░░░▓                    ●         ║\n");
    mvprintw(8, 0,  "║                                      ║\n");
    mvprintw(9, 0,  "║                                      ║\n");
    mvprintw(10, 0, "║                                      ║\n");
    mvprintw(11, 0, "║                                      ║\n");
    mvprintw(12, 0, "║                                      ║\n");
    mvprintw(13, 0, "║                                      ║\n");
    mvprintw(14, 0, "║                                      ║\n");
    mvprintw(15, 0, "╚══════════════════════════════════════╝\n");
    mvprintw(16, 0, "Length: 6  ");
}

int checkMemory() {
    if (length-2 == arraySize) {
        arraySize += 10;
        int* newPath = realloc(path, arraySize * sizeof(int));
        path = newPath;
    }
}

int endGame() {
    mvprintw(7, 15, "Game Over!"); 
    mvprintw(8, 11, "Press r to restart");
    mvprintw(9, 10, "Press CTRL+C to quit");
    nodelay(stdscr, FALSE);
    while(true) {
        switch(getch()) {
            case 3:
                free(path);
                endwin();
                exit(0);
                break;
            case 114:
                nodelay(stdscr, TRUE);
                initGame();
                return(0);
        }
    }
}

int newFruit() {
    int randx = 1+(rand() % 14);
    int randy =  1+(rand() % 38);
    if (mvinch(randx, randy) != L'░') {
        mvprintw(randx, randy, "●");
    } else {
        newFruit(); //recur if the fruit lands on snake
    }
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

int nextChar() {
    switch(direction) {
        case LEFT:
            return mvinch(y, x-1);
        case DOWN:
            return mvinch(y+1, x);
        case UP:
            return mvinch(y-1, x);
        case RIGHT:
            return mvinch(y, x+1);
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

    initGame();

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
            case 27:
                mvprintw(17, 0, "Paused");
                ch = 0;
                while (ch != 27) {
                    ch = getch();
                }
                mvprintw(17, 0, "      ");
                break;
            case 3: /*CTRL+C*/
                free(path);
                endwin();
                return(0);
        }
        switch(nextChar()) {
            case L'●':
                length++;
                mvprintw(16, 0, "Length: %d", length);
                newFruit();
                path[length-2] = direction;
                checkMemory();
                break;
            case L'░':
                endGame();
            default:
                mvprintw(endY, endX, " ");
                updateEnd();
                shiftPath();
        }
        moveSnake();

        refresh();
    }
}
