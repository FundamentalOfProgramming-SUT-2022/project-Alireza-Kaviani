#ifndef UNDO_H
#define UNDO_H

#include <stdio.h>
#include "str.h"
#include "editor.h"

int count_backups(string* path);
void save(window* path);
void get_src_dst(FILE** src, FILE** dst, string* path);
void undo(window* win);

#endif