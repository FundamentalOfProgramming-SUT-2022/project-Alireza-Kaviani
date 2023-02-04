#ifndef EDITOR_H
#define EDITOR_H

#include "file.h"
#include <ncurses.h>

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
    COLOR_SELECTION
} COLOR;

typedef struct{
    string* path;
    string* command;
    int start, curx , cury;
    bool issaved;
    MODE mode;
} window;

void init_window();
window* create_window(string* path);
void show(window* win);

#endif