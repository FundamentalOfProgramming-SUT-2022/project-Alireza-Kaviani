#ifndef REPLACE_H
#define REPLACE_H

#include "../file.h"
#include "../command.h"
#include "../undo.h"

bool replace(FILE* outf, string* path, string* expr, string* rep, int type);
bool run_replace(FILE* outf, command* cmd);

#endif