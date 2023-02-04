#include "editor.h"
#include <stdlib.h>

#include "modes/normal.h"

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
    res->line = 0; res->pos = 0;
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
    for(int i = 0; (c = fgetc(src)) != EOF; i++){
        if(i < start || end <= i){
            while(c != '\n' && c != EOF){
                c = fgetc(src);
            }
            continue;
        }
        printw("%4d ", i + 1);
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

    move(win->line - win->start, win->pos + 5);

    refresh();
}

char read_char(window* win){
    show(win);
    return getch();
}

void move_cursor(window* win, char c){
    if(c == 'k'){
        win->line--;
    }
    if(c == 'j'){
        win->line++;
    }
    if(c == 'h'){
        win->pos--;
    }
    if(c == 'l'){
        win->pos++;
    }
    FILE* src = fopen(get_path(win->path, 0)->s, "r");
    get_valid_pos(src, &win->line, &win->pos);
    if(c == 'k' && win->line - win->start < 3 && win->start > 0){
        win->start--;
    }
    if(c == 'j' && win->start + getmaxy(stdscr) - win->line < 6){
        win->start++;
    }
}

void mainloop(window* win){
    while(1){
        normal_mode(win);
    }
}