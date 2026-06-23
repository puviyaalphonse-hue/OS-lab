#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <io.h>

int main()
{
    int fd;

    fd = open("foo.txt", O_RDONLY | O_CREAT, 0666);

    printf("fd = %d\n", fd);

    if (fd == -1)
    {
        printf("Error Number = %d\n", errno);
        perror("Program");
    }

    close(fd);

    return 0;
}