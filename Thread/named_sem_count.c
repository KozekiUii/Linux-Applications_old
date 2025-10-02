//
// Created by komorebi on 2025/10/2.
//


#include <semaphore.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    const char *sem_name = "/named_sem";

    // 初始化有名信号量
    sem_t *sem = sem_open(sem_name, O_CREAT, 0666, 0);

    const pid_t pid = fork();
    if (pid > 0) {
        sem_wait(sem);
        printf("this is father\n");
        // 等待子进程执行完毕
        waitpid(pid, nullptr, 0);

        // 释放引用
        sem_close(sem);

        // 释放有名信号量,当没有进程引用时才能执行清除，且只执行一次
        if (sem_unlink(sem_name) == -1) {
            perror("sem_unlink");
        }
    }
    else if (pid == 0) {
        sleep(1);
        printf("this is son\n");
        sem_post(sem);
        // 释放引用
        sem_close(sem);
    }
    else {
        perror("fork");
    }

    return 0;
}
