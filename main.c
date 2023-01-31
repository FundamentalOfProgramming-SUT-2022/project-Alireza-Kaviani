#include <stdio.h>
#include <sys/stat.h>
#include "src/vecstr.h"
#include "src/io.h"
#include "src/file.h"
#include "src/command.h"
#include "src/commands/createfile.h"

int main(){
    string* path = create_file(char_to_str(OUTPUT), 1);
    printstr(path);
    FILE* f = fopen(path->s, "w");
    read_command(f);

    fclose(f);
    return 0;
}