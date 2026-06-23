#include <stdio.h>
#include <windows.h>

#define BUFFER_SIZE 5
#define MAX_ITEMS 10

int buffer[BUFFER_SIZE] = {0};
int produced_items = 0;
int consumed_items = 0;

HANDLE empty, full;
CRITICAL_SECTION cs;

DWORD WINAPI producer(LPVOID arg)
{
    while (produced_items < MAX_ITEMS)
    {
        WaitForSingleObject(empty, INFINITE);

        EnterCriticalSection(&cs);

        int i;
        for (i = 0; i < BUFFER_SIZE; i++)
        {
            if (buffer[i] == 0)
            {
                buffer[i] = produced_items + 1;
                printf("Produced: %d\n", buffer[i]);
                produced_items++;
                break;
            }
        }

        LeaveCriticalSection(&cs);

        ReleaseSemaphore(full, 1, NULL);

        Sleep(100);
    }

    return 0;
}

DWORD WINAPI consumer(LPVOID arg)
{
    while (consumed_items < MAX_ITEMS)
    {
        WaitForSingleObject(full, INFINITE);

        EnterCriticalSection(&cs);

        int i;
        for (i = 0; i < BUFFER_SIZE; i++)
        {
            if (buffer[i] != 0)
            {
                printf("Consumed: %d\n", buffer[i]);
                buffer[i] = 0;
                consumed_items++;
                break;
            }
        }

        LeaveCriticalSection(&cs);

        ReleaseSemaphore(empty, 1, NULL);

        Sleep(200);
    }

    return 0;
}

int main()
{
    HANDLE producerThread, consumerThread;

    InitializeCriticalSection(&cs);

    empty = CreateSemaphore(NULL, BUFFER_SIZE, BUFFER_SIZE, NULL);
    full = CreateSemaphore(NULL, 0, BUFFER_SIZE, NULL);

    producerThread = CreateThread(NULL, 0, producer, NULL, 0, NULL);
    consumerThread = CreateThread(NULL, 0, consumer, NULL, 0, NULL);

    WaitForSingleObject(producerThread, INFINITE);
    WaitForSingleObject(consumerThread, INFINITE);

    CloseHandle(producerThread);
    CloseHandle(consumerThread);

    CloseHandle(empty);
    CloseHandle(full);

    DeleteCriticalSection(&cs);

    return 0;
}