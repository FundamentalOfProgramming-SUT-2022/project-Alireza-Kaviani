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
    fseek(src, from, SEEK_SET);
    char c;
    for(int i = from; (c = fgetc(src)) != EOF && (i < to || to == -1); i++){
        fputc(c, dst);
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

int pos_to_index(FILE* src, int line, int pos){
    line--;
    int idx = 0, L = 0, P = 0;
    char c;
    while((c = fgetc(src)) != EOF && (L < line || P < pos)){
        if(c == '\n'){
            L++; P = 0;
        }
        else{
            P++;
        }
        idx++;
    }
    return idx;
}

bool command_to_pos(FILE* outf, command *cmd, int* res){
    string* path = get_option(cmd, "--file");
    if(check_file(outf, path)){
        return true;
    }
    int line, pos;
    sscanf(get_option(cmd, "--pos")->s, "%d:%d", &line, &pos);
    FILE* src = fopen(get_path(path, 0)->s, "r");
    *res = pos_to_index(src, line, pos);
    return false;
}