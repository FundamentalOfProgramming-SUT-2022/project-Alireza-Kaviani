#include "find.h"
#include "../pattern.h"
#include <limits.h>
#include <stdlib.h>

int get_index(string* path, int pos, int byword){
    if(byword == 0) return pos + 1;
    return get_word_index(path, pos);
}

bool find(FILE* outf, string* path, string* expr, int type, int byword){
    int n = expr->size;
    pattern* ptrn = create_pattern(expr);
    reset(ptrn, 0);
    FILE* src = fopen(get_path(path, 0)->s, "r");
    char c;
    bool flag = false;
    int prv = -1, cnt = 0;
    for(int i = 0; (c = fgetc(src)) != EOF; i++){
        update(ptrn, c, i);
        if(ptrn->dp[n] != INT_MAX){
            int pos = get_index(path, ptrn->dp[n], byword);
            if(pos <= prv)  continue;
            cnt++;
            if(cnt == type || type == -2){
                if(flag){
                    fprintf(outf, ", ");
                }
                fprintf(outf, "%d", pos);
                flag = 1;
            }
            prv = pos;
        }
    }
    if(type == -1){
        fprintf(outf, "%d", cnt);
    }
    else if(flag == false){
        fprintf(outf, "-1");
    }
    fprintf(outf, "\n");
    fclose(src);
    return false;
}

bool run_find(FILE* outf, command* cmd){
    string* path = get_option(cmd, "--file");
    if(check_file(outf, path)){
        return true;
    }
    string* expr = get_option(cmd, "--str");
    int type = -1; // pos:at, -1:count, -2:all 
    if(get_option(cmd, "-all")->size != 0){
        type = -2;
    }
    if(get_option(cmd, "-at")->size != 0){
        type = atoi(get_option(cmd, "-at")->s);
    }
    int byword = (get_option(cmd, "-byword")->size != 0);
    find(outf, path, expr, type, byword);
    return false;
}