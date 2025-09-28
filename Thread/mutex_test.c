#include <pthread.h>
#include <complex.h>
#include <stdio.h>
#include <unistd.h>

#define THREAD_COUNT 20000

// 静态初始化，进程结束后，操作系统会自动回收进程所有资源，包括互斥锁，不需要显式销毁
// 如果互斥锁是动态分配的 (pthread_mutex_init函数初始化), 则需要显式销毁
static pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;

/**
 * @brief 线程函数，用于对传入的整数指针所指向的值进行自增操作
 * 
 * @param arg 指向整数的指针，该整数将被自增1
 * @return 返回NULL（void*类型）
 */
void *add_thread(void *arg) {
    int *p = arg;  // 将void指针转换为int指针
    // 累加之前加锁, 此时其他获取该锁的线程都会被阻塞
    pthread_mutex_lock(&counter_mutex);
    (*p)++;        // 对指针所指向的整数值进行自增操作
    // 累加完成，解锁
    pthread_mutex_unlock(&counter_mutex);
    return 0;      // 返回NULL
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