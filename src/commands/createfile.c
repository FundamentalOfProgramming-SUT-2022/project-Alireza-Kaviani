#include "createfile.h"

bool createfile(FILE* outf, string* path){
    if(file_exists(get_path(path, 0))){
        fprintf(outf, "File already exists\n");
        return true;
    }
    create_file(path, 0);
    fprintf(outf, "Done\n");
    return false;
}

bool run_createfile(FILE* outf, command* cmd){
    string* path = get_option(cmd, "--file");
    return createfile(outf, path);
}