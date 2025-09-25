#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

// 定义信号处理函数
void sigint_handler(int signum){
    printf("\n收到%d信号, 停止程序! \n", signum);
    exit(signum );
}
int main(int argc, char const *argv[]) {
    // 注册SIGINT信号处理函数，收到ctrl+c信号之后不执行默认的函数，而是执行新的注册函数
    if(signal(SIGINT, sigint_handler) == SIG_ERR){
        perror("注册新的信号处理函数失败\n");
        return 1;
    }

    // 无限循环等待信号
    while(1){
        sleep(1);
        printf("你好, 在吗?\n");
    }
    return 0;
}