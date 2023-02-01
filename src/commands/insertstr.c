#include "insertstr.h"

bool insertstr(FILE* outf, string* path, string* str, int pos){
    FILE *src, *dst;
    get_src_dst(&src, &dst, path);
    print_range(dst, src, 0, pos);
    printstr(dst, str);
    print_range(dst, src, pos, -1);
    fclose(src);
    fclose(dst);
    fprintf(outf, "Done\n");
    return false;
}

bool run_insertstr(FILE* outf, command* cmd){
    int pos;
    if(command_to_pos(outf, cmd, &pos)){
        return true;
    }
    string* path = get_option(cmd, "--file");
    string* str = get_option(cmd, "--str");
    insertstr(outf, path, str, pos);
    return false;
}