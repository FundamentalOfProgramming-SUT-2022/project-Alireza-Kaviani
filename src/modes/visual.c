#include "visual.h"
#include "../file.h"
#include "../commands/cutstr.h"
#include "../commands/copystr.h"

void visual_mode(window* win){
    char c = read_char(win);
    if(c == 'h' || c == 'j' || c == 'k' || c == 'l'){
        move_cursor(win, c);
        FILE* src = fopen(get_path(char_to_str(OPENFILE), 1)->s, "r");
        win->hr = pos_to_index(src, win->line, win->pos);
        fclose(src);
        return;
    }
    if(c == 'd' || c == 'y'){
        int L = win->hl, R = win->hr;
        if(L > R){
            L ^= R; R ^= L; L ^= R;
        }
        R++;
        if(c == 'd'){
            cutstr(NULL, char_to_str(OPENFILE), L, R);
            win->issaved = false;
            FILE* src = fopen(get_path(char_to_str(OPENFILE), 1)->s, "r");
            get_valid_pos(src, &win->line, &win->pos);
            fclose(src);
        }
        else{
            copystr(NULL, char_to_str(OPENFILE), L, R);
        }
        win->mode = NORMAL;
        win->hl = win->hr = -1;
        win->highlight = COLOR_TEXT;
        return;
    }
}