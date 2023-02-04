#include "command.h"
#include "../io.h"

void command_mode(window* win){
    FILE* outf = fopen(get_path(char_to_str(OUTPUT), 1)->s, "w");
    read_command(outf, win);
    fclose(outf);
    win->mode = NORMAL;
}