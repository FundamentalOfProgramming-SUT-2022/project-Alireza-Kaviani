#include "cat.h"

bool cat(FILE* dst, command* cmd){
    FILE* src;
    if(open_file(dst, &src, get_option(cmd, "--file"), "r")){
        return true;
    }
    print_file(dst, src);
    return false;
}