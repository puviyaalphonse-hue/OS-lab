#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *file;

    file = fopen("example.txt", "w");

    if (file == NULL)
    {
        printf("Error creating file.\n");
        return 1;
    }

    fprintf(file, "This is an example file content.");

    fclose(file);

    printf("File created successfully.\n");

    return 0;
}