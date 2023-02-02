#include "io.h"
#include "command.h"
#include "file.h"

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
            else if(c == '*')
                append(s, '`');
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

bool read_command(FILE* outf){
    string* s = create_string();
    command* cmd = create_command();
    bool isname = true, isval = false, isempty = true;
    while(read_word(s)){
        isempty = false;
        if(isval && (s->s[0] == '-' || s->s[0] == '=')){
            push_back(cmd->val, char_to_str("true"));
            isval = false;
        }
        if(s->s[0] == '='){
            FILE* output = fopen(get_path(char_to_str(OUTPUT), 1)->s, "w");
            run_command(output, cmd);
            fclose(output);
            output = fopen(get_path(char_to_str(OUTPUT), 1)->s, "r");
            cmd = create_command();
            push_back(cmd->opt, char_to_str("--str"));
            push_back(cmd->val, file_to_str(output));
            isname = true;
            fclose(output);
        }
        else if(s->s[0] == '-'){
            push_back(cmd->opt, s);
            isval = true;
        }
        else if(isname){
            cmd->name = s;
            isname = false;
        }
        else if(isval){
            push_back(cmd->val, s);
            isval = false;
        }
        else{
            push_back(cmd->oth, s);
        }
        s = create_string();
    }
    if(isempty){
        return true;
    }
    if(isval){
        push_back(cmd->val, char_to_str("true"));
    }
    return run_command(outf, cmd);
}