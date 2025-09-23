#include <endian.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    char *name = "laoxueyuan";
    printf("i am %s %d, i am on first floor\n", name, getpid());
    char *argv[] = {"/home/komorebi/Documents/Workspace/shangguigu/Communication/erlou", name, NULL};
    char *envp[] = {"/usr/local/sbin:/usr/local/bin:/usr/bin:/usr/bin/site_perl:/usr/bin/vendor_perl:/usr/bin/core_perl",
                name, NULL};
    int re = execve(argv[0], argv, envp);
    if(re == -1){
        perror("execve");
        return -1;
    }
    return 0;
}