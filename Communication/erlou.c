#include <stdio.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    if(argc != 2){
        printf("not enough arguments\n");
        return 1;
    }
    
    printf("i am %s %d, i will come to second floor\n", argv[1], getpid());
    return 0;
}