#include <stdio.h>
#include <stdlib.h>

#define MAX_FRAMES 3

void printFrames(int frames[], int n)
{
    int i;

    for(i = 0; i < n; i++)
    {
        if(frames[i] == -1)
            printf(" - ");
        else
            printf(" %d ", frames[i]);
    }

    printf("\n");
}

int main()
{
    int frames[MAX_FRAMES];
    int usageHistory[MAX_FRAMES];
    int pageFaults = 0;
    int i, j, k;

    int referenceString[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
    int n = sizeof(referenceString) / sizeof(referenceString[0]);

    for(i = 0; i < MAX_FRAMES; i++)
    {
        frames[i] = -1;
        usageHistory[i] = 0;
    }

    printf("Reference String: ");

    for(i = 0; i < n; i++)
    {
        printf("%d ", referenceString[i]);
    }

    printf("\n\nPage Replacement Order:\n");

    for(i = 0; i < n; i++)
    {
        int page = referenceString[i];
        int pageFound = 0;

        /* Check for page hit */
        for(j = 0; j < MAX_FRAMES; j++)
        {
            if(frames[j] == page)
            {
                pageFound = 1;

                for(k = 0; k < MAX_FRAMES; k++)
                {
                    if(k != j)
                        usageHistory[k]++;
                }

                usageHistory[j] = 0;
                break;
            }
        }

        /* Page Fault */
        if(!pageFound)
        {
            printf("Page %d -> ", page);

            int lruPage = 0;

            for(j = 1; j < MAX_FRAMES; j++)
            {
                if(usageHistory[j] > usageHistory[lruPage])
                {
                    lruPage = j;
                }
            }

            int replacedPage = frames[lruPage];

            frames[lruPage] = page;
            usageHistory[lruPage] = 0;

            for(j = 0; j < MAX_FRAMES; j++)
            {
                if(j != lruPage)
                    usageHistory[j]++;
            }

            if(replacedPage == -1)
                printf("Load into empty frame: ");
            else
                printf("Replace %d with %d: ", replacedPage, page);

            printFrames(frames, MAX_FRAMES);

            pageFaults++;
        }
    }

    printf("\nTotal Page Faults: %d\n", pageFaults);

    return 0;
}