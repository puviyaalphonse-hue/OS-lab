#include <stdio.h>
#include <windows.h>

HANDLE mutex, writeBlock;

int data = 0;
int readersCount = 0;

DWORD WINAPI reader(LPVOID arg)
{
    int i;

    for(i = 0; i < 10; i++)
    {
        WaitForSingleObject(mutex, INFINITE);

        readersCount++;

        if(readersCount == 1)
        {
            WaitForSingleObject(writeBlock, INFINITE);
        }

        ReleaseMutex(mutex);

        printf("Reader reads data: %d\n", data);

        WaitForSingleObject(mutex, INFINITE);

        readersCount--;

        if(readersCount == 0)
        {
            ReleaseMutex(writeBlock);
        }

        ReleaseMutex(mutex);

        Sleep(100);
    }

    return 0;
}

DWORD WINAPI writer(LPVOID arg)
{
    int i;

    for(i = 0; i < 10; i++)
    {
        WaitForSingleObject(writeBlock, INFINITE);

        data++;

        printf("Writer writes data: %d\n", data);

        ReleaseMutex(writeBlock);

        Sleep(100);
    }

    return 0;
}

int main()
{
    HANDLE readerThread, writerThread;

    mutex = CreateMutex(NULL, FALSE, NULL);
    writeBlock = CreateMutex(NULL, FALSE, NULL);

    readerThread = CreateThread(NULL, 0, reader, NULL, 0, NULL);
    writerThread = CreateThread(NULL, 0, writer, NULL, 0, NULL);

    WaitForSingleObject(readerThread, INFINITE);
    WaitForSingleObject(writerThread, INFINITE);

    CloseHandle(readerThread);
    CloseHandle(writerThread);

    CloseHandle(mutex);
    CloseHandle(writeBlock);

    return 0;
}