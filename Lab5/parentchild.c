#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
int main(void)
{
int status;
pid_t pid1;
pid1=fork();
if(pid1==0){
printf("Child process\n");
printf("PID %d\n",getpid());
printf("PPID %d \n",getppid());}
else if(pid1>0){
wait(&status);
printf("Parent process\n");
printf("PID %d\n",getpid());
printf("PPID %d\n",getppid());}
else
printf("Error");
return 0;
}
