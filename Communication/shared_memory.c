#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <string.h>

int main(int argc, char *argv[]){
    char *share;
    pid_t pid;
    char shmName[100] = {0};
    sprintf(shmName, "/letter%d", getpid());
    int fd;
    fd = shm_open(shmName, O_CREAT | O_RDWR, 0664);
    if(fd == -1){
        perror("共享内存创建失败");
        exit(EXIT_FAILURE);
    }
    // 将共享内存的大小设置为100字节
    ftruncate(fd, 100);
    // 将共享内存映射到进程的地址空间
    share = (char *)mmap(NULL, 100, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if(share == MAP_FAILED){
        perror("共享内存映射失败");
        exit(EXIT_FAILURE);
    }
    // 映射区建立完成，关闭读取连接，注意不是删除
    close(fd);
    // 创建子进程
    pid = fork();
    if(pid == 0){
        strcpy(share, "hello, i am child process");
        printf("子进程%d写入数据\n", getpid());
        // 解除子进程映射
        int ret_1 = munmap(share, 100);
        if(ret_1 == -1){
            perror("子进程解除映射失败");
            _exit(EXIT_FAILURE);
        }
    }else if(pid > 0){
        // 父进程等待1秒
        sleep(1);
        strcpy(share, "hello, i am parent process");
        printf("父进程%d读到子进程%d写的数据: %s\n" , getpid(), pid,share);
        // 等待子进程结束
        wait(NULL);
        // 解除父进程映射
        int ret_2 = munmap(share, 100);
        if(ret_2 == -1){
            perror("父进程解除映射失败");
            exit(EXIT_FAILURE);
        }
        // 删除共享内存
        shm_unlink(shmName);
        printf("共享内存删除完成\n");
        return 0;
    }

}