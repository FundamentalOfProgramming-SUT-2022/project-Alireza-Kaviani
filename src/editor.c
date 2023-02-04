#include "editor.h"
#include "file.h"
#include "undo.h"
#include <stdlib.h>

#include "modes/normal.h"
#include "modes/insert.h"
#include "modes/command.h"
#include "modes/visual.h"

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
    copy_file(get_path(path, 0), get_path(char_to_str(OPENFILE), 1));
    res->path = path;
    res->command = create_string();
    res->mode = NORMAL;
    res->start = 0;
    res->line = 0; res->pos = 0;
    res->issaved = true;
    res->hl = -1; res->hr = -1;
    res->highlight = COLOR_TEXT;
    return res;
}

void open_file(window* win, string* path){
    save(win);
    if(!file_exists(get_path(path, 0))){
        create_file(path, 0);
    }
    copy_file(get_path(path, 0), get_path(char_to_str(OPENFILE), 1));
    win->path = path;
    win->command = create_string();
    win->mode = NORMAL;
    win->start = 0;
    win->line = 0; win->pos = 0;
    win->issaved = true;
    win->hl = -1; win->hr = -1;
    win->highlight = COLOR_TEXT;
}

void show(window* win){
    string* filename = get_filename(win->path);
    clear();
    int L = win->hl, R = win->hr;
    if(L > R){
        L ^= R; R ^= L; L ^= R;
    }

    FILE* src = fopen(get_path(char_to_str(OPENFILE), 1)->s, "r");
    char c;
    int ind = 0, start = win->start, end = start + getmaxy(stdscr) - 2;
    attron(COLOR_PAIR(COLOR_TEXT));
    for(int i = 0; (c = fgetc(src)) != EOF; i++){
        if(i < start || end <= i){
            while(c != '\n' && c != EOF){
                c = fgetc(src);
                ind++;
            }
            ind++;
            continue;
        }
        printw("%4d ", i + 1);
        while(c != '\n' && c != EOF){
            if(L <= ind && ind <= R){
                attron(COLOR_PAIR(win->highlight));
                printw("%c", c);
                attroff(COLOR_PAIR(win->highlight));
            }
            else{
                printw("%c", c);
            }
            c = fgetc(src);
            ind++;
        }
        ind++;
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
    FILE* src = fopen(get_path(char_to_str(OPENFILE), 1)->s, "r");
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
        if(win->mode == NORMAL){
            normal_mode(win);
        }
        if(win->mode == INSERT){
            insert_mode(win);
        }
        if(win->mode == COMMAND){
            command_mode(win);
        }
        if(win->mode == VISUAL){
            visual_mode(win);
        }
    }
}