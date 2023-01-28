#include "str.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

string* create_string(){
    string* str = (string*) malloc(sizeof(string));
    str->s = calloc(INITSIZE, sizeof(char));
    str->cap = INITSIZE;
    str->size = 0;
    return str;
}

void str_resize(string* str, int n){
    char* newS = calloc(n, sizeof(char));
    memcpy(newS, str->s, str->size + 1);
    str->s = newS;
    str->cap = n;
}

void append(string* str, char c){
    if(str->size + 1 >= str->cap){
        str_resize(str, str->cap * 2);
    }
    str->s[str->size++] = c;
}

void print(string* str){
    printf("%s\n", str->s);
}

string* strcopy(string* str){
    string* res = create_string();
    res->s = calloc(str->cap, sizeof(char));
    memcpy(res->s, str->s, str->size + 1);
    res->size = str->size;
    res->cap = str->cap;
    return res;
}