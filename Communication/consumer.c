#include <bits/time.h>
#include <time.h>
#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    char *mq_name = "/p_c_mq";

    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
    attr.mq_curmsgs = 0;

    // 创建或打开消息队列
    mqd_t mqdes = mq_open(mq_name, O_CREAT | O_RDWR, 0666, &attr);

    if (mqdes == -1) {
        perror("mq_open");
    }

    char readBuf[100];
    struct timespec time_info;
    while(1){
        // 清空读缓冲区
        memset(readBuf, 0, sizeof(readBuf));

        // 获取1天后的time_spec结构对象，目的是测试期间使得消费者一直等待生产者发送的数据
        clock_gettime(CLOCK_REALTIME, &time_info);
        time_info.tv_sec += 86400;

        // 接收数据
        if(mq_timedreceive(mqdes, readBuf, sizeof(readBuf), NULL, &time_info) == -1){
            perror("mq_timedreceive");
        }

        // 如果收到生产者发送的EOF，则结束进程
        if(readBuf[0] == EOF){
            printf("接收到生产者的终止信号，准备退出\n");
            break;
        }
        // 如果没有收到EOF,将接收到的数据打印到标准输出
        printf("接收到来自生产者的数据：%s\n", readBuf);
    }

    // 释放消息队列描述符
    close(mqdes);

    // mq_unlink只调用一次
    // 清除消息队列
    mq_unlink(mq_name);

    return 0;
}