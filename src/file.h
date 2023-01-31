#ifndef FILE_H
#define FILE_H

#define ROOT    "./vimr"
#define HIDDEN  "./vimr/.vim"

#include <stdio.h>
#include <stdbool.h>
#include "str.h"

bool file_exists(string *path);
string* create_file(string* path, int hidden);
string* file_to_str(FILE* f);
void print_file(FILE* f);

#endif