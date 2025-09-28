#include <pthread.h>
#include <complex.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define THREAD_COUNT 20000

void *add_thread(void *arg) {
    int *p = arg;
    (*p)++;
    return 0;   // 自动调整为void*
}
int main(int argc, char const *argv[]) {
    pthread_t pid[THREAD_COUNT];
    int num = 0;
    // 用 200000 个线程对 num 作累加
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_create(pid + i, NULL, add_thread, &num);
    }

    // 等待所有线程结束
    for (int i = 0; i < THREAD_COUNT; i++) {
        pthread_join(pid[i], NULL);
    }
    // 打印累加结果
    printf("num = %d\n", num);
    return 0;
}