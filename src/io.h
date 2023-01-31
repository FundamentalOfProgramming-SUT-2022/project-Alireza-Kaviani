#ifndef IO_H
#define IO_H

#include <stdio.h>
#include <stdbool.h>
#include "str.h"

bool read_word(string* s);
bool read_command(FILE* f);

#endif