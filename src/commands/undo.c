#include "undo.h"
#include "../undo.h"

bool run_undo(FILE* outf, window* win){
    undo(win);
    return false;
}