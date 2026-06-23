#include <stdio.h>
#include <stdlib.h>

int main()
{
    int n, head, seek_time = 0;
    int i, j;

    printf("Enter the number of disk requests: ");
    scanf("%d", &n);

    int request_queue[n];

    printf("Enter the disk request queue:\n");

    for(i = 0; i < n; i++)
    {
        scanf("%d", &request_queue[i]);
    }

    printf("Enter the initial position of the disk head: ");
    scanf("%d", &head);

    /* Sort request queue */
    for(i = 0; i < n - 1; i++)
    {
        for(j = i + 1; j < n; j++)
        {
            if(request_queue[i] > request_queue[j])
            {
                int temp = request_queue[i];
                request_queue[i] = request_queue[j];
                request_queue[j] = temp;
            }
        }
    }

    printf("\nC-SCAN Disk Scheduling:\n");
    printf("Head Movement Sequence: %d", head);

    int pos = 0;

    while(pos < n && request_queue[pos] < head)
    {
        pos++;
    }

    /* Service requests to the right */
    for(i = pos; i < n; i++)
    {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];

        printf(" -> %d", head);
    }

    /* Jump to beginning */
    if(pos > 0)
    {
        seek_time += abs(head - request_queue[0]);
        head = request_queue[0];

        printf(" -> %d", head);
    }

    /* Service remaining requests */
    for(i = 1; i < pos; i++)
    {
        seek_time += abs(head - request_queue[i]);
        head = request_queue[i];

        printf(" -> %d", head);
    }

    printf("\nTotal Seek Time: %d\n", seek_time);
    printf("Average Seek Time: %.2f\n", (float)seek_time / n);

    return 0;
}