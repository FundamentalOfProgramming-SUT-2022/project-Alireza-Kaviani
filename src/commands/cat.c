#include "cat.h"

bool cat(FILE* outf, string* path){
    if(check_file(outf, path)){
        return true;
    }
    FILE* src = fopen(get_path(path, 0)->s, "r");
    print_file(outf, src);
    fclose(src);
    return false;
}

bool run_cat(FILE* outf, command* cmd){
    string* path = get_option(cmd, "--file");
    return cat(outf, path);
}