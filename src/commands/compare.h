#ifndef COMPARE_H
#define COMPARE_H

#include "../file.h"
#include "../command.h"

bool compare(FILE* outf, string* path1, string* path2);
bool run_compare(FILE* outf, command* cmd);

#endif