#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "src/io.h"
#include "src/file.h"
#include "src/editor.h"

int main(){
    mkdir(ROOT, 0777);
    //while(!read_command(stdout));

    /*initscr();

    FILE* f = fopen("./vimr/guitest.c", "r");
    char c;
    while((c = fgetc(f)) != EOF){
        printw("%c", c);
    }

    int mx = getmaxx(stdscr), my = getmaxy(stdscr);
    printf("%d %d", mx, my);

    refresh();

    move(2 , 2);
    while(true){
        c = getch();
        clear();
        printf("%d", c);
        printw("%c", c);
        break;
    }

    endwin();*/

    init_window();
    window* win = create_window(char_to_str("/root/guitest.c"));
    win->start = 5;
    show(win);

    while(1){
        char c = getch();
        append(win->command, c);
        win->start++;
        show(win);
    }
    getch();
    endwin();

    return 0;
}