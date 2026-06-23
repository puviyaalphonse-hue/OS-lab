#include <stdio.h>
#include <stdlib.h>

int main()
{
    FILE *fp;
    char buffer[100];

    /* Create File */
    fp = fopen("sample.txt", "w");

    if (fp == NULL)
    {
        printf("Error creating file.\n");
        return 1;
    }

    printf("File 'sample.txt' created successfully.\n");

    fprintf(fp, "Hello, World!\n");

    printf("Data written to 'sample.txt'.\n");

    fclose(fp);

    /* Open File for Reading */
    fp = fopen("sample.txt", "r");

    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    printf("File 'sample.txt' opened for reading.\n");

    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        printf("%s", buffer);
    }

    fclose(fp);

    /* Delete File */
    if (remove("sample.txt") == 0)
    {
        printf("\nFile 'sample.txt' deleted successfully.\n");
    }
    else
    {
        printf("\nError deleting file.\n");
    }

    return 0;
}