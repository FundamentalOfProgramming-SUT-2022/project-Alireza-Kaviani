#include "str.h"

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

string* create_string(){
    string* str = malloc(sizeof(string));
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

void printstr(FILE* outf, string* str){
    fprintf(outf, "%s", str->s);
}

string* strcopy(string* str){
    string* res = create_string();
    res->s = calloc(str->cap, sizeof(char));
    memcpy(res->s, str->s, str->size + 1);
    res->size = str->size;
    res->cap = str->cap;
    return res;
}

string* char_to_str(char* c){
    int n = strlen(c);
    string* s = create_string();
    for(int i = 0; i < n; i++){
        append(s, c[i]);
    }
    return s;
}

string* concat(string* A, string* B){
    A = strcopy(A);
    for(int i = 0; i < B->size; i++){
        append(A, B->s[i]);
    }
    return A;
}

string* int_to_str(int x){
    char* c = calloc(INITSIZE, sizeof(char));
    sprintf(c, "%d", x);
    return char_to_str(c);
}