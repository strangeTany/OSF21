#include <stdio.h>
#include <limits.h>
#include <float.h>

int main() {
    int INTEGER = INT_MAX;
    float FLOAT = FLT_MAX;
    double DOUBLE = DBL_MAX;
    
    printf("The size of integer type is %zu and its max value is %d\n", sizeof(INTEGER), INT_MAX);
    printf("The size of float type is %zu and its max value is %d\n", sizeof(FLOAT), FLT_MAX);
    printf("The size of double type is %zu and its max value is %d\n", sizeof(DOUBLE), DBL_MAX);
    

    return 0;
}
