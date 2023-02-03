#include "grep.h"
#include <stdlib.h>

int* build_kmp(string* s){
    int n = s->size, k = 0;
    int* kmp = calloc(n, sizeof(int));
    for(int i = 1; i < n; i++){
        while(k > 0 && s->s[k] != s->s[i])    k = kmp[k - 1];
        if(s->s[k] == s->s[i])  k++;
        kmp[i] = k;
    }
    return kmp;
}

int count_file(FILE* outf, string* path, string* s, int* kmp, int print){
    FILE* src = fopen(get_path(path, 0)->s, "r");
    int n = s->size, res = 0;
    char c;
    while((c = fgetc(src)) != EOF){
        int k = 0;
        bool flag = false;
        string* line = create_string();
        while(c != '\n' && c != EOF){
            if(print)
                append(line, c);
            while(k > 0 && c != s->s[k])    k = kmp[k - 1];
            if(c == s->s[k])    k++;
            if(k == n){
                k = kmp[k - 1];
                flag = true;
            }
            c = fgetc(src);
        }
        if(flag){
            res++;
            if(print){
                fprintf(outf, "%s: %s\n", path->s, line->s);
            }
        }
    }
    return res;
}

bool grep(FILE* outf, vecstr* files, string* s, int type){
    for(int i = 0; i < files->size; i++){
        string* path = &files->v[i];
        if(check_file(outf, path)){
            return true;
        }
    }
    int* kmp = build_kmp(s), cnt = 0;
    for(int i = 0; i < files->size; i++){
        string* path = &files->v[i];
        int c = count_file(outf, path, s, kmp, (type == 0));
        cnt += c;
        if(c > 0 && type == 2){
            fprintf(outf, "%s\n", path->s);
        }
    }
    if(type == 1){
        fprintf(outf, "%d\n", cnt);
    }
    return false;
}

bool run_grep(FILE* outf, command* cmd){
    vecstr* files = create_vecstr();
    push_back(files, get_option(cmd, "--files"));
    for(int i = 0; i < cmd->oth->size; i++){
        push_back(files, &cmd->oth->v[i]);
    }
    string* s = get_option(cmd, "--str");
    int type = 0;
    if(get_option(cmd, "-c")->size != 0){
        type = 1;
    }
    if(get_option(cmd, "-l")->size != 0){
        type = 2;
    }
    return grep(outf, files, s, type);
}