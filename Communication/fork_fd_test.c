#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main()
{
    int fd = open("io.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd < 0){
        perror("open");
        exit(EXIT_FAILURE);
    }
    char buffer[1024];
    pid_t pid = fork();
    if (pid < 0){
        perror("fork");
        exit(EXIT_FAILURE);
    }else if (pid == 0) {
        strcpy(buffer, "这是子进程写入的数据！\n");
    }else {
        sleep(1);
        printf("父进程计时结束\n");
        strcpy(buffer, "这是父进程写入的数据！\n");
    }

    // 两个进程都要执行
    ssize_t bytes_write = write(fd, buffer, strlen(buffer));
    
    if (bytes_write < 0){
        perror("write");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("写入数据成功\n");
    close(fd);
    if(pid == 0){
        printf("子进程写入数据成功,释放文件描述符\n");
    }else {
        printf("父进程写入数据成功,释放文件描述符\n");
    }
    return 0;
}