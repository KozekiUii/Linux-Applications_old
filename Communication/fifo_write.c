#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
<<<<<<< HEAD
int main(int argc, char *argv[])
{
    char *pipe_path = "/tmp/myfifo";
=======
#include <errno.h>
int main(int argc, char *argv[])
{
    char *pipe_path = "/tmp/myfifo3";
    // 检查FIFO是否存在，不存在则创建
    if(access(pipe_path, F_OK) == -1){
>>>>>>> 51c1a7db3fe516fa9f67d89778d0e7dfae4de73c
        if (mkfifo( pipe_path, 0664)!= 0){
            perror("mkfifo");
            exit(EXIT_FAILURE);
        }
<<<<<<< HEAD
=======
    }

>>>>>>> 51c1a7db3fe516fa9f67d89778d0e7dfae4de73c

    // 对有名管道的特殊文件 创建fd
    int fd = open(pipe_path, O_RDWR);
    if (fd == -1){
        perror("open");
        exit(EXIT_FAILURE);
    }
    char buf[100];
<<<<<<< HEAD
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
=======
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
>>>>>>> 51c1a7db3fe516fa9f67d89778d0e7dfae4de73c

    printf("发送数据到管道完成，进程终止\n");
    close(fd);

<<<<<<< HEAD
    // 关闭管道
    if(unlink(pipe_path) == -1){
        perror("fifo_write unlink");
    }

=======
>>>>>>> 51c1a7db3fe516fa9f67d89778d0e7dfae4de73c
    return 0;
}