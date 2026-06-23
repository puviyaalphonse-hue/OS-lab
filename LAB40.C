#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main()
{
    char filename[] = "file.txt";

    /* Read and Write Permission */
    if (chmod(filename, S_IREAD | S_IWRITE) == 0)
    {
        printf("File permissions changed successfully.\n");
    }
    else
    {
        perror("chmod");
        return 1;
    }

    return 0;
}