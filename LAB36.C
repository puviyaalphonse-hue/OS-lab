#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Block
{
    char data[256];
    struct Block *next;
};

int main()
{
    struct Block *firstBlock = NULL;
    struct Block *lastBlock = NULL;
    struct Block *currentBlock;
    struct Block *newBlock;

    int blockCount = 0;
    int blockNumber;
    int i;

    char data[256];
    char choice;

    printf("Linked Allocation Simulation\n");

    while (1)
    {
        printf("\nEnter 'W' to write a block, 'R' to read a block, or 'Q' to quit: ");
        scanf(" %c", &choice);

        if (choice == 'Q' || choice == 'q')
        {
            break;
        }

        if (choice == 'W' || choice == 'w')
        {
            printf("Enter data for the block: ");
            scanf(" %[^\n]", data);

            newBlock = (struct Block *)malloc(sizeof(struct Block));

            if (newBlock == NULL)
            {
                printf("Memory allocation failed.\n");
                return 1;
            }

            strcpy(newBlock->data, data);
            newBlock->next = NULL;

            if (blockCount == 0)
            {
                firstBlock = newBlock;
                lastBlock = newBlock;
            }
            else
            {
                lastBlock->next = newBlock;
                lastBlock = newBlock;
            }

            blockCount++;

            printf("Block %d written successfully.\n", blockCount);
        }
        else if (choice == 'R' || choice == 'r')
        {
            if (blockCount == 0)
            {
                printf("No blocks available.\n");
                continue;
            }

            printf("Enter the block number to read (1-%d): ", blockCount);
            scanf("%d", &blockNumber);

            if (blockNumber < 1 || blockNumber > blockCount)
            {
                printf("Invalid block number.\n");
            }
            else
            {
                currentBlock = firstBlock;

                for (i = 1; i < blockNumber; i++)
                {
                    currentBlock = currentBlock->next;
                }

                printf("Block %d Data: %s\n",
                       blockNumber,
                       currentBlock->data);
            }
        }
        else
        {
            printf("Invalid choice.\n");
        }
    }

    currentBlock = firstBlock;

    while (currentBlock != NULL)
    {
        struct Block *nextBlock = currentBlock->next;
        free(currentBlock);
        currentBlock = nextBlock;
    }

    return 0;
}