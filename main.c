#include <stdio.h>
#include <sys/stat.h>
#include "src/io.h"
#include "src/file.h"

int main(){
    mkdir(ROOT, 0777);
    while(!read_command(stdout));

    return 0;
}