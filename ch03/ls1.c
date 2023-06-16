#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>

void do_ls(char[]);

void main(int ac, char* av[]) {
    if(ac == 1) {
        do_ls(".");
    } else {
        while(--ac) {
            printf("%s:\n", *++av);
            do_ls(*av);
        }
    }
}

void do_ls(char ch[]) {
    DIR* dir_ptr;
    struct dirent* direntp;
    if((dir_ptr = opendir(ch)) == NULL) {
        fprintf(stderr, "ls1: cannot open %s\n", ch);
    } else {
        while((direntp = readdir(dir_ptr)) != NULL) {
            printf("%s\n", direntp->d_name);
        }
        closedir(dir_ptr);
    }
}