#include <stdio.h>
#include <stdlib.h>

struct process
{
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
};

int compare(const void* a, const void* b){
    return ((*(struct process*)a).AT - (*(struct process*)b).AT);
}


int main(){
    struct process processes[100];

    printf("Enter number of processes: ");
    int n;
    scanf("%d",&n);

    printf("Enter Arrival time and Burst time for each process: \n");
    for (size_t i = 0; i < n; i++)
    {
        printf("Arrival time of process[%ld]: ", i+1);
        scanf("%d", &(processes[i].AT));

        printf("Burst time of process[%ld]: ", i+1);
        scanf("%d", &(processes[i].BT));
    }

    double average_TAT = 0;
    double average_WT = 0;

    qsort(processes, n, sizeof(struct process), compare);

    printf("P#\tAT\tBT\tCT\tTAT\tWT\n\n");
    for (size_t i = 0; i < n; i++)
    {
        if (i == 0){
            processes[i].CT = processes[i].BT + processes[i].AT;
            processes[i].TAT = processes[i].BT;
            processes[i].WT = processes[i].TAT - processes[i].BT;
        }
        else{
            if (processes[i].AT > processes[i-1].CT){
                processes[i].CT = processes[i].AT + processes[i].BT;
            }
            else{
                processes[i].CT = processes[i-1].CT + processes[i].BT;
            }
            processes[i].TAT = processes[i].CT - processes[i].AT;
            processes[i].WT = processes[i].TAT - processes[i].BT;
        }

        printf("P%ld\t%d\t%d\t%d\t%d\t%d\n", i+1, processes[i].AT, processes[i].BT, processes[i].CT, processes[i].TAT, processes[i].WT);

        average_TAT += processes[i].TAT;
        average_WT += processes[i].WT;
    }

    average_TAT /= n;
    average_WT /= n;

    printf("\n");
    printf("Average Turnaround Time = %lf\n", average_TAT);
    printf("Average Waiting Time = %lf\n", average_WT);

    return 0;
}