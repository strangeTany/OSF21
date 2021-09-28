#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct process
{
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
    int is_done;
    int remaining_execution_time;
};

struct process processes[100];

int compare_by_AT(const void* a, const void* b){
    struct process processA = *(struct process*)a;
    struct process processB = *(struct process*)b;

    if (processA.is_done)
        return 1;

    if (processB.is_done)
        return -1;

    return (processA.AT - processB.AT);
}

int get_index_of_last_arrived(int current_time, int n){
    for (int i = n - 1; i > -1; i--)
    {
        if (processes[i].AT <= current_time && !processes[i].is_done)
            return i;
    }
    
    return -1;
}

int main(){
    double average_TAT = 0;
    double average_WT = 0;

    printf("Enter number of processes: ");
    int n;
    scanf("%d",&n);

    printf("Enter quantum size: ");
    int quant;
    scanf("%d", &quant);

    printf("Enter Arrival time and Burst time for each process: \n");
    for (size_t i = 0; i < n; i++)
    {
        printf("Arrival time of process[%ld]: ", i+1);
        scanf("%d", &(processes[i].AT));

        printf("Burst time of process[%ld]: ", i+1);
        scanf("%d", &(processes[i].BT));

        processes[i].is_done = 0;
        processes[i].remaining_execution_time = processes[i].BT;
    }

    qsort(processes, n, sizeof(struct process), compare_by_AT);
    int current_time = 0;
    int index_of_last_arrived;

    int done_process_counter = 0;
    int i = 0;

    printf("P#\tAT\tBT\tCT\tTAT\tWT\n\n");
    while (1)
    {
        qsort(processes, n, sizeof(struct process), compare_by_AT);

        if (processes[0].is_done)
            break;


        index_of_last_arrived = get_index_of_last_arrived
    (current_time, n);

        while (index_of_last_arrived == -1)
        {
            current_time++;
            index_of_last_arrived = get_index_of_last_arrived
        (current_time, n);
        }
        
        if (i > index_of_last_arrived)
            i = 0;

        if (quant >= processes[i].remaining_execution_time){
            current_time += processes[i].remaining_execution_time;

            processes[i].remaining_execution_time = 0;
            processes[i].CT = current_time;
            processes[i].TAT = current_time - processes[i].AT;
            processes[i].WT = processes[i].TAT - processes[i].BT;
            processes[i].is_done = 1;

            average_TAT += processes[i].TAT;
            average_WT += processes[i].WT;

            done_process_counter++;
            printf("P%d\t%d\t%d\t%d\t%d\t%d\n", done_process_counter, processes[i].AT, processes[i].BT, processes[i].CT, processes[i].TAT, processes[i].WT);
        }
        else{
            current_time += quant;

            processes[i].remaining_execution_time -= quant;
            
            i++;
        }
    }

    average_WT /= n;
    average_TAT /= n;

    printf("\n");
    printf("Average Turnaround Time = %lf\n", average_TAT);
    printf("Average Waiting Time = %lf\n", average_WT);

    return 0;
}

/*
Imput:
Enter number of processes: 4
Enter quantum size: 1 (For RR)
Enter Arrival time and Burst time for each process: 
Arrival time of process[1]: 0
Burst time of process[1]: 1
Arrival time of process[2]: 1
Burst time of process[2]: 10
Arrival time of process[3]: 2
Burst time of process[3]: 1
Arrival time of process[4]: 3
Burst time of process[4]: 1
FCFS output:
P#      AT      BT      CT      TAT     WT
P1      0       1       1       1       0
P2      1       10      11      10      0
P3      2       1       12      10      9
P4      3       1       13      10      9
Average Turnaround Time = 7.750000
Average Waiting Time = 4.500000
SJN output:
P#      AT      BT      CT      TAT     WT
P1      0       1       1       1       0
P2      1       10      11      10      0
P3      2       1       12      10      9
P4      3       1       13      10      9
Average Turnaround Time = 7.750000
Average Waiting Time = 4.500000
RR output:
P#      AT      BT      CT      TAT     WT
P1      0       1       1       1       0
P2      2       1       3       1       0
P3      3       1       4       1       0
P4      1       10      13      12      2
Average Turnaround Time = 3.750000
Average Waiting Time = 0.500000
For this particular case RR is faster than other algorithms.
*/