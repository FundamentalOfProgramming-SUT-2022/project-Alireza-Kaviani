#include "io.h"
#include "command.h"
#include "file.h"

#include <stdio.h>
#include <stdbool.h>

bool flag = false;

bool read_word(window* win, string* s){
    if(flag){
        return false;
    }
    char c = '!';
    do{
        c = (read_char(win));
    } while(c == ' ');
    if(c == EOF || c == '\n'){
        win->command = char_to_str("DONE");
        return false;
    }
    bool qu = false, bs = false;
    do{
        if(!qu && !bs && (c == ' ' || c == '\n'))
            break;
        append(win->command, c);
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
    } while((c = read_char(win)) != EOF);
    append(win->command, ' ');
    if(c == '\n'){
        flag = true;
    }
    return true;
}

bool read_pattern(window* win, string* pattern){
    flag = false;
    return read_word(win, pattern);
}

bool read_command(FILE* outf, window* win){
    flag = false;
    string* s = create_string();
    command* cmd = create_command();
    bool isname = true, isval = false, isempty = true;
    while(read_word(win, s)){
        isempty = false;
        if(isval && (s->s[0] == '-' || s->s[0] == '=')){
            push_back(cmd->val, char_to_str("true"));
            isval = false;
        }
        if(s->s[0] == '='){
            FILE* output = fopen(get_path(char_to_str(TMPFILE), 1)->s, "w");
            fclose(output);
            output = fopen(get_path(char_to_str(TMPFILE), 1)->s, "r");
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
    return run_command(outf, win, cmd);
}