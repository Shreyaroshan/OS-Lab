#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include<limits.h>
struct process{
int burst;
int arrival;
int priority;
int no;
int ct;
int wt;
int tat;
int rt;
int start_time;
};
int main()
{
int n;
printf("Enter no of processes\n");
scanf("%d",&n);
struct process p[10];
printf("Enter burst time\n");
int i,j;
for(i=0;i<n;i++)
{
scanf("%d",&p[i].burst);
p[i].no=i;
}
printf("Enter arrival time\n");
for(i=0;i<n;i++)
{
scanf("%d",&p[i].arrival);
}
printf("Enter priority\n");
for(i=0;i<n;i++)
{
scanf("%d",&p[i].priority);
}
float sum_tat=0,sum_wt=0,sum_rt=0;
int completed=0,current_time=0;
bool is_completed[10]={false};
while(completed!=n)
{
int min_index=-1;
int minimum=INT_MAX;
for(i=0;i<n;i++)
{
if(p[i].arrival<=current_time && is_completed[i]==false)
{
if(p[i].priority<minimum)
{
minimum=p[i].priority;
min_index=i;
}
if(p[i].priority==minimum)
{
if(p[i].burst<p[min_index].burst)
{
minimum=p[i].priority;
min_index=i;
}
}
}
}
if(min_index==-1)
current_time++;
else
{
p[min_index].start_time=current_time;
p[min_index].ct=p[min_index].start_time+p[min_index].burst;
p[min_index].tat=p[min_index].ct-p[min_index].arrival;
p[min_index].wt=p[min_index].tat-p[min_index].burst;
p[min_index].rt=p[min_index].wt;

sum_tat +=p[min_index].tat;
            sum_wt += p[min_index].wt;
            sum_rt += p[min_index].rt;
            completed++;
            is_completed[min_index]=true;
            current_time = p[min_index].ct;
            }
}
printf("\nProcess No.\tAT\tBurst\tCT\tTAT\tWT\tRT\tStart Time\n");
for(i=0;i<n;i++)
{
printf("%d\t\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",p[i].no,p[i].arrival,p[i].burst,p[i].ct,p[i].tat,p[i].wt,p[i].rt,p[i].start_time);
}
printf("\n");
    printf("\nAverage Turn Around time= %f ",(float)sum_tat/n);
    printf("\nAverage Waiting Time= %f ",(float)sum_wt/n);
    printf("\nAverage Response Time= %f ",(float)sum_rt/n);
}
