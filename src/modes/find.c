#include "find.h"
#include "../io.h"
#include "../commands/find.h"

void back_to_normal(window* win){
    win->command = char_to_str("Find done");
    read_char(win);
    win->mode = NORMAL;
    win->command = create_string();
    win->findat = 1;
    win->highlight = COLOR_TEXT;
}

void find_mode(window* win){
    string* pattern = create_string();
    if(win->command->size == 1){
        read_pattern(win, pattern);
    }
    else{
        if(read_char(win) != 'n'){
            back_to_normal(win);
            return;
        }
        for(int i = 1; i < win->command->size - 1; i++){
            append(pattern, win->command->s[i]);
        }
    }
    FILE* dst = fopen("vimr/.vim/output.vim", "w");
    printstr(dst, pattern);
    fclose(dst);
    find(NULL, char_to_str(OPENFILE), pattern, win->findat, &win->hl, &win->hr);
    if(win->hl == -1){
        back_to_normal(win);
    }
    else{
        win->findat++;
    }
}