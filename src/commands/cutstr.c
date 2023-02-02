#include "cutstr.h"
#include "copystr.h"
#include "removestr.h"

bool cutstr(FILE* outf, string* path, int left, int right){
    copystr(NULL, path, left, right);
    removestr(NULL, path, left, right);
    if(outf != NULL)
        fprintf(outf, "Done\n");
    return false;
}

bool run_cutstr(FILE* outf, command* cmd){
    int left, right;
    if(command_to_range(outf, cmd, &left, &right)){
        return true;
    }
    string* path = get_option(cmd, "--file");
    cutstr(outf, path, left, right);
    return false;
}