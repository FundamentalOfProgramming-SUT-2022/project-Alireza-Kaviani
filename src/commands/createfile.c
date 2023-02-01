#include "createfile.h"

bool createfile(FILE* dst, command* cmd){
    string* s = get_option(cmd, "--file");
    if(file_exists(get_path(s, 0))){
        fprintf(dst, "File already exists\n");
        return true;
    }
    create_file(s, 0);
    fprintf(dst, "Done\n");
    return false;
}