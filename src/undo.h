#ifndef UNDO_H
#define UNDO_H

#include <stdio.h>
#include "str.h"

int count_backups(string* path);
void save(string* path);
void get_src_dst(FILE** src, FILE** dst, string* path);
void undo(string* path);

#endif