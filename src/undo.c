#include "undo.h"
#include "file.h"

int count_backups(string* path){
    int cnt = 1;
    while(file_exists(concat(path, int_to_str(cnt)))){
        cnt++;
    }
    return cnt - 1;
}

void save(window* win){
    string* path = win->path;
    string* hidden = get_path(path, 1);
    append(hidden, '_');
    int cnt = count_backups(hidden);
    for(int i = cnt; i >= 1; i--){
        string* src = concat(hidden, int_to_str(i));
        string* dst = concat(hidden, int_to_str(i + 1));
        copy_file(src, dst);
    }
    copy_file(get_path(path, 0), concat(hidden, int_to_str(1)));
    copy_file(get_path(char_to_str(OPENFILE), 1), get_path(path, 0));
    win->issaved = true;
}

void get_src_dst(FILE** src, FILE** dst, string* path){
    string* open = get_path(char_to_str(OPENFILE), 1);
    string* tmp = get_path(char_to_str(TMPFILE), 1);
    copy_file(open, tmp);
    *src = fopen(tmp->s, "r");
    *dst = fopen(open->s, "w");
}

void undo(string* path){
    string* hidden = get_path(path, 1);
    append(hidden, '_');
    int cnt = count_backups(hidden);
    if(cnt == 0){
        return;
    }
    copy_file(concat(hidden, int_to_str(1)), get_path(path, 0));
    for(int i = 1; i < cnt; i++){
        string* src = concat(hidden, int_to_str(i + 1));
        string* dst = concat(hidden, int_to_str(i));
        copy_file(src, dst);
    }
}