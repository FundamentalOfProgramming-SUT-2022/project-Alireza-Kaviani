#include "command.h"
#include <string.h>
#include <stdlib.h>

#include "file.h"

#include "commands/createfile.h"
#include "commands/insertstr.h"
#include "commands/cat.h"
#include "commands/removestr.h"
#include "commands/copystr.h"
#include "commands/cutstr.h"
#include "commands/pastestr.h"
#include "commands/find.h"
#include "commands/replace.h"
#include "commands/grep.h"
#include "commands/undo.h"
#include "commands/autoindent.h"
#include "commands/compare.h"
#include "commands/tree.h"
#include "commands/save.h"
#include "commands/saveas.h"

command* create_command(){
    command* cmd = malloc(sizeof(command));
    cmd->name = create_string();
    cmd->opt = create_vecstr();
    cmd->val = create_vecstr();
    cmd->oth = create_vecstr();
    push_back(cmd->opt, char_to_str("--file"));
    push_back(cmd->val, char_to_str(OPENFILE));
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

bool run_command(FILE* outf, window* win, command* cmd){
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
    if(!strcmp(cmd->name->s, "replace")){
        return run_replace(outf, cmd);
    }
    if(!strcmp(cmd->name->s, "grep")){
        return run_grep(outf, cmd);
    }
    if(!strcmp(cmd->name->s, "undo")){
        return run_undo(outf, win);
    }
    if(!strcmp(cmd->name->s, "auto-indent")){
        return run_autoindent(outf, cmd);
    }
    if(!strcmp(cmd->name->s, "compare")){
        return run_compare(outf, cmd);
    }
    if(!strcmp(cmd->name->s, "tree")){
        return run_tree(outf, cmd);
    }
    if(!strcmp(cmd->name->s, "save")){
        return run_save(outf, win, cmd);
    }
    if(!strcmp(cmd->name->s, "saveas")){
        return run_saveas(outf, win, cmd);
    }
    if(!strcmp(cmd->name->s, "open")){
        open_file(win, cmd->oth->v);
        return false;
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