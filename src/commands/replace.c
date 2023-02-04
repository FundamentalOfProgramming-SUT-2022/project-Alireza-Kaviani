#include "replace.h"
#include "../pattern.h"
#include <limits.h>
#include <stdlib.h>

bool replace(FILE* outf, string* path, string* expr, string* rep, int type){
    FILE *src, *dst, *f;
    get_src_dst(&src, &dst, path);
    int n = expr->size;
    pattern* ptrn = create_pattern(expr);
    reset(ptrn, 0);
    char c;
    int prv = -1, cnt = 0, start = 0;
    for(int i = 0; (c = fgetc(src)) != EOF; i++){
        update(ptrn, c, i);
        if(ptrn->dp[n] != INT_MAX){
            int pos = i;
            if(pos <= prv)  continue;
            cnt++;
            if(cnt == type || type == -1){
                print_range(dst, src, start, ptrn->dp[n]);
                printstr(dst, rep);
                reset(ptrn, i + 1);
                start = i + 1;
                fseek(src, start, SEEK_SET);
            }
            prv = pos;
        }
    }
    print_range(dst, src, start, -1);
    fprintf(outf, "Done\n");
    fclose(src);
    fclose(dst);
    return false;
}

bool run_replace(FILE* outf, command* cmd){
    string* path = get_option(cmd, "--file");
    string* expr = get_option(cmd, "--str1");
    string* rep = get_option(cmd, "--str2");
    int type = 1; // pos:at, -1:all
    if(get_option(cmd, "-all")->size != 0){
        type = -1;
    }
    if(get_option(cmd, "-at")->size != 0){
        type = atoi(get_option(cmd, "-at")->s);
    }
    replace(outf, path, expr, rep, type);
    return false;
}