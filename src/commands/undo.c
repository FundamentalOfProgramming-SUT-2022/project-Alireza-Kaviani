#include "undo.h"
#include "../undo.h"

bool run_undo(FILE* outf, command* cmd){
    string *path = get_option(cmd, "--file");
    if(check_file(outf, path)){
        return true;
    }
    undo(path);
    fprintf(outf, "Done\n");
    return false;
}