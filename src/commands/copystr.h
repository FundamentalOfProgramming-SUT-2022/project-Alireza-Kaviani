#ifndef COPYSTR_H
#define COPYSTR_H

#include "../file.h"
#include "../command.h"
#include "../undo.h"

bool copystr(FILE* outf, string* path, int left, int right);
bool run_copystr(FILE* outf, command* cmd);

#endif