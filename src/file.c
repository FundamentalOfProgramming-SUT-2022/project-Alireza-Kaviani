#include "file.h"
#include <sys/stat.h>

string* get_path(string* path, int hidden){
    string* cur = create_string();
    string* res = create_string();
    for(int i = 1; i < path->size; i++){
        if(path->s[i] == '/'){
            if(cur->s[0] != '/'){
                cur = (hidden ? char_to_str(HIDDEN) : char_to_str(ROOT));
            }
            res = concat(res, cur);
            mkdir(res->s, 0777);
            cur = char_to_str("/");
            continue;
        }
        append(cur, path->s[i]);
    }
    res = concat(res, cur);
    return res;
}

bool file_exists(string* real_path){
    struct stat buffer;
    return (stat(real_path->s, &buffer) == 0);
}

string* create_file(string* path, int hidden){
    string* res = get_path(path, hidden);
    FILE* f = fopen(res->s, "w");
    fclose(f);
    return res;
}

bool check_file(FILE* outf, string* path){
    string* cur = create_string();
    string* res = create_string();
    for(int i = 1; i < path->size; i++){
        if(path->s[i] == '/'){
            if(cur->s[0] != '/'){
                cur = char_to_str(ROOT);
            }
            res = concat(res, cur);
            if(!file_exists(res)){
                fprintf(outf, "Directory doesn't exist\n");
                return true;
            }
            cur = char_to_str("/");
            continue;
        }
        append(cur, path->s[i]);
    }
    res = concat(res, cur);
    if(!file_exists(res)){
        fprintf(outf, "File doesn't exist\n");
        return true;
    }
    return false;
}

void print_range(FILE* dst, FILE* src, int from, int to){
    fseek(src, 0, SEEK_SET);
    char c;
    for(int i = 0; (c = fgetc(src)) != EOF; i++){
        if(from <= i && (i < to || to == -1)){
            fputc(c, dst);
        }
    }
}

void print_file(FILE* dst, FILE* src){
    print_range(dst, src, 0, -1);
}

void copy_file(string* src, string* dst){
    FILE* srcf = fopen(src->s, "r");
    FILE* dstf = fopen(dst->s, "w");
    print_file(dstf, srcf);
    fclose(dstf);
    fclose(srcf);
}