/**
 * @file    rwlock_write_hungry.c
 * @author  Komorebi
 * @brief   写饥饿测试
 *          读写锁的写饥饿问题是指在使用读写锁时，写线程可能无限期地等待获取写锁，因为读线程持续的获取读锁而不断地推迟写线程执行
 *          这种情况通常出现在读操作远多于写操作时出现
 * @version 0.1
 * @date 2025-09-27
 * 
 * @copyright Copyright (c) 2025
 * 
 */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t rwlock;
int shared_data = 0;

/**
 * @brief 写操作
 * 加锁
 * @param arg 
 * @return void* 
 */
void *lock_writer(void *arg) {
    // 给多个线程添加写锁
    // 同一时间只能有一个线程获取写锁，会造成两个线程顺序执行
    printf("我%s要获取写锁\n", (char *)arg);
    pthread_rwlock_wrlock(&rwlock);
     int tmp = shared_data + 1;
    //  sleep(1);
     shared_data = tmp;
     printf("this is %s, shared_data: %d\n", (char *)arg, shared_data);
     pthread_rwlock_unlock(&rwlock);
     printf("我%s要释放写锁\n", (char *)arg);
}

/**
 * @brief 读操作
 * 加锁
 * 
 * @param arg 
 * @return void* 
 */
 void *lock_reader(void *arg) {
    printf("我%s要获取读锁\n", (char *)arg);
    // 加锁
    pthread_rwlock_rdlock(&rwlock);
    printf("this is %s, shared_data=%d\n", (char *)arg, shared_data);
    sleep(1);
    // 释放锁
    pthread_rwlock_unlock(&rwlock);
    printf("我%s要释放读锁\n", (char *)arg);
}
int main(int argc, char const *argv[]) {

    pthread_rwlock_init(&rwlock, NULL);

    pthread_t writer1, writer2, reader1, reader2, reader3, reader4, reader5, reader6;
    
    // 线程的执行顺序由操作系统内核调度，不可以简单的理解为“先创建先执行”
    pthread_create(&writer1, NULL, lock_writer, "writer1");
    
    // sleep(3);
    pthread_create(&reader1, NULL, lock_reader, "reader1");
    pthread_create(&reader2, NULL, lock_reader, "reader2");
    pthread_create(&reader3, NULL, lock_reader, "reader3");
    // 在线程读取数据的时候，中间添加一个获取写锁的操作
    pthread_create(&writer2, NULL, lock_writer, "writer2");

    pthread_create(&reader4, NULL, lock_reader, "reader4");
    pthread_create(&reader5, NULL, lock_reader, "reader5");
    pthread_create(&reader6, NULL, lock_reader, "reader6");

    pthread_join(writer1, NULL);
    pthread_join(writer2, NULL);
    pthread_join(reader1, NULL);
    pthread_join(reader2, NULL);
    pthread_join(reader3, NULL);
    pthread_join(reader4, NULL);
    pthread_join(reader5, NULL);
    pthread_join(reader6, NULL);

    pthread_rwlock_destroy(&rwlock);

    return 0;
}