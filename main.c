#include <stdio.h>
#include <sys/stat.h>
#include "src/vecstr.h"
#include "src/io.h"
#include "src/file.h"
#include "src/command.h"
#include "src/commands/createfile.h"
#include "src/undo.h"

int main(){
    //string* path = create_file(char_to_str(OUTPUT), 1);

    //FILE* f = fopen(path->s, "w");
    while(!read_command(stdout));

    /*fclose(f);
    f = fopen(path->s, "r");
    print_file(stdout, f);
    fclose(f);*/

    return 0;
}