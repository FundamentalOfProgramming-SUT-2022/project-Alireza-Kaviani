#ifndef STR_H
#define STR_H

typedef struct{
    char *s;
    int cap, size;
} string;

#define INITSIZE    10

string* create_string();
void str_resize(string* str, int n);
void append(string* str, char c);
void printstr(string* str);
string* strcopy(string* str);
string* char_to_str(char* c);

#endif