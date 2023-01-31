#include <stdio.h>
#include <sys/stat.h>
#include "src/vecstr.h"
#include "src/io.h"
#include "src/file.h"

int main(){
    string* s = char_to_str("aboc");
    printstr(concat(s, s));
    printstr(s);
    s = create_string();
    while(read_word(s)){
        create_file(s, 0);
        s = create_string();
    }

    return 0;
}