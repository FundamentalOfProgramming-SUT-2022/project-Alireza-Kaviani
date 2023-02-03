#ifndef GREP_H
#define GREP_H

#include "../file.h"
#include "../command.h"

int* build_kmp(string* s);
int count_file(FILE* outf, string* path, string* s, int* kmp, int print);
bool grep(FILE* outf, vecstr* files, string* s, int type);
bool run_grep(FILE* outf, command* cmd);

#endif