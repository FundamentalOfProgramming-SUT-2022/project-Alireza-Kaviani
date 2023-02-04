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

string* file_to_str(FILE* src){
    string* res = create_string();
    char c;
    while((c = fgetc(src)) != EOF){
        append(res, c);
    }
    return res;
}

int pos_to_index(FILE* src, int line, int pos){
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
    int line, pos;
    sscanf(get_option(cmd, "--pos")->s, "%d:%d", &line, &pos);
    FILE* src = fopen(get_path(path, 1)->s, "r");
    *res = pos_to_index(src, line - 1, pos);
    fclose(src);
    return false;
}

bool command_to_range(FILE* outf, command *cmd, int* left, int* right){
    int pos, size;
    if(command_to_pos(outf, cmd, &pos)){
        return true;
    }
    sscanf(get_option(cmd, "-size")->s, "%d", &size);
    if(get_option(cmd, "-f")->size != 0){
        *left = pos;
        *right = pos + size;
    }
    else{
        *right = pos + 1;
        *left = pos - size + 1;
    }
    return false;
}

int get_word_index(string* path, int pos){
    FILE* src = fopen(get_path(path, 0)->s, "r");
    int res = 1, prv = 0;
    char c;
    for(int i = 0; i <= pos && (c = fgetc(src)) != EOF; i++){
        if(c == ' ' || c == '\n'){
            prv = 1;
            continue;
        }
        res += prv;
        prv = 0;
    }
    fclose(src);
    return res;
}

vecstr* readlines(FILE* src){
    vecstr* res = create_vecstr();
    char c;
    while((c = fgetc(src)) != EOF){
        string* str = create_string();
        while(c != '\n' && c != EOF){
            append(str, c);
            c = fgetc(src);
        }
        push_back(res, str);
    }
    return res;
}

string* get_filename(string* path){
    string* res = create_string();
    for(int i = 0; i < path->size; i++){
        append(res, path->s[i]);
        if(path->s[i] == '/'){
            res = create_string();
        }
    }
    return res;
}

void get_valid_pos(FILE* src, int* line, int* pos){
    char c;
    int l = 0, p = 0;
    for(l = 0; l < *line; l++){
        do{
            c = fgetc(src);
        }
        while(c != '\n' && c != EOF);
        if(c == EOF){
            break;
        }
    }
    for(p = 0; p < *pos; p++){
        c = fgetc(src);
        if(c == '\n' || c == EOF){
            break;
        }
    }
    *line = l;
    *pos = p;
}