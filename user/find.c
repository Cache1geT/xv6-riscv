#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

void find(char *path,char *pattern){
    char buf[512],*p;
    int fd;
    struct dirent de;
    struct stat st;
    char dot[DIRSIZ],ddot[DIRSIZ];
    dot[0]='.';
    ddot[0]='.';
    ddot[1]='.';

    if((fd=open(path,0))<0){
        fprintf(2,"find: cannot open %s\n",path);
        return;
    }

    strcpy(buf,path);
    p=buf+strlen(buf);
    *p++='/';

    while(read(fd,&de,sizeof(de))==sizeof(de)){
        memmove(p,de.name,DIRSIZ);
        p[DIRSIZ]=0;
        if(stat(buf,&st)<0){
            printf("find: cannot stat %s\n",buf);
        }
        switch(st.type){
            case T_FILE:
                //compare
                if(!strcmp(pattern,de.name)){
                    printf("%s\n",buf);
                }
                
            case T_DIR:
                //recursion
                if(!strcmp(dot,de.name) && !strcmp(ddot,de.name)){
                    find(buf,pattern);
                }
        }
    }
}
int main(int argc,char *argv[]){
    if(argc!=3){
        printf("find usage: find directory pattern");
        exit(1);
    }
    find(argv[1],argv[2]);
    exit(0);
}
