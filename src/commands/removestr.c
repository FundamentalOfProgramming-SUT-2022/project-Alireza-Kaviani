#include "removestr.h"

bool removestr(FILE* outf, string* path, int left, int right){
    FILE *src, *dst;
    get_src_dst(&src, &dst, path);
    print_range(dst, src, 0, left);
    print_range(dst, src, right, -1);
    fclose(src);
    fclose(dst);
    if(outf != NULL)
        fprintf(outf, "Done\n");
    return false;
}

bool run_removestr(FILE* outf, command* cmd){
    int left, right;
    if(command_to_range(outf, cmd, &left, &right)){
        return true;
    }
    string* path = get_option(cmd, "--file");
    removestr(outf, path, left, right);
    return false;
}