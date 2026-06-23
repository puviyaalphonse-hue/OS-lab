#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <io.h>

#define BUFFER_SIZE 4096

void create()
{
    FILE *fp;

    fp = fopen("sasi.txt", "w");

    if (fp == NULL)
    {
        printf("File creation failed!\n");
        return;
    }

    fclose(fp);
    printf("File created successfully.\n");
}

void copyFile()
{
    int source_fd, dest_fd;
    char buffer[BUFFER_SIZE];
    int bytesRead;

    source_fd = open("sasi.txt", O_RDONLY);

    if (source_fd < 0)
    {
        printf("Source file not found!\n");
        return;
    }

    dest_fd = open("sk.txt",
                   O_WRONLY | O_CREAT | O_TRUNC,
                   0666);

    if (dest_fd < 0)
    {
        printf("Destination file creation failed!\n");
        close(source_fd);
        return;
    }

    while ((bytesRead = read(source_fd, buffer, BUFFER_SIZE)) > 0)
    {
        write(dest_fd, buffer, bytesRead);
    }

    close(source_fd);
    close(dest_fd);

    printf("File copied successfully.\n");
}

void deleteFile()
{
    if (remove("sasi.txt") == 0)
        printf("File deleted successfully.\n");
    else
        printf("File not found!\n");
}

int main()
{
    int choice;

    printf("1. Create\n");
    printf("2. Copy\n");
    printf("3. Delete\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            create();
            break;

        case 2:
            copyFile();
            break;

        case 3:
            deleteFile();
            break;

        default:
            printf("Invalid Choice!\n");
    }

    return 0;
}