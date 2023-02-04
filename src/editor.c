#include "editor.h"
#include <stdlib.h>

char* mode_name[5] = {"NORMAL", "INSERT", "VISUAL", "FIND", "COMMAND"};

void init_window(){
    initscr();
    start_color();
    init_pair(COLOR_TEXT, COLOR_WHITE, COLOR_BLACK);
    init_pair(COLOR_MODE, COLOR_BLACK, COLOR_WHITE);
    init_pair(COLOR_SELECTION, COLOR_BLACK, COLOR_WHITE);
}

window* create_window(string* path){
    window* res = malloc(sizeof(window));
    res->path = path;
    res->command = create_string();
    res->mode = NORMAL;
    res->start = 1;
    res->curx = 0; res->cury = 0;
    res->issaved = true;
    return res;
}

void show(window* win){
    string* filename = get_filename(win->path);
    clear();
    
    FILE* src = fopen(get_path(win->path, 0)->s, "r");
    char c;
    int start = win->start, end = start + getmaxy(stdscr) - 2;
    attron(COLOR_PAIR(COLOR_TEXT));
    for(int i = 1; (c = fgetc(src)) != EOF; i++){
        if(i < start || end <= i){
            while(c != '\n' && c != EOF){
                c = fgetc(src);
            }
            continue;
        }
        printw("%4d ", i);
        while(c != '\n' && c != EOF){
            printw("%c", c);
            c = fgetc(src);
        }
        printw("\n");
        start++;
    }
    for(int i = start; i < end; i++){
        printw("~\n");
    }
    attroff(COLOR_PAIR(COLOR_TEXT));
    fclose(src);

    attron(COLOR_PAIR(COLOR_MODE));
    printw("%s %s", mode_name[win->mode], filename->s);
    if(!win->issaved)
        printw(" +");
    printw("\n");
    attroff(COLOR_PAIR(COLOR_MODE));
    
    printw("%s", win->command->s);

    refresh();
}