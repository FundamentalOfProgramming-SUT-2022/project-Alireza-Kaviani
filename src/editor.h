#ifndef EDITOR_H
#define EDITOR_H

#include <ncurses.h>
#include "str.h"

typedef enum{
    NORMAL,
    INSERT,
    VISUAL,
    FIND,
    COMMAND
} MODE;


typedef enum{
    COLOR_TEXT,
    COLOR_MODE,
    COLOR_SELECTION,
    COLOR_FIND
} COLOR;

typedef struct{
    string* path;
    string* command;
    int start, line , pos;
    int hl, hr, findat;
    bool issaved;
    MODE mode;
    COLOR highlight;
} window;

void init_window();
window* create_window(string* path);
void open_file(window* win, string* path);
void show(window* win);
char read_char(window* win);

void move_cursor(window* win, char c);
void mainloop(window* win);

#endif