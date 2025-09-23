#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
int main(int argc, char *argv[])
{
    char *pipe_path = "/temp/myfifo";
    if (mkfifo( pipe_path, 0666)!= 0){
        perror("mkfifo");
        exit(EXIT_FAILURE);
    }

    // 对有名管道的特殊文件 创建fd
    int fd = open(pipe_path, O_RDWR);

    return 0;
}