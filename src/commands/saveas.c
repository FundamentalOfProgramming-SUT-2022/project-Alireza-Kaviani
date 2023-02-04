#include "save.h"
#include "../undo.h"

bool run_saveas(FILE* outf, window* win, command* cmd){
    copy_file(get_path(char_to_str(OPENFILE), 1), get_path(&cmd->oth->v[0], 0));
    return false;
}