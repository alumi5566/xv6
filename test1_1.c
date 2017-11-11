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
#include "spinlock.h"


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

int main(void){
    
//int status;
int i=0, j=0;
printf( 1,"Hello world on xv6!!\n");
int pid = fork();
if(pid == 0){
	sleep(30);
	while(i++ < 30){
		printf(1,"child %d\n",i);
	}
	exit(getpid());
}else{
	while(j++ <30){
	    printf(1,"parent %d\n",j);
	    //wait(&status);
	    //waitpid(pid,&status,0);
	    //printf(1,"status = %d\n",status);
	}//wait(&status);
}
exit(0);
}


