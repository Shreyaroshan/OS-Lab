#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<string.h>
#include <stdlib.h>
void bubbleSort(char *arr[], int n) {
    char *temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (strcmp(arr[j], arr[j + 1]) > 0) {
                temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}
void selectionSort(char *arr[], int n) {
    int minIdx;
    char *temp;
    for (int i = 0; i < n - 1; i++) {
        minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (strcmp(arr[j], arr[minIdx]) < 0) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            temp = arr[i];
            arr[i] = arr[minIdx];
            arr[minIdx] = temp;
        }
    }
}
int main(){
    int status,n;
    printf("Enter the number of strings: ");
    scanf("%d", &n);
    //printf("\n");
    char **strings=(char **)malloc(n*sizeof(char *));
    for (int i=0;i<n;i++){
        strings[i]=(char *)malloc(100*sizeof(char));
        printf("\nEnter string %d: ", i + 1);
        scanf("%s", strings[i]);
    }
    printf("\n");
    pid_t pid1=fork();
    if (pid1==0){
        printf("\nFirst child process (Bubble Sort):\n");
        bubbleSort(strings, n);
        for (int i = 0; i < n; i++) {
            printf("%s\n", strings[i]);
        }
        exit(0);
    }
    pid_t pid2=fork();
    if (pid2==0){
        printf("\nSecond child process (Selection Sort):\n");
        selectionSort(strings, n);
        for (int i = 0; i < n; i++) {
            printf("%s\n", strings[i]);
        }
        exit(0);
    }
    pid_t finishedPid = wait(&status);
    if (finishedPid == pid1) {
        printf("\nParent process: First child (Bubble Sort) has finished.\n");
    } else if (finishedPid == pid2) {
        printf("\nParent process: Second child (Selection Sort) has finished.\n");
    }
    for (int i = 0; i < n; i++) {
        free(strings[i]);
    }
    free(strings);
}
