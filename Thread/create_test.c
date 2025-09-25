#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define BUF_LEN 1024

char *buf;
// 读线程
void *input_thread(void *arg) {
    int i = 0;
    while (1) {
        char c = fgetc(stdin);
        if( c && c != '\n'){
            buf[i++] = c;
        }
        // 缓冲区索引溢出
        if( i >= BUF_LEN){
            i = 0;
        }
    }
}

// 写线程
void *output_thread(void *arg) {
    int i = 0;
    while (1) {
        if(buf[i]){
            // 读取一个字节写出到控制台 之后换行
            fputc(buf[i], stdout);
            fputc('\n', stdout);
            buf[i++] = 0;
            // 读取数据到最大下标
            if(i >= BUF_LEN){
                i = 0;
            }
        }else {
            // 如果当前还没有写入数据
            sleep(1);
        }
    }
}

// 读线程STDOUT_FILENO
/**
 * 程序实现创建两个线程
 * 线程1：读取控制台信息，写入到缓存中
 * 线程2：读取缓存中的信息，并打印到控制台
 */ 
int main(int argc, char const *argv[]) {
    // 初始化buf
    buf = malloc(BUF_LEN);
    // 创建两个线程
    pthread_t pid_input, pid_output;
    // 创建读线程
    pthread_create(&pid_input, NULL, (void *)input_thread, NULL);
    // 创建写线程
    pthread_create(&pid_output, NULL, (void *)output_thread, NULL);

    // 主线程等待读写双线程结束
    pthread_join(pid_input, NULL);
    pthread_join(pid_output, NULL);

    free(buf);
    return 0;
}