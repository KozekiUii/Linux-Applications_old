#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h> 
int main(int argc, char *argv[])
{
    char *pipe_path = "/tmp/myfifo";

    // 对有名管道的特殊文件 创建fd
    int fd = open(pipe_path, O_RDONLY);
    if (fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }
    char buf[100];

    ssize_t read_num;
    // 读取管道信息，写入到控制台
    while((read_num = read(fd, buf, sizeof( buf))) > 0){
        write(STDOUT_FILENO, buf, read_num);
    }
    if(read_num < 0){
        perror("read");
        close(fd);
        exit(EXIT_FAILURE);
    }

    printf("接受管道数据完成，进程终止\n");
    close(fd);

    return 0;
}