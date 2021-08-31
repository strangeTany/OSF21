#include <stdio.h>

int main() {
    printf("Please, enter a string: ");
    char line[100];
    int len = 0;
    
    scanf("%[^\n]", line);
    while (line[len] != '\0')
      len++;
      
    for (int i = len; i>=0; --i) {
        printf("%c", line[i]);
    }

    return 0;
}
