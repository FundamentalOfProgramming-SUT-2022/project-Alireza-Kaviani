#include "command.h"
#include <string.h>
#include <stdlib.h>

#include "commands/createfile.h"

#include "commands/cat.h"

command* create_command(){
    command* cmd = malloc(sizeof(command));
    cmd->name = create_string();
    cmd->opt = create_vecstr();
    cmd->val = create_vecstr();
    cmd->oth = create_vecstr();
    return cmd;
}

string* get_option(command* cmd, char* op){
    for(int i = 0; i < cmd->opt->size; i++){
        if(!strcmp(cmd->opt->v[i].s, op)){
            return &cmd->val->v[i];
        }
    }
    return create_string();
}

bool run_command(FILE* dst, command* cmd){
    if(!strcmp(cmd->name->s, "createfile")){
        return createfile(dst, cmd);
    }
    if(!strcmp(cmd->name->s, "cat")){
        return cat(dst, cmd);
    }
    return true;
}

/*
createfile DONE
insertstr
cat
removestr
copystr
cutstr
pastestr
find
replace
grep
undo
auto-indent
compare
tree
*/