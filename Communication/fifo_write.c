#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
int main(int argc, char *argv[])
{
    char *pipe_path = "/tmp/myfifo";
        if (mkfifo( pipe_path, 0664)!= 0){
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }

    // 对有名管道的特殊文件 创建fd
    int fd = open(pipe_path, O_RDWR);
    if (fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }
    char buf[100];
    // ssize_t read_num;
    char *p;
    // 读取控制台数据，写入到管道中
    // (read_num = read(STDIN_FILENO, buf, sizeof( buf))) > 0
    while((p = fgets(buf, sizeof(buf), stdin)) != NULL){
        write(fd, buf, strlen(buf));
    }

    // if(p == NULL){
    //     perror("read");
    //     close(fd);
    //     exit(EXIT_FAILURE);
    // }

    printf("发送数据到管道完成，进程终止\n");
    close(fd);

    // 关闭管道
    if(unlink(pipe_path) == -1){
        perror("fifo_write unlink");
    }

    return 0;
}