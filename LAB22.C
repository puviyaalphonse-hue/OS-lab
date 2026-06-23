#include <stdio.h>

#define MAX_MEMORY 1000

int memory[MAX_MEMORY];

/* Initialize Memory */
void initializeMemory()
{
    int i;

    for(i = 0; i < MAX_MEMORY; i++)
    {
        memory[i] = -1;
    }
}

/* Display Memory Status */
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

            printf("Free memory block %d-%d\n", i, j - 1);

            i = j - 1;
        }
    }

    if(count == 0)
    {
        printf("No free memory available.\n");
    }
}

/* Worst Fit Allocation */
void allocateMemory(int processId, int size)
{
    int i, j;
    int start;
    int currentSize;

    int worstStart = -1;
    int worstSize = 0;

    for(i = 0; i < MAX_MEMORY; )
    {
        if(memory[i] == -1)
        {
            start = i;
            currentSize = 0;

            while(i < MAX_MEMORY && memory[i] == -1)
            {
                currentSize++;
                i++;
            }

            if(currentSize >= size && currentSize > worstSize)
            {
                worstSize = currentSize;
                worstStart = start;
            }
        }
        else
        {
            i++;
        }
    }

    if(worstStart != -1)
    {
        for(j = worstStart; j < worstStart + size; j++)
        {
            memory[j] = processId;
        }

        printf("Allocated memory block %d-%d to Process %d\n",
               worstStart,
               worstStart + size - 1,
               processId);
    }
    else
    {
        printf("Memory allocation for Process %d failed (not enough contiguous memory).\n",
               processId);
    }
}

/* Deallocate Memory */
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