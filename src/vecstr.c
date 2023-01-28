#include "vecstr.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

vecstr* create_vecstr(){
    vecstr* vec = malloc(sizeof(vecstr));
    vec->v = calloc(INITSIZE, sizeof(string));
    vec->cap = INITSIZE;
    vec->size = 0;
    return vec;
}

void vector_resize(vecstr* vec, int n){
    string* newV = calloc(n, sizeof(string));
    memcpy(newV, vec->v, vec->size * sizeof(string));
    vec->v = newV;
    vec->cap = n;
}

void push_back(vecstr* vec, string str){
    if(vec->size == vec->cap){
        vector_resize(vec, vec->cap * 2);
    }
    vec->v[vec->size++] = *strcopy(&str);
    return;
}