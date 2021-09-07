//
// Created by strangetany on 01/09/2021.
//
#include <stdio.h>
void swap(int *xp, int *yp) {
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
}

void bubble_sort(int *array, int n) {
    int i, j;
    for (i = 0; i < n - 1; i++)

        // Last i elements are already in place
        for (j = 0; j < n - i - 1; j++)
            if (array[j] > array[j + 1])
                swap(&array[j], &array[j + 1]);

}

int main() {
    int array[] = {0, 4, 2, 13, 6, 8, 5};
    bubble_sort(array, 7);
    for (int i = 0; i < 7; ++i) {
        printf("%d\n", array[i]);
    }
    return 0;
}
