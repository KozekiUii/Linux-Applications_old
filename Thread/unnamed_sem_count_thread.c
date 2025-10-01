#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>

// 宏定义：用于开启调试模式。如果不需要调试，可以注释掉这行。
// #define DEBUG

sem_t *full;
sem_t *empty;

int shared_num;
int counter;

int rand_num() {
    // 修正：这里不再调用 srand()，它应该只在 main 函数中被调用一次
    return rand();
}

void *producer(void *arg) {
    for(int i = 0; i < 5; i++){
#ifdef DEBUG
        sem_getvalue(empty, &counter);
        printf("empty: %d\n", counter);
#endif
        sem_wait(empty);
        printf("\n=========> 第 %d 轮数据传输 <=========\n\n", i+1);

#ifdef DEBUG
        sem_getvalue(empty, &counter);
        printf("empty: %d\n", counter);
#endif
        sleep(1);
        shared_num = rand_num();
        printf("producer has sent data\n");
        sem_post(full);

#ifdef DEBUG
        sem_getvalue(full, &counter);
        printf("full: %d\n", counter);
#endif
    }
}

void *consumer(void *arg) {
    for(int i = 0; i < 5; i++){

        sem_wait(full);
        printf("consumer has read data\n");
        printf("the shard_num is %d\n", shared_num);

#ifdef DEBUG
        sem_getvalue(full, &counter);
        printf("full: %d\n", counter);
#endif
        sleep(1);
        sem_post(empty);

#ifdef DEBUG
        sem_getvalue(empty, &counter);
        printf("empty: %d\n", counter);
#endif
    }
}

int main(int argc, char const *argv[]) {
    // 修正：srand() 函数只需要在程序开始时调用一次
    srand(time(NULL));

    full = malloc(sizeof(sem_t));
    empty = malloc(sizeof(sem_t));
    sem_init(full, 0, 0);
    sem_init(empty, 0, 1);

    pthread_t producer_id, consumer_id;
    pthread_create(&producer_id, NULL, producer, NULL);
    pthread_create(&consumer_id, NULL, consumer, NULL);

    pthread_join(producer_id, NULL);
    pthread_join(consumer_id, NULL);

    sem_destroy(full);
    sem_destroy(empty);
    free(full); // 释放分配的内存
    free(empty); // 释放分配的内存

    return 0;
}