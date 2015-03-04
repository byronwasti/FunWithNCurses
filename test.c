#include <stdio.h>
#include <stdlib.h>
#include <curses.h>
#include <unistd.h>
#include <sys/poll.h>

int main( int argc, char *argv[]){
    struct pollfd fds;
    fds.fd = 0;
    fds.events = POLLIN;

    int c, y, x, max_y, max_x, ret;
    char buf[1];
    initscr();
    //raw();
    cbreak();
    noecho();
    mvaddch(1,1,'t');
    getmaxyx(stdscr, max_y, max_x);
    for(y = 0; y < max_y;y++){   

        refresh();
        usleep(30000);
        mvaddch(y,x,'t');
        ret = poll(&fds, 1, 0);
        if (ret == 1){
            //printf("%c", buf[0]);
            c = getchar();
            mvaddch(0,0,c);
            x++;
        }
    }
    endwin();
}  
