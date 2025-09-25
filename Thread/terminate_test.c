#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <string.h>

// 定义结果结构体
typedef struct Result{
    char *p;
    int len;
} Result;

// 红玫瑰线程
void *red_thread(void *arg){ 
    Result *result = malloc(sizeof(Result));
    char code = *((char *)arg);
    char *ans = malloc(101);
    while (1) {
        fgets(ans, sizeof(ans), stdin);
        if(ans[0] == code){
            // 接收到了对应的信息
            free(ans);
            printf("红玫瑰离开了！");
            char *redAns = strdup("红玫瑰独自去了纽约。\n");
            result->p = redAns;
            result->len = strlen(redAns);
            // 线程结束，输出返回值
            pthread_exit(result);
        }else {
            printf("红玫瑰还在等你！\n ");
        }
    }
}
// 白玫瑰线程
void *white_thread(void *arg){
    Result *result = malloc(sizeof(Result));
    char code = *((char *)arg);
    char *ans = malloc(101);
    while (1) {
        fgets(ans, sizeof(ans), stdin);
        if(ans[0] == code){
            // 接收到了对应的信息
            free(ans);
            printf("白玫瑰离开了！");
            char *whiteAns = strdup("白玫瑰独自去了纽约。\n");
            result->p = whiteAns;
            result->len = strlen(whiteAns);
            // 线程结束，输出返回值
            pthread_exit(result);
        }else {
            printf("白玫瑰还在等你！\n ");
        }
    }
}

int main(int argc, char const *argv[]) {
    pthread_t pid_red;
    pthread_t pid_white;
    char red_code = 'r';
    char white_code = 'w';
    Result *red_result = NULL;
    Result *white_result = NULL;
    // 创建红玫瑰线程
    pthread_create(&pid_red, NULL, (void *)&red_thread, &red_code);
    // 创建白玫瑰线程
    pthread_create(&pid_white, NULL, (void *)&white_thread, &white_code);
    // 获取红玫瑰结果
    pthread_join(pid_red, (void **)&red_result);
    printf("红玫瑰故事结局：%s\n", red_result->p);
    // 释放内存
    free(red_result->p);
    free(red_result);
    
    // 获取白玫瑰结果
    pthread_join(pid_white, (void **)&white_result);
    printf("白玫瑰故事结局：%s\n", white_result->p);

    // 释放内存
    free(white_result->p);
    free(white_result);

    return 0;
}