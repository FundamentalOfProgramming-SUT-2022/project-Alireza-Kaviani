#include "copystr.h"

bool copystr(FILE* outf, string* path, int left, int right){
    FILE* src = fopen(get_path(path, 1)->s, "r");
    FILE* dst = fopen(get_path(char_to_str(CLIPBOARD), 1)->s, "w");
    print_range(dst, src, left, right);
    fclose(src);
    fclose(dst);
    if(outf != NULL)
        fprintf(outf, "Done\n");
    return false;
}

bool run_copystr(FILE* outf, command* cmd){
    int left, right;
    if(command_to_range(outf, cmd, &left, &right)){
        return true;
    }
    string* path = get_option(cmd, "--file");
    copystr(outf, path, left, right);
    return false;
}