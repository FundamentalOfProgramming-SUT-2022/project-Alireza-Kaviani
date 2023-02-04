#include "find.h"
#include "../pattern.h"
#include <limits.h>
#include <stdlib.h>

bool find(FILE* outf, string* path, string* expr, int type, int* l, int* r){
    int n = expr->size;
    pattern* ptrn = create_pattern(expr);
    reset(ptrn, 0);
    FILE* src = fopen(get_path(path, 1)->s, "r");
    char c;
    bool flag = false;
    int prv = -1, cnt = 0;
    *l = -1; *r = -1;
    for(int i = 0; (c = fgetc(src)) != EOF; i++){
        update(ptrn, c, i);
        int pos = ptrn->dp[n];
        if(pos != INT_MAX){
            if(pos <= prv)  continue;
            cnt++;
            if(cnt == type){
                *l = pos;
                *r = i;
            }
            prv = pos;
        }
    }
    fclose(src);
    return false;
}

bool run_find(FILE* outf, command* cmd){
    string* path = get_option(cmd, "--file");
    if(check_file(outf, path)){
        return true;
    }
    string* expr = get_option(cmd, "--str");
    int type = 1; // pos:at, -1:count, -2:all
    if(get_option(cmd, "-count")->size != 0){
        type = -1;
    }
    if(get_option(cmd, "-all")->size != 0){
        type = -2;
    }
    if(get_option(cmd, "-at")->size != 0){
        type = atoi(get_option(cmd, "-at")->s);
    }
    int byword = (get_option(cmd, "-byword")->size != 0), l = 0, r = 0;
    find(outf, path, expr, type, &l, &r);
    return false;
}