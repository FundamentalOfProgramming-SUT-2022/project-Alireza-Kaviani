#ifndef FILE_H
#define FILE_H

#define ROOT        "./vimr"
#define HIDDEN      "./vimr/.vim"
#define OUTPUT      "/root/output.vim"
#define CLIPBOARD   "/root/clipboard.vim"

#include <stdio.h>
#include <stdbool.h>
#include "str.h"
#include "command.h"

string* get_path(string* path, int hidden);
bool file_exists(string *path);
string* create_file(string* path, int hidden);
bool check_file(FILE* outf, string* path);

void print_range(FILE* dst, FILE* src, int from, int to);
void print_file(FILE* dst, FILE* src);
string* file_to_str(FILE* src);
void copy_file(string* src, string* dst);

int pos_to_index(FILE* src, int line, int pos);
bool command_to_pos(FILE* outf, command *cmd, int* res);
bool command_to_range(FILE* outf, command *cmd, int* left, int* right);

#endif