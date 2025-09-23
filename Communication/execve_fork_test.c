#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>


int main(int argc, char *argv[]){
    char *name = "old student";
    printf("%s %d, still on first floor\n", name, getpid());
    __pid_t pid = fork();

    if(pid < 0){
        perror("fork");
    }else if(pid == 0){
        char *newName = "ergou";
        char *argv[] = {"/home/komorebi/Documents/Workspace/shangguigu/Communication/erlou", newName, NULL};
        char *envp[] = {"PATH=/usr/local/sbin:/usr/local/bin:/usr/bin:/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl",
                newName};
        int re = execve(argv[0], argv, envp);
        if(re < 0){
            perror("execve");
            return 1;
        }
    }else {
        printf("old student %d, recommend new student %d, still on first floor\n", getpid(), pid);
    }
    return 0;
}