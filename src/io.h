#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdbool.h>
#include "str.h"
#include "editor.h"

bool read_word(window* win, string* s);
bool read_command(FILE* outf, window* win);

#endif