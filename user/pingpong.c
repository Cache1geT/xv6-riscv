#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc,char *argv[]){
    int p1[2];
    int p2[2];
    pipe(p1);
    pipe(p2);
    int pid=fork();
    if(pid==0){//child
        pid=getpid();
        char r='x';
        read(p1[0],&r,1);
        printf("%d: received ping\n",pid);
        write(p2[1],&r,1);
    }
    else{//parent
        pid=getpid();
        char r='x';
        write(p1[1],"a",1);
        read(p2[0],&r,1);
        printf("%d: received pong\n",pid);
    }
    exit(0);
}
