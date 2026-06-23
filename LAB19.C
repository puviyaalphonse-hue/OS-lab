#include <stdio.h>
#include <windows.h>

int counter = 0;
CRITICAL_SECTION cs;

DWORD WINAPI threadFunction(LPVOID arg)
{
    int i;

    for (i = 0; i < 1000000; i++)
    {
        EnterCriticalSection(&cs);

        counter++;

        LeaveCriticalSection(&cs);
    }

    return 0;
}

int main()
{
    HANDLE thread1, thread2;

    InitializeCriticalSection(&cs);

    thread1 = CreateThread(
        NULL,
        0,
        threadFunction,
        NULL,
        0,
        NULL
    );

    thread2 = CreateThread(
        NULL,
        0,
        threadFunction,
        NULL,
        0,
        NULL
    );

    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    CloseHandle(thread1);
    CloseHandle(thread2);

    DeleteCriticalSection(&cs);

    printf("Final counter value: %d\n", counter);

    return 0;
}