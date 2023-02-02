#include "pattern.h"

#include <stdlib.h>
#include <limits.h>

void fill(int* start, int* end, int val){
    for(int* it = start; it != end; it++){
        (*it) = val;
    }
}

pattern* create_pattern(string* exp){
    pattern* res = malloc(sizeof(pattern));
    res->expr = exp;
    res->n = exp->size;
    res->dp = calloc(res->n + 1, sizeof(int));
    fill(res->dp, res->dp + res->n + 1, INT_MAX);
    return res;
}

bool matches(char x, char y){
    if(x == '`' && y == '*')    return true;
    return (x == y || (x == '*' && y != ' ' && y != '\n'));
}

void update(pattern* ptrn, char c, int ind){
    int n = ptrn->n;
    int* newdp = calloc(n + 1, sizeof(int));
    fill(newdp, newdp + n + 1, INT_MAX);
    for(int i = 1; i <= n; i++){
        if(ptrn->expr->s[i - 1] == '*'){
            newdp[i] = newdp[i - 1];
        }
        if(matches(ptrn->expr->s[i - 1], c)){
            if(newdp[i] > ptrn->dp[i - 1]){
                newdp[i] = ptrn->dp[i - 1];
            }
            if(ptrn->expr->s[i - 1] == '*' && newdp[i] > ptrn->dp[i]){
                newdp[i] = ptrn->dp[i];
            }
        }
    }
    newdp[0] = ind + 1; // maybe ind, TODO
    ptrn->dp = newdp;
}

void reset(pattern* ptrn, int start){
    fill(ptrn->dp, ptrn->dp + ptrn->n + 1, INT_MAX);
    ptrn->dp[0] = start;
}