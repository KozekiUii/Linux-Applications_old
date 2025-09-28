#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void *task(void *arg) {
    printf("task start\n");
    sleep(1); // 模拟耗时
    printf("task end\n");
    return NULL;
}
int main(int argc, char const *argv[]) {
    pthread_t tid;

    // 创建线程, 并不会直接运行
    pthread_create(&tid, NULL, task, NULL);
    // 使用pthread_detach()让线程自动回收资源
    pthread_detach(tid);

    // 主线程继续工作
    printf("main thread continue\n");
    sleep(2);
    /**需要注意的是，pthread_detach 不会等待子线程结束，如果在后者执行完毕之前主线程退出，则整个进程退出
    * 子线程被强制终止，
    * 因此需要等待足够的时间确保子线程完成自己的任务
    */
    printf("main thread end\n");
    return 0;
}