#include "tree.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <errno.h>
#include <string.h>
#include <dirent.h>

void print_tree(FILE* outf, string* path, int maxdepth, int depth){
    if(depth > maxdepth){
        return;
    }
    DIR* dir = opendir(path->s);
    struct dirent* file;
    while((file = readdir(dir)) != NULL){
        char* name = file->d_name;
        if(name[0] == '.'){
            continue;
        }
        for(int i = 0; i < depth * 4; i++){
            if(i % 4 == 0){
                fprintf(outf, "|");
            }
            else if(i / 4 == depth - 1){
                fprintf(outf, "-");
            }
            else{
                fprintf(outf, " ");
            }
        }
        if(file->d_type == DT_DIR){
            fprintf(outf, "%s/\n", name);
            print_tree(outf, concat(path, concat(char_to_str("/"), char_to_str(name))), maxdepth, depth + 1);
        }
        else{
            fprintf(outf, "%s\n", name);
        }
    }
}

bool tree(FILE* outf, string* path, int maxdepth){
    print_tree(outf, path, maxdepth, 1);
    return false;
}

bool run_tree(FILE* outf, command* cmd){
    string* path = char_to_str(ROOT);
    int maxdepth = atoi(cmd->oth->v[0].s);
    return tree(outf, path, maxdepth);
}