#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>
struct process{
	int burst;
	int arrival;
	int no;
    int ct;
    int wt;
    int tat;
    int start_time;
    int rt;
    int bt_remaining;
};
int max(int a, int b){
    return (a>b) ? a:b;
}
int main()
{
int n,y=0,x=0,tq,index;
printf("Enter number of processes:\n");
	scanf("%d",&n);
	struct process p[10];
	printf("Enter the burst time:\n");
	int i,j;
    int queue[10];
    int front=-1,rear=-1;
    int completed=0,current_time=0;
    float sum_tat=0,sum_wt=0,sum_rt=0;
    bool visited[10]={false};
	for (i=0;i<n;i++){
		scanf("%d",&p[i].burst);
		p[i].no=i;
        p[i].bt_remaining=p[i].burst;
	}
	printf("Enter the arrival time:\n");
	for (i=0;i<n;i++){
		scanf("%d",&p[i].arrival);
	}
    printf("Enter time quantum:\n");
    scanf("%d",&tq);
    for (i=0;i<n-1;i++){
		for (j=0;j<n-i-1;j++){
			if (p[j].arrival > p[j+1].arrival){
				int temp = p[j].arrival;  
				p[j].arrival=p[j+1].arrival;
        		p[j+1].arrival = temp; 
        			
        		temp = p[j].burst;  
				p[j].burst=p[j+1].burst;
        		p[j+1].burst = temp; 
        			
    			temp = p[j].no;  
				p[j].no=p[j+1].no;
    			p[j+1].no = temp; 
			}
		}
	}
	front=rear=0;
    queue[rear]=0;    
    visited[0] = true;
    printf("Gant chart:\n");
    while(completed!=n){
        index=queue[front];
        front++;
        printf("| P%d- ",index);
        if(p[index].bt_remaining == p[index].burst)
        {
            p[index].start_time = max(current_time,p[index].arrival);
            current_time =  p[index].start_time;  
        }
        if(p[index].bt_remaining-tq > 0)
        {    
            printf("%d",tq);
            p[index].bt_remaining -= tq;
            current_time += tq;
        }
        else{
            printf("%d",p[index].bt_remaining);
            current_time += p[index].bt_remaining;
            p[index].bt_remaining = 0;
            completed++;

            p[index].ct = current_time;
            p[index].tat = p[index].ct - p[index].arrival;
            p[index].wt = p[index].tat - p[index].burst;
            p[index].rt = p[index].start_time - p[index].arrival;

            sum_tat += p[index].tat;
            sum_wt += p[index].wt;
            sum_rt += p[index].rt;
        }
        for(int i = 1; i < n; i++) 
        {
          if(p[i].bt_remaining > 0 && p[i].arrival <= current_time && visited[i] == false) 
          {
            //q.push(i);
            queue[++rear]=i;
            visited[i] = true;
          }
        }
        if(p[index].bt_remaining>0){
            //q.push(index);
            queue[++rear]=index;
        }
        if(front>rear)
        {
            for(int i = 1; i < n; i++)
            {
                if(p[i].bt_remaining > 0)
                {
                queue[rear++]=i;
                visited[i] = true;
                break;
                }
            }
        }
    }
    printf("\nProcess No.\tAT\tCPU Burst Time\tCT\tTAT\tWT\tRT\tStart Time\n");
    for(int i=0;i<n;i++){
        printf("%d\t\t%d\t%d\t\t%d\t%d\t%d\t%d\t%d\n",p[i].no,p[i].arrival,p[i].burst,p[i].ct,p[i].tat,p[i].wt,p[i].rt,p[i].start_time);
    }
    printf("\n");
    printf("\nAverage Turn Around time= %f ",(float)sum_tat/n);
    printf("\nAverage Waiting Time= %f ",(float)sum_wt/n);
    printf("\nAverage Response Time= %f ",(float)sum_rt/n);
}
