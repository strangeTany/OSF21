#include <stdio.h>
#include <dirent.h>

struct dirent *folder;

int main() {

    DIR *d;
    d = opendir("/");
    while ((folder = readdir(d)) != NULL) {

        printf("%s\n", folder->d_name);
    }

    closedir(d);
    return 0;
}
