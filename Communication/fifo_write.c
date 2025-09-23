#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
int main(int argc, char *argv[])
{
    char *pipe_path = "/tmp/myfifo3";
    // 检查FIFO是否存在，不存在则创建
    if(access(pipe_path, F_OK) == -1){
        if (mkfifo( pipe_path, 0664)!= 0){
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
    }


    // 对有名管道的特殊文件 创建fd
    int fd = open(pipe_path, O_RDWR);
    if (fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }
    char buf[100];
    ssize_t read_num;
    // 读取控制台数据，写入到管道中
    while((read_num = read(STDIN_FILENO, buf, sizeof( buf))) > 0){
        write(fd, buf, read_num);
    }
    if(read_num < 0){
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("发送数据到管道完成，进程终止\n");
    close(fd);

    return 0;
}