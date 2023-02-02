#include "pastestr.h"

bool pastestr(FILE* outf, string* path, int pos){
    FILE *src, *dst;
    FILE *clip = fopen(get_path(char_to_str(CLIPBOARD), 1)->s, "r");
    get_src_dst(&src, &dst, path);
    print_range(dst, src, 0, pos);
    print_file(dst, clip);
    print_range(dst, src, pos, -1);
    fclose(src);
    fclose(dst);
    fclose(clip);
    if(outf != NULL)
        fprintf(outf, "Done\n");
    return false;
}

bool run_pastestr(FILE* outf, command* cmd){
    int pos;
    if(command_to_pos(outf, cmd, &pos)){
        return true;
    }
    string* path = get_option(cmd, "--file");
    pastestr(outf, path, pos);
    return false;
}