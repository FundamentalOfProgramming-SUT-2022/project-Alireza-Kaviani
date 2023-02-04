#include "insert.h"
#include "../commands/insertstr.h"

void insert_mode(window* win){
    char c = read_char(win);
    string* str = create_string();
    append(str, c);
    FILE* src = fopen(get_path(char_to_str(OPENFILE), 1)->s, "r");
    int pos = pos_to_index(src, win->line, win->pos);
    fclose(src);
    insertstr(stdout, win->path, str, pos);
    win->pos++;
    if(c == '\n'){
        move_cursor(win, 'j');
        win->pos = 0;
    }
    win->issaved = false;
}