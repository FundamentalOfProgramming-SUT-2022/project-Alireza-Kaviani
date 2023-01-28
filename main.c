#include <stdio.h>
#include "src/vecstr.h"

int main(){
    vecstr vec = *create_vecstr();
    string s = *create_string();
    for(int i = 0; i < 26; i++){
        append(&s, 'a' + i);
        push_back(&vec, s);
    }
    for(int i = 0; i < vec.size; i++){
        print(&vec.v[i]);
    }

    return 0;
}