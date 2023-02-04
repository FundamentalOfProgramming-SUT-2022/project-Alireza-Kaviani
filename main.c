#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "src/io.h"
#include "src/file.h"
#include "src/editor.h"

int main(int argc, char* argv[]){
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
    window* win = create_window(char_to_str(argv[1]));

    mainloop(win);
    endwin();

    return 0;
}