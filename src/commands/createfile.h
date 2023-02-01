#ifndef CREATEFILE_H
#define CREATEFILE_H

#include "../file.h"
#include "../command.h"

bool createfile(FILE* outf, string* path);
bool run_createfile(FILE* outf, command* cmd);

#endif