#include "autoindent.h"

bool autoindent(FILE* outf, string* path){
    FILE *src, *dst;
    get_src_dst(&src, &dst, path);
    bool qu = false;
    char prv = '\n', cur;
    int depth = 0;
    while((cur = fgetc(src)) != EOF){
        if(qu){
            fputc(cur, dst);
            if(cur == '"' && prv != '\\'){
                qu = false;
            }
            prv = cur;
            continue;
        }
        if(cur == ' '){
            if(prv != ' ' && prv != '\n'){
                fputc(cur, dst);
                prv = cur;
            }
            continue;
        }
        if(cur == '\n'){
            if(prv != '\n'){
                fputc(cur, dst);
                prv = cur;
            }
            continue;
        }
        if(cur == '}'){
            depth--;
            if(prv != '\n'){
                fputc('\n', dst);
                prv = '\n';
            }
        }
        if(prv == '\n'){
            for(int i = 0; i < depth * TABSIZE; i++){
                fputc(' ', dst);
                prv = ' ';
            }
        }
        if(cur == '{' && prv != ' ' && prv != '\n'){
            fputc(' ', dst);
            prv = ' ';
        }
        fputc(cur, dst);
        prv = cur;
        if(cur == '"'){
            qu = true;
        }
        if(cur == '{' || cur == '}'){
            fputc('\n', dst);
            prv = '\n';
        }
        depth += (cur == '{');
    }
    fclose(src);
    fclose(dst);
    if(outf != NULL)
        fprintf(outf, "Done\n");
    return false;
}

bool run_autoindent(FILE* outf, command* cmd){
    string* path = cmd->oth->v;
    if(check_file(outf, path)){
        return true;
    }
    return autoindent(outf, path);
}