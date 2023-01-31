#ifndef VECSTR_H
#define VECSTR_H

#include "str.h"

typedef struct{
    string* v;
    int cap, size;
} vecstr;

vecstr* create_vecstr();
void vector_resize(vecstr* vec, int n);
void push_back(vecstr* vec, string* str);

#endif