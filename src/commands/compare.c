#include "compare.h"
#include <string.h>

bool compare(FILE* outf, string* path1, string* path2){
    FILE* first = fopen(get_path(path1, 0)->s, "r");
    FILE* second = fopen(get_path(path2, 0)->s, "r");
    vecstr* vec1 = readlines(first); int n = vec1->size;
    vecstr* vec2 = readlines(second); int m = vec2->size;
    for(int i = 0; i < n && i < m; i++){
        if(!strcmp(vec1->v[i].s, vec2->v[i].s)){
            continue;
        }
        fprintf(outf, "====== #%d ======\n%s\n%s\n", i + 1, vec1->v[i].s, vec2->v[i].s);
    }
    if(n == m){
        return false;
    }
    if(n > m){
        n ^= m; m ^= n; n ^= m;
    }
    fprintf(outf, ">>>>> #%d - #%d >>>>>\n", n + 1, m);
    for(int i = n; i < m; i++){
        if(vec1->size > i){
            fprintf(outf, "%s\n", vec1->v[i].s);
        }
        if(vec2->size > i){
            fprintf(outf, "%s\n", vec2->v[i].s);
        }
    }
    return false;
}

bool run_compare(FILE* outf, command* cmd){
    string* path1 = &cmd->oth->v[0];
    string* path2 = &cmd->oth->v[1];
    if(check_file(outf, path1) || check_file(outf, path2)){
        return true;
    }
    return compare(outf, path1, path2);
}