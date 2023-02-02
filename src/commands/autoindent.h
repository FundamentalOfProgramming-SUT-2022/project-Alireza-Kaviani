#ifndef AUTOINDENT_H
#define AUTOINDENT_H

#include "../file.h"
#include "../command.h"
#include "../undo.h"

#define TABSIZE 4

bool autoindent(FILE* outf, string* path);
bool run_autoindent(FILE* outf, command* cmd);

#endif