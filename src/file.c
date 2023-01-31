#include "file.h"
#include <sys/stat.h>

string* get_path(string* path, int hidden){
    string* cur = create_string();
    string* res = create_string();
    for(int i = 1; i < path->size; i++){
        if(path->s[i] == '/'){
            if(cur->s[0] != '/'){
                cur = (hidden ? char_to_str(HIDDEN) : char_to_str(ROOT));
            }
            res = concat(res, cur);
            mkdir(res->s, 0777);
            cur = char_to_str("/");
            continue;
        }
        append(cur, path->s[i]);
    }
    res = concat(res, cur);
    return res;
}

bool file_exists (string* path){
    struct stat buffer;
    return (stat(get_path(path, 0)->s, &buffer) == 0);
}

string* create_file(string* path, int hidden){
    string* res = get_path(path, hidden);
    FILE* f = fopen(res->s, "w");
    fclose(f);
    return res;
}