#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define max(a,b) (((a)>(b))?(a):(b))

struct process
{
    int AT;
    int BT;
    int CT;
    int TAT;
    int WT;
};

struct process processes[100];

int compare_by_AT(const void* a, const void* b){
    return (((struct process*)a)->AT - ((struct process*)b)->AT);
}

int compare_by_BT(const void* a, const void* b){
    return (((struct process*)a)->BT - ((struct process*)b)->BT);
}

int get_index_of_last_arrived(int current_time, int number_of_procosses){
    for (int i = number_of_procosses - 1; i > -1; i--)
    {
        if (processes[i].AT <= current_time)
            return i;
    }
    
    return -1;
}

int main(){
    
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

    qsort(processes, n, sizeof(struct process), compare_by_AT);
    int current_time = 0;
    int index_of_last_arrived;
    double average_TAT = 0;
    double average_WT = 0;

    printf("P#\tAT\tBT\tCT\tTAT\tWT\n\n");
    for (size_t i = 0; i < n; i++)
    {
        qsort(processes, n, sizeof(struct process), compare_by_AT);
        index_of_last_arrived = get_index_of_last_arrived(current_time, n);

        while (index_of_last_arrived == -1)
        {
            current_time++;
            index_of_last_arrived = get_index_of_last_arrived(current_time, n);
        }
        

        qsort(processes, index_of_last_arrived + 1, sizeof(struct process), compare_by_BT);

        current_time = processes[0].BT + max(processes[0].AT, current_time);
        processes[0].CT = current_time;
        processes[0].TAT = current_time - processes[0].AT;
        processes[0].WT = processes[0].TAT - processes[0].BT;

        printf("P%ld\t%d\t%d\t%d\t%d\t%d\n", i+1, processes[0].AT, processes[0].BT, processes[0].CT, processes[0].TAT, processes[0].WT);

        average_TAT += processes[0].TAT;
        average_WT += processes[0].WT;
        
        processes[0].AT = INT_MAX;
        processes[0].BT = INT_MAX;
    }

    average_WT /= n;
    average_TAT /= n;

    printf("\n");
    printf("Average Turnaround Time = %lf\n", average_TAT);
    printf("Average Waiting Time = %lf\n", average_WT);

    return 0;
}
