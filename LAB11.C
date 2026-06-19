#include <stdio.h>
#include <windows.h>

DWORD WINAPI threadFunction(LPVOID arg)
{
    char *message = (char *)arg;
    printf("%s\n", message);
    return 0;
}

int main()
{
    HANDLE thread1, thread2;

    char *message1 = "Hello from Thread 1!";
    char *message2 = "Hello from Thread 2!";

    thread1 = CreateThread(NULL, 0, threadFunction, message1, 0, NULL);
    thread2 = CreateThread(NULL, 0, threadFunction, message2, 0, NULL);

    WaitForSingleObject(thread1, INFINITE);
    WaitForSingleObject(thread2, INFINITE);

    CloseHandle(thread1);
    CloseHandle(thread2);

    return 0;
}