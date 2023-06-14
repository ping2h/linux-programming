/* who1.c - a first version of the who program open, read Utmp file
 and show results 
 */
#include <stdio.h>
#include <utmp.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define SHOWHOST
void show_time(time_t);
void show_info(struct utmp*);
int main() {
    struct utmp current_record;
    int utmpfd;
    int reclen = sizeof(current_record);

    if ((utmpfd = open(UTMP_FILE, O_RDONLY)) == -1) {
        perror(UTMP_FILE);
        exit(1);
    }
    while (read(utmpfd, &current_record, reclen) == reclen)
    {
        show_info(&current_record);
    }
    close(utmpfd);
    return 0;
}

void show_info(struct utmp* str) {
    if (str->ut_type != USER_PROCESS) {
        return;
    }
    printf("%-8.8s",str->ut_user); // Username
    printf(" ");
    printf("%-8.8s",str->ut_line); // Device name of tty
    printf(" ");
    show_time(str->ut_time);
    // printf("%-8d",str->ut_tv.tv_sec); // ut_time
    printf(" ");
#ifdef SHOWHOST
    printf("%-8s",str->ut_host); // host name for remote login
    printf(" ");
#endif
    printf("\n");
}

void show_time(time_t t) {
    char* ch = ctime(&t);
    printf("%12.12s", ch+4);
}