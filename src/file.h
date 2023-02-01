#ifndef FILE_H
#define FILE_H

#define ROOT    "./vimr"
#define HIDDEN  "./vimr/.vim"
#define OUTPUT  "/root/output"

#include <stdio.h>
#include <stdbool.h>
#include "str.h"

string* get_path(string* path, int hidden);
bool file_exists(string *path);
string* create_file(string* path, int hidden);
bool check_file(FILE* outf, string* path);

void print_range(FILE* dst, FILE* src, int from, int to);
void print_file(FILE* dst, FILE* src);
string* file_to_str(FILE* src);

void copy_file(string* src, string* dst);

#endif