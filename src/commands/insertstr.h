#ifndef INSERTSTR_H
#define INSERTSTR_H

#include "../file.h"
#include "../command.h"
#include "../undo.h"

bool insertstr(FILE* outf, string* path, string* str, int pos);
bool run_insertstr(FILE* outf, command* cmd);

#endif