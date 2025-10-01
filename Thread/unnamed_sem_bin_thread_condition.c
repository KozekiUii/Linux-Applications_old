#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <semaphore.h>

int shared_num = 0;

void *plusOne(void *arg) {
    int tmp = shared_num + 1;
    shared_num = tmp;
}
int main(int argc, char const *argv[]) {
    pthread_t tid[10000];

    for (int i = 0; i < 10000; i++) {
        pthread_create(tid + i, NULL, plusOne, NULL);
    }

    for(int i = 0; i < 10000; i++){
        pthread_join(tid[i], NULL);
    }

    printf("shared_num = %d\n", shared_num);

    return 0;
}