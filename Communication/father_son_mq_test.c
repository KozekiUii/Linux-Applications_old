#include <bits/time.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <mqueue.h>
#include <sys/stat.h>


int main(int argc, char const *argv[]){
    // 创建消息队列
    struct mq_attr attr;
    // 有用的参数，表示消息队列的容量
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
    // 忽略的消息 表示创建消息队列的时候用不到
    attr.mq_flags = 0;
    attr.mq_curmsgs = 0;

    char *mq_name = "/father_son_mq";
    struct timespec time_info;
    mqd_t mqdes = mq_open(mq_name, O_CREAT | O_RDWR, 0664, &attr);
    if(mqdes == (mqd_t)-1){
        perror("mq_open");
        exit(EXIT_FAILURE);
    }
    // 创建子进程
    pid_t pid = fork();
    if(pid == -1){
        perror("fork");
        exit(EXIT_FAILURE);
    }
    // 子进程
    if(pid == 0){
        // 子进程 等待接收消息队列中的消息
        char read_buf[100];
        struct timespec time_info;
        for(size_t i = 0; i < 10; i++){
            // 清空接收数据的缓冲区
            memset(read_buf, 0, sizeof(read_buf));
            // 设置接收数据的等待时间
            clock_gettime(CLOCK_REALTIME, &time_info);
            time_info.tv_sec += 15;
            // 发送消息
            if(mq_timedreceive(mqdes, read_buf, sizeof(read_buf), NULL, &time_info) == -1){
                perror("mq_timedread");
            }
            printf("子进程接收到数据%s\n", read_buf);
        }
    }
    else {
        // 父进程 发送消息
        char send_buf[100];
        struct timespec time_info;

        for(size_t i = 0; i < 10; i++){
            // 清空处理buf
            memset(send_buf, 0, sizeof(send_buf));
            sprintf(send_buf, "父进程的第%d次发送消息\n", (int)(i+1));
            clock_gettime(CLOCK_REALTIME, &time_info);
            time_info.tv_sec += 5;
            // 发送消息
            if(mq_timedsend(mqdes, send_buf, sizeof(send_buf), 0, &time_info) == -1){
                perror("mq_timedsend");
            }
            printf("父进程发送了一条数据, 休眠1s\n");
            sleep(1);
        }
    }
    // 不管是父进程还是子进程都需要释放消息队列
    close(mqdes);
    // 清除消息队列只需要执行一次
    if(pid > 0){
        mq_unlink(mq_name);
    }
    return 0;
}