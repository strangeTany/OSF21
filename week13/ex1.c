#include <stdio.h>
#include <stdlib.h>

int is_en(const int *requested_matrix, const int *free, int no_resources);

void free_res(const int *cur, int *free, int no_resources);

int main() {

    FILE *inp = fopen("input.txt", "r");

    int n; //resources number
    int m; //processes number

    fscanf(inp, "%d", &resources_num);
    fscanf(inp, "%d", &m);

    int exist[resources_num];
    int free[resources_num];
    int cur[resources_num][m];
    int req[resources_num][m];
    int is_finished[m];

    for (int i = 0; i < resources_num; ++i)
        fscanf(inp, "%d", &exist[i]);


    for (int i = 0; i < resources_num; ++i)
        fscanf(inp, "%d", &free[i]);


    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < resources_num; ++j)
            fscanf(inp, "%d", &cur[i][j]);

        is_finished[i] = 0;
    }

    for (int i = 0; i < m; ++i)
        for (int j = 0; j < resources_num; ++j)
            fscanf(inp, "%d", &requested_matrix[i][j]);

    for (int i = 0; i < m; ++i)
        for (int process = 0; process < m; ++process)
            if (is_finished[process] == 0 && is_en(requested_matrix[process], free, resources_num) == 1) {
                free_res(cur[process], free, resources_num);
                is_finished[process] = 1;
            }



    int is_deadlock = 0;
    for (int i = 0; i < m; ++i)
        if (is_finished[i] == 0) {
            is_deadlock = 1;
            printf("Process %d is in deadlock\n", i);
        }


    if (is_deadlock == 0)
        printf("No deadlock is detected\n");


    return 0;
}

int is_en(const int *requested_matrix, const int *free, int no_resources) {
    for (int i = 0; i < no_resources; ++i)
        if (requested_matrix[i] > free[i])
            return 0;


    return 1;
}

void free_res(const int *cur, int *free, int no_resources) {
    for (int i = 0; i < no_resources; ++i)
        free[i] += cur[i];

}