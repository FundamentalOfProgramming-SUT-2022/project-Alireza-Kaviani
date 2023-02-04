#include "save.h"
#include "../undo.h"

bool run_save(FILE* outf, window* win, command* cmd){
    save(win);
    return false;
}