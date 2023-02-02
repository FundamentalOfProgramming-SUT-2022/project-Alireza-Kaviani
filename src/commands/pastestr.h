#ifndef PASTESTR_H
#define PASTESTR_H

#include "../file.h"
#include "../command.h"
#include "../undo.h"

bool pastestr(FILE* outf, string* path, int pos);
bool run_pastestr(FILE* outf, command* cmd);

#endif