#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char const *argv[]) {
    char *shm_value_name = "unnamed_sem_bin_process_condition_value";

    // 创建内存共享对象
    int value_fd = shm_open(shm_value_name, O_CREAT | O_RDWR, 0666);
    // 调整内存共享对象的大小
    ftruncate(value_fd, sizeof(int));
    // 将内存存共享对象映射到共享内存区域
    int *value = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, 
    MAP_SHARED, value_fd, 0);

    // 初始化共享变量的值
    *value = 0;

    int pid = fork();
    if (pid > 0) { 
        int tmp = *value + 1;
        sleep(1);
        *value = tmp;

        // 等待子进程结束
        waitpid(pid, NULL, 0);
        printf("this is parent process, child finished\n");
        printf("the final value is %d\n", *value);
    }else if (pid == 0) {
        int tmp = *value + 1;
        sleep(1);
        *value = tmp;
    }else {
        perror("fork");
    }

    // 无论父子进程，都需要解除共享内存的映射关系，并关闭共享对象的文件描述符
    if(munmap(value, sizeof(int)) == -1){
        perror("munmap");
    }
    if(close(value_fd) == -1){
        perror("close");
    }

    // 如果调用时别的进程仍在使用共享对象，则等待所有进程释放资源后，才会销毁相关资源
    // shm_unlink 只能调用一次，在父进程中调用shm_unlink
    if(pid > 0){
        // 销毁共享对象
        if(shm_unlink(shm_value_name) == -1){
            perror("shm_unlink");
        }
    }

}