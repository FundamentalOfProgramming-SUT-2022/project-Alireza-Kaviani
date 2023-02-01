#include "cat.h"

bool cat(FILE* outf, string* path){
    FILE* src;
    if(open_file(outf, &src, path, "r")){
        return true;
    }
    print_file(outf, src);
    return false;
}

bool run_cat(FILE* outf, command* cmd){
    string* path = get_option(cmd, "--file");
    return cat(outf, path);
}