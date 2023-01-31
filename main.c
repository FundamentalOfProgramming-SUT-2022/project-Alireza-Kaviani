#include <stdio.h>
#include "src/vecstr.h"
#include "src/io.h"

int main(){
    string* s = char_to_str("aboc");
    printstr(s); s = create_string();
    while(read_word(s)){
        printstr(s);
        s = create_string();
    }

    return 0;
}