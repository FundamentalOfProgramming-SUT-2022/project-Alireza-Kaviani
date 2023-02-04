#include "normal.h"
#include "../commands/autoindent.h"

void normal_mode(window* win){
    char c = read_char(win);
    if(c == 'h' || c == 'j' || c == 'k' || c == 'l'){
        move_cursor(win, c);
        return;
    }
    if(c == 'i'){
        win->mode = INSERT;
        return;
    }
    if(c == ':'){
        append(win->command, ':');
        win->mode = COMMAND;
        return;
    }
    if(c == '/'){
        append(win->command, '/');
        win->mode = FIND;
        return;
    }
    if(c == '='){
        autoindent(stdout, win->path);
        return;
    }
}