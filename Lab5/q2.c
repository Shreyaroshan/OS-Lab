#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<string.h>
void bubble_sort(char *arr[],int n){
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
int main(int argc,char *argv[]){
    int status;
    if (argc<2){
        printf("Please provide some strings as command line arguments.\n");
        return 1;
    }
    int pid=fork();
    if (pid==0){
        bubble_sort(&argv[1],argc-1);
        printf("Sorted strings (Child Process):\n");
        for (int i = 1; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
    }
    else if(pid>0){
        wait(&status);
        printf("\nUnsorted strings (Parent Process):\n");
        for (int i = 1; i < argc; i++) {
            printf("%s\n", argv[i]);
        }
    }
}
