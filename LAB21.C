#include <stdio.h>

#define MAX_MEMORY 1000

int memory[MAX_MEMORY];

/* Initialize memory */
void initializeMemory()
{
    int i;

    for(i = 0; i < MAX_MEMORY; i++)
    {
        memory[i] = -1;
    }
}

/* Display memory status */
void displayMemory()
{
    int i, j;
    int count = 0;

    printf("\nMemory Status:\n");

    for(i = 0; i < MAX_MEMORY; i++)
    {
        if(memory[i] == -1)
        {
            count++;
            j = i;

            while(j < MAX_MEMORY && memory[j] == -1)
            {
                j++;
            }

            printf("Free memory block %d - %d\n", i, j - 1);

            i = j - 1;
        }
    }

    if(count == 0)
    {
        printf("No free memory available.\n");
    }
}

/* Allocate memory */
void allocateMemory(int processId, int size)
{
    int start = -1;
    int blockSize = 0;
    int i;

    for(i = 0; i < MAX_MEMORY; i++)
    {
        if(memory[i] == -1)
        {
            if(blockSize == 0)
            {
                start = i;
            }

            blockSize++;
        }
        else
        {
            blockSize = 0;
        }

        if(blockSize >= size)
        {
            break;
        }
    }

    if(blockSize >= size)
    {
        for(i = start; i < start + size; i++)
        {
            memory[i] = processId;
        }

        printf("Allocated memory block %d - %d to Process %d\n",
               start,
               start + size - 1,
               processId);
    }
    else
    {
        printf("Memory allocation for Process %d failed.\n",
               processId);
    }
}

/* Deallocate memory */
void deallocateMemory(int processId)
{
    int i;

    for(i = 0; i < MAX_MEMORY; i++)
    {
        if(memory[i] == processId)
        {
            memory[i] = -1;
        }
    }

    printf("Memory released by Process %d\n", processId);
}

int main()
{
    initializeMemory();

    displayMemory();

    allocateMemory(1, 200);
    displayMemory();

    allocateMemory(2, 300);
    displayMemory();

    deallocateMemory(1);
    displayMemory();

    allocateMemory(3, 400);
    displayMemory();

    return 0;
}