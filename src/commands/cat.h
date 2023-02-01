#ifndef CAT_H
#define CAT_H

#include "../file.h"
#include "../command.h"

bool cat(FILE* outf, string* path);
bool run_cat(FILE* outf, command* cmd);

#endif