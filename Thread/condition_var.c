/**
 * @file condition_var.c
 * @author Komorebi (2389895003@qq.com)
 * @brief  条件变量与互斥锁的使用
 *         注意生产者与消费者线程会争抢互斥锁，所以输出的结果可能不是5个一组的
 *         期望的功能是读或者写的一方，一直进行读写操作，直到缓冲区读完或者写满，暂时释放
 * @version 0.1
 * @date 2025-09-29
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count = 0;
// 初始化锁
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// 初始化条件变量
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;

/**
 * 生产者线程函数
 * 该函数实现生产者逻辑，不断生成数据并放入缓冲区
 * @param arg 线程参数，未使用
 * @return 返回NULL
 */
void *producer(void *arg) {
    int item = 0;
    pthread_mutex_lock(&mutex);
    while (1) {
        /* 获取互斥锁，确保对共享资源的独占访问 */
        // pthread_mutex_lock(&mutex);
        
        /* 等待缓冲区有空闲空间 */
        while (count == BUFFER_SIZE) {
            /* 当缓冲区已满时，释放锁并等待条件变量唤醒 */
            pthread_cond_wait(&cond, &mutex);
        }
        
        /* 将新生产的项目放入缓冲区 */
        buffer[count++] = item ++;
        printf("白月光发送了一个幸运数字%d\n", buffer[count - 1]);
        
        /* 通知等待的消费者线程有新数据可消费 */
        // pthread_cond_signal(&cond);
        // pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_unlock(&mutex);
}
/**
 * 消费者线程函数
 * 从缓冲区中取出数据并处理
 * 
 * @param arg 线程参数，未使用
 * @return 返回NULL
 */
void *consumer(void *arg) {
    pthread_mutex_lock(&mutex);
    while (1) {
        // 获取互斥锁，拿不到等
        // pthread_mutex_lock(&mutex);
        
        // 如果缓冲区空，等生产者产生数据
        while (count == 0) {
            // 暂停线程，等待唤醒
            pthread_cond_wait(&cond, &mutex);
        }
        
        printf("我接收到了幸运数字%d\n", buffer[--count]);
        
        // 通知生产者 可以发送数据了
        // 唤醒生产者 同时解锁
        pthread_cond_signal(&cond);
        // pthread_mutex_unlock(&mutex);
    }
    pthread_mutex_unlock(&mutex);
}

int main(int argc, char const *argv[]) {
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    return 0;
}