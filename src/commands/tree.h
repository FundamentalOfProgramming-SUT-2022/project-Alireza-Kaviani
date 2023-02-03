#ifndef TREE_H
#define TREE_H

#include "../file.h"
#include "../command.h"

void print_tree(FILE* outf, string* path, int maxdepth, int depth);
bool tree(FILE* outf, string* path, int maxdepth);
bool run_tree(FILE* outf, command* cmd);

#endif