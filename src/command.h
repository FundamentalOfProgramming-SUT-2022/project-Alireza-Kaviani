#ifndef COMMAND_H
#define COMMAND_H

#include <stdio.h>
#include <stdbool.h>
#include "vecstr.h"

typedef struct{
    string* name;
    vecstr* opt;
    vecstr* val;
    vecstr* oth;
} command;

command* create_command();
string* get_option(command* cmd, char* op);
bool run_command(FILE* f, command* cmd);

#endif