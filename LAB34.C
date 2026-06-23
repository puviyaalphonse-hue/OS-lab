#include <stdio.h>
#include <stdlib.h>

struct Record
{
    int recordNumber;
    char data[256];
};

int main()
{
    FILE *file;
    struct Record record;
    int recordNumber;

    /* Open file for writing */
    file = fopen("sequential_file.dat", "wb");

    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }

    printf("Enter records (Enter 0 as record number to stop):\n");

    while (1)
    {
        printf("Record Number: ");
        scanf("%d", &record.recordNumber);

        if (record.recordNumber == 0)
        {
            break;
        }

        printf("Data: ");
        scanf(" %[^\n]", record.data);

        fwrite(&record, sizeof(struct Record), 1, file);
    }

    fclose(file);

    /* Open file for reading */
    file = fopen("sequential_file.dat", "rb");

    if (file == NULL)
    {
        printf("Error opening the file.\n");
        return 1;
    }

    while (1)
    {
        printf("\nEnter the record number to read (0 to exit): ");
        scanf("%d", &recordNumber);

        if (recordNumber == 0)
        {
            break;
        }

        rewind(file);

        while (fread(&record, sizeof(struct Record), 1, file) == 1)
        {
            if (record.recordNumber == recordNumber)
            {
                printf("\nRecord Found\n");
                printf("Record Number: %d\n", record.recordNumber);
                printf("Data: %s\n", record.data);
                break;
            }
        }
    }

    fclose(file);

    return 0;
}