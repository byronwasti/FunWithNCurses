#include <ncurses.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/poll.h>


#define DELAY 50000

int main(int argc, char *argv[]){
    int    px,    py,
            i,     j,
        max_y, max_x;

    int    bx = 1,    by = 1,
        dir_y = -1, dir_x = -1;
    int speed;

    int score = 0;
    char sc[3];
    char *s = sc;

    char c;
    char paddle = '_';
    char ball = 'o';

    initscr();
    start_color();
    noecho();
    cbreak();   
    curs_set(FALSE);

    struct pollfd fds;
    int ret;
    fds.fd = 0;
    fds.events = POLLIN;

    getmaxyx(stdscr, max_y, max_x);
    py = max_y - 2;
    px = max_x/2;
    speed = max_x / 15;
    for( j = 0; j < 1000; j++){
        clear();
        for( i = 0; i < max_x/5; i++){
            mvaddch(py, px+i, paddle);
        }

        //init_pair(1, COLOR_RED, COLOR_BLACK);
        //attron(COLOR_PAIR(1));   
        mvaddch(by,bx, ball);

        sprintf(sc, "%d", score);
        mvaddstr(0,0, s);

        refresh();
        
        usleep(DELAY);

        if (by == 0) dir_y = -dir_y;
        if (bx == max_x || bx == 0) dir_x = -dir_x;
        if (by == max_y) break;
        if ( px < bx && bx < (px + max_x/5) && by == py) {dir_y = -dir_y; score++;}

        switch(dir_x){
            case -1: bx += 1; break;
            case 1: bx -= 1; break;
        }
        switch(dir_y){
            case -1: by += 1; break;
            case 1: by -= 1; break;
        }

        ret = poll(&fds, 1, 0);
        if (ret == 1){
            c = getchar();
            switch (c){
                case 'a': px-=speed; break;
                case 'd': px+=speed; break; 
                case 'q': endwin(); return 0;
                default: break;
            }
        }

    }

    endwin();
}
