#ifndef SAVE_H
#define SAVE_H

#include "../file.h"
#include "../command.h"
#include "../editor.h"

bool run_save(FILE* outf, window* win, command* cmd);

#endif