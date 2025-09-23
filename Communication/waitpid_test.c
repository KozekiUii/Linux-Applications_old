#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]){
    int subproccess_status;
    printf("老学员在校区\n");
    pid_t pid = fork();
    if(pid < 0){
        perror("fork");
        return 1;
    }else if (pid == 0) {
        char *args[] = {"/usr/bin/ping","-c", "50", "www.atguigu.com", NULL};
        char *envs[] = {NULL};
        printf("新学员%d 联系海哥 10 次\n", getpid());
        int exR = execve(args[0], args, envs);
        if(exR < 0){
            perror("execve");
            return 1;
        }
    }else {
        printf("老学员%d 等待新学员%d 联系\n", getpid(), pid);
        waitpid(pid, &subproccess_status, 0);
    }
    printf("老学员等待新学员联系完成\n");
    return 0;
}