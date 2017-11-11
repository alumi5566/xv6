//#include "types.h"
//#include "stat.h"
//#include "user.h"

#include "param.h"
#include "types.h"
#include "stat.h"
#include "user.h"
#include "fs.h"
#include "fcntl.h"
#include "syscall.h"
#include "traps.h"
#include "memlayout.h"


uint rand (void)
{
   static uint z1 = 12345, z2 = 12345, z3 = 12345, z4 = 12345;
   uint b;
   b  = ((z1 << 6) ^ z1) >> 13;
   z1 = ((z1 & 4294967294U) << 18) ^ b;
   b  = ((z2 << 2) ^ z2) >> 27; 
   z2 = ((z2 & 4294967288U) << 2) ^ b;
   b  = ((z3 << 13) ^ z3) >> 21;
   z3 = ((z3 & 4294967280U) << 7) ^ b;
   b  = ((z4 << 3) ^ z4) >> 12;
   z4 = ((z4 & 4294967168U) << 13) ^ b;
   return (z1 ^ z2 ^ z3 ^ z4);
}

/*
int main(void){
    int status;
    int i=0, j=0;
    printf( 1,"Hello world on xv6!!\n");
    if(fork()==0){
	sleep(30);
	while(i++ < 50){
		printf(1,"child %d\n",i);
	}
	//for(int i=0;i<100;i++);
    }else{
	while(j++ <50){
		printf(1,"parent %d\n",j);
		wait(&status);
	}//wait(&status);
    }
    exit(0);
}
*/

int main(int argc, char ** argv){
    
    int begin = getpid();
    int pid = fork();
    int i;
    int status;
    if(pid > 0){
        for(i = 0; i < 15 && pid > 0; i++){
            pid = fork();
            if(pid < 0)
                printf(1,"errors occur!\n");
        }
        if (pid == 0){
            int j = 0;
            while(j++ < 1000);
            if(getpid() == begin+5) sleep(50);
            
            printf(1,"pid = %d\n",getpid());
            if(getpid() == begin+10){
                printf(1,"pid %d waiting for %d\n",begin+10,begin+5);
                int wpid = waitpid(begin+5,&status,0);
                printf(1,"success clean %d\n",wpid);
            }
            if(getpid() == begin+12){
                printf(1,"pid %d waiting for %d\n",begin+12,begin+5);
                int wpid = waitpid(begin+5,&status,0);
                if(wpid == -1)
                    printf(1,"no more waiting for %d\n",begin+5);
            }
            if(getpid() == begin+5)
                exit(5);
            exit(0);
        }
    }else if(pid == 0){
        int j = 0;
        while(j++ < 1000);
        exit(0);
    }
    int going = 1;
    while(going >= 0){
        going = wait(&status);
        printf(1,"kill %d process\n",going);
    };
    exit(0);
    return 0;
}


