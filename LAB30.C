#include <stdio.h>
#include <windows.h>

DWORD WINAPI func(LPVOID arg)
{
    printf("Inside the thread\n");
    return 0;
}

void fun()
{
    HANDLE hThread;
    DWORD threadId;

    hThread = CreateThread(
        NULL,
        0,
        func,
        NULL,
        0,
        &threadId
    );

    if (hThread == NULL)
    {
        printf("Thread creation failed.\n");
        return;
    }

    printf("This line may be printed before thread terminates\n");

    WaitForSingleObject(hThread, INFINITE);

    printf("This line will be printed after thread ends\n");

    CloseHandle(hThread);
}

int main()
{
    fun();
    return 0;
}