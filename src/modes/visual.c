#include "visual.h"
#include "../file.h"

void visual_mode(window* win){
    char c = read_char(win);
    if(c == 'h' || c == 'j' || c == 'k' || c == 'l'){
        move_cursor(win, c);
        FILE* src = fopen(get_path(char_to_str(OPENFILE), 1)->s, "r");
        win->hr = pos_to_index(src, win->line, win->pos);
        fclose(src);
        return;
    }
    if(c == 'd'){
        int L = win->hl, R = win->hr;
        
    }
}