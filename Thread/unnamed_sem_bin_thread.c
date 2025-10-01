#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

sem_t unnamed_sem;
int shared_num = 0;

void *plusOne(void *arg) {
    sem_wait(&unnamed_sem);
    int tmp = shared_num + 1;
    shared_num = tmp;
    sem_post(&unnamed_sem);
}
int main(int argc, char const *argv[]) {
    // 初始化信号量, 0表示是线程信号量, 1表示是进程信号量
    sem_init(&unnamed_sem, 0, 1);
    pthread_t tid[10000];

    for (int i = 0; i < 10000; i++) {
        pthread_create(tid + i, NULL, plusOne, NULL);
    }

    for(int i = 0; i < 10000; i++){
        pthread_join(tid[i], NULL);
    }

    printf("shared_num = %d\n", shared_num);

    return 0;
}