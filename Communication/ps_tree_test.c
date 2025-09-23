#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char const *argv[]){
    char *name = "老学员";
    printf("%s%d在一楼请进\n", name, getpid());
    __pid_t pid = fork();
    if (pid == -1) {
        printf("邀请新学员失败\n");
    }else if (pid == 0) {
        char *newName = "ergou";
        char *args[] = {"/home/komorebi/Documents/Workspace/shangguigu/Communication/erlou", newName, NULL};
        char *envs[] = {"/usr/local/sbin:/usr/local/bin:/usr/bin:/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl", NULL};
        int re = execve(args[0], args, envs);
        if (re == -1) {
            printf("新学员上二楼失败\n");
            return 1;
        }
    }else {
        printf("老学员%d邀请完%d之后还是在一楼学习\n", getpid(), pid);
        char bye = fgetc(stdin);
    }
    return 0;
}