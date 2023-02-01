#ifndef REMOVESTR_H
#define REMOVESTR_H

#include "../file.h"
#include "../command.h"
#include "../undo.h"

bool removestr(FILE* outf, string* path, int left, int right);
bool run_removestr(FILE* outf, command* cmd);

#endif