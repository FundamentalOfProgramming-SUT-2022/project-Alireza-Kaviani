#ifndef FIND_H
#define FIND_H

#include "../file.h"
#include "../command.h"

bool find(FILE* outf, string* path, string* expr, int type, int* l, int* r);
bool run_find(FILE* outf, command* cmd);

#endif