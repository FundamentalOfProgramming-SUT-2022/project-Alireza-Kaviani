#include "command.h"
#include <string.h>
#include <stdlib.h>

#include "commands/createfile.h"
#include "commands/insertstr.h"
#include "commands/cat.h"
#include "commands/removestr.h"
#include "commands/copystr.h"
#include "commands/cutstr.h"
#include "commands/pastestr.h"
#include "commands/find.h"

#include "commands/undo.h"
#include "commands/autoindent.h"

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

bool run_command(FILE* outf, command* cmd){
    if(!strcmp(cmd->name->s, "createfile")){
        return run_createfile(outf, cmd);
    }
    if(!strcmp(cmd->name->s, "insertstr")){
        return run_insertstr(outf, cmd);
    }
    if(!strcmp(cmd->name->s, "cat")){
        return run_cat(outf, cmd);
    }
    if(!strcmp(cmd->name->s, "removestr")){
        return run_removestr(outf, cmd);
    }
    if(!strcmp(cmd->name->s, "copystr")){
        return run_copystr(outf, cmd);
    }
    if(!strcmp(cmd->name->s, "cutstr")){
        return run_cutstr(outf, cmd);
    }
    if(!strcmp(cmd->name->s, "pastestr")){
        return run_pastestr(outf, cmd);
    }
    if(!strcmp(cmd->name->s, "find")){
        return run_find(outf, cmd);
    }
    if(!strcmp(cmd->name->s, "undo")){
        return run_undo(outf, cmd);
    }
    if(!strcmp(cmd->name->s, "auto-indent")){
        return run_autoindent(outf, cmd);
    }
    return true;
}

/*
createfile DONE
insertstr DONE
cat DONE
removestr DONE
copystr DONE
cutstr DONE
pastestr DONE
find
replace
grep
undo DONE
auto-indent
compare
tree
*/