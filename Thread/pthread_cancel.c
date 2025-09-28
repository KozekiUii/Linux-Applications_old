#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *task(void *arg) {
    printf("Thread start\n");

    // 默认取消类型为无延迟，无需设置，立即响应

    // 模拟工作
    printf("Working...\n");
    sleep(1);       // 模拟工作
    pthread_testcancel();   // 取消点函数
    printf("After Cancelled\n");

    return NULL;
}
int main(int argc, char const *argv[]) {
    pthread_t tid;
    void *res;

    // 创建线程, 并不会直接运行
    pthread_create(&tid, NULL, task, NULL);
    // 取消子线程（只是发送取消信号，并不一定能取消）
    if(pthread_cancel(tid) != 0){
        perror("pthread_cancel");
    }

    // 等待子线程结束，res 为取消线程返回值，
    pthread_join(tid, &res);

    // 检查子线程是否被取消
    if( res == PTHREAD_CANCELED ){
        printf("Thread was canceled\n");
    }
    else {
        printf("Thread was not canceled, exit code: %ld\n", (long)res);
    }

    return 0;
}