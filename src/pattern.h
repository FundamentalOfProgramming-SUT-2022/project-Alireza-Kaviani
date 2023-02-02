#ifndef PATTERN_H
#define PATTERN_H

#include "str.h"
#include <stdbool.h>

typedef struct{
    string* expr;
    int n, *dp;
} pattern;

void fill(int* start, int* end, int val);
pattern* create_pattern(string* exp);
bool matches(char x, char y);
void update(pattern* ptrn, char c, int ind);
void reset(pattern* ptrn, int start);

#endif