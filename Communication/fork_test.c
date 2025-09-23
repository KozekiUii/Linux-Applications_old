#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main(){
    printf("海哥教老学员%d 春暖花开!\n", getpid());
    pid_t pid = fork();
    if (pid < 0) {
        printf("fork error\n");
        return 1;
    }else if(pid == 0){
        printf("新学员%d 加入成功，他是老学员%d 推荐的\n", getpid(), getppid());
    }else {
        printf("老学员%d 继续加油, 他推荐了%d\n", getpid(),pid);
    }
    return 0;
}