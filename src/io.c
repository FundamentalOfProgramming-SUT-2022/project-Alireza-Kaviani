#include "io.h"

#include <stdio.h>
#include <stdbool.h>

bool read_word(string* s){
    char c;
    do{
        c = getchar();
    } while(c == ' ');
    if(c == EOF || c == '\n'){
        return 0;
    }
    bool qu = false, bs = false;
    do{
        if(!qu && !bs && (c == ' ' || c == '\n'))
            break;
        if(bs){
            if(c == 'n')
                append(s, '\n');
            else if(c == 't')
                append(s, '\t');
            else if(c == '"')
                append(s, '"');
            else if(c == '\\')
                append(s, '\\');
            else
                append(s, c);
            bs = false;
            continue;
        }
        if(c == '\\')
            bs = true;
        else if(c == '"')
            qu = !qu;
        else
            append(s, c);
    } while((c = getchar()) != EOF);
    ungetc(c, stdin);
    return 1;
}

