#include <fcntl.h>
#include <time.h>
#include <mqueue.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(){
    char *mq_name = "/p_c_mq";
    struct mq_attr attr;

    attr.mq_flags = 0;
    attr.mq_maxmsg = 10;
    attr.mq_msgsize = 100;
    attr.mq_curmsgs = 0;

    // 创建或打开消息队列
    mqd_t mqdes = mq_open(mq_name, O_CREAT | O_RDWR, 0666, &attr);

    if(mqdes == (mqd_t)-1){
        perror("mq_open");
    }

    char write_buf[100];
    struct timespec time_info;

    while(1){
        // 清空写缓冲区
        memset(write_buf, 0, sizeof(write_buf));
    }
}