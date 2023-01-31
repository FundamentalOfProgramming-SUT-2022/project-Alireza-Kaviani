#include "createfile.h"

bool createfile(FILE* f, command* cmd){
    string* s = get_option(cmd, "--file");
    if(file_exists(s)){
        printf("File already exists");
        fprintf(f, "File already exists\n");
        return true;
    }
    create_file(s, 0);
    fprintf(f, "Done");
    return false;
}