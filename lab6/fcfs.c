#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct process{
int burst;
int arrival;
int no;
};
int max(int a, int b){
return (a>b)? a:b;
}
int main()
{
int n,y=0,x=0;
printf("Enter number of processes:\n");
scanf("%d",&n);
struct process p[10];
printf("Enter the burst time\n");
int i,j;
for(i=0;i<n;i++){
scanf("%d",&p[i].burst);
p[i].no=i;
}printf("Enter the arrival time\n");
for(i=0;i<n;i++){
scanf("%d",&p[i].arrival);
}
for(i=0;i<n-1;i++)
{
for(j=0;j<n-i-1;j++)
{
if(p[j].arrival > p[j+1].arrival)
{
int temp=p[j].arrival;
p[j].arrival=p[j+1].arrival;
p[j+1].arrival=temp;

temp=p[j].burst;
p[j].arrival=p[j+1].burst;
p[j+1].burst=temp;

temp=p[j].no;
p[j].arrival=p[j+1].no;
p[j+1].no=temp;}}}
float sum1=0,sum2=0;
for(i=0;i<n;i++)
{
x=max(p[i].arrival,y);
y=x+p[i].burst;
int z=x-p[i].arrival;
int t=y-p[i].arrival;
sum1+=z;
sum2+=t;
printf("P%d: %d-%d\t waiting time: %d\t tat:%d\n",p[i].no,x,y,z,t);
}
float awt=sum1/n;
float atat=sum2/n;
printf("Average waiting time: %f\n",awt);
printf("Average Turn around time: %f\n",atat);
}
