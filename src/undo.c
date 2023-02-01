#include "undo.h"
#include "file.h"

int count_backups(string* path){
    int cnt = 1;
    while(file_exists(concat(path, int_to_str(cnt)))){
        cnt++;
    }
    return cnt - 1;
}

void save(string* path){
    string* hidden = get_path(path, 1);
    append(hidden, '_');
    int cnt = count_backups(hidden);
    for(int i = cnt; i >= 1; i--){
        string* src = concat(hidden, int_to_str(i));
        string* dst = concat(hidden, int_to_str(i + 1));
        copy_file(src, dst);
    }
    copy_file(get_path(path, 0), concat(hidden, int_to_str(1)));
}

void get_src_dst(FILE** src, FILE** dst, string* path){
    save(path);
    string* hidden = get_path(path, 1);
    append(hidden, '_'); append(hidden, '1');
    *src = fopen(hidden->s, "r");
    *dst = fopen(get_path(path, 0)->s, "w");
}