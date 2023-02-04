#include "normal.h"
#include "../commands/autoindent.h"
#include "../undo.h"
#include "../commands/pastestr.h"

void normal_mode(window* win){
    char c = read_char(win);
    if(c == 'h' || c == 'j' || c == 'k' || c == 'l'){
        move_cursor(win, c);
        return;
    }
    if(c == 'i' || c == 'a'){
        win->mode = INSERT;
        return;
    }
    if(c == 'v'){
        win->mode = VISUAL;
        win->highlight = COLOR_SELECTION;
        FILE* src = fopen(get_path(char_to_str(OPENFILE), 1)->s, "r");
        win->hl = win->hr = pos_to_index(src, win->line, win->pos);
        fclose(src);
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
        win->issaved = false;
        return;
    }
    if(c == 'u'){
        undo(win);
    }
    if(c == 'p'){
        FILE* src = fopen(get_path(char_to_str(OPENFILE), 1)->s, "r");
        int pos = pos_to_index(src, win->line, win->pos);
        fclose(src);
        pastestr(NULL, win->path, pos);
        win->issaved = false;
    }
}