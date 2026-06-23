#include <stdio.h>
#include <stdlib.h>

struct Block
{
    int blockNumber;
    char data[256];
};

int main()
{
    FILE *file;
    struct Block block;
    int blockNumber;

    long indexBlock[100];

    int i;
    for(i = 0; i < 100; i++)
    {
        indexBlock[i] = -1;
    }

    /* Open file for writing */
    file = fopen("indexed_file.dat", "wb");

    if(file == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }

    printf("Enter blocks (Enter 0 as block number to stop):\n");

    while(1)
    {
        printf("Block Number: ");
        scanf("%d", &block.blockNumber);

        if(block.blockNumber == 0)
        {
            break;
        }

        printf("Data: ");
        scanf(" %[^\n]", block.data);

        indexBlock[block.blockNumber] = ftell(file);

        fwrite(&block, sizeof(struct Block), 1, file);
    }

    fclose(file);

    /* Open file for reading */
    file = fopen("indexed_file.dat", "rb");

    if(file == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }

    while(1)
    {
        printf("\nEnter block number to read (0 to exit): ");
        scanf("%d", &blockNumber);

        if(blockNumber == 0)
        {
            break;
        }

        if(blockNumber < 0 || blockNumber >= 100)
        {
            printf("Invalid Block Number.\n");
            continue;
        }

        if(indexBlock[blockNumber] == -1)
        {
            printf("Block not found.\n");
        }
        else
        {
            fseek(file, indexBlock[blockNumber], SEEK_SET);

            fread(&block, sizeof(struct Block), 1, file);

            printf("\nBlock Found\n");
            printf("Block Number: %d\n", block.blockNumber);
            printf("Data: %s\n", block.data);
        }
    }

    fclose(file);

    return 0;
}