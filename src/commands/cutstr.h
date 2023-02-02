#ifndef CUTSTR_H
#define CUTSTR_H

#include "../file.h"
#include "../command.h"
#include "../undo.h"

bool cutstr(FILE* outf, string* path, int left, int right);
bool run_cutstr(FILE* outf, command* cmd);

#endif