#include <iostream>
#include <Windows.h>
#include <process.h>
#include <tchar.h>

using namespace std;

string g_str = "";
HANDLE hMutex;

unsigned int __stdcall PingFunc(PVOID pvParam)
{
	DWORD dwResult = 0;

    while(true){
        WaitForSingleObject(hMutex, INFINITE);
        if(g_str != "ping"){
            g_str = "ping";
            _tprintf(_T("ping!"));
        }
        ReleaseMutex(hMutex);
        Sleep(100);
    }

	return (dwResult);
}

unsigned int __stdcall PongFunc(PVOID pvParam)
{
	DWORD dwResult = 0;

    while(true){
        WaitForSingleObject(hMutex, INFINITE);
        if(g_str != "pong"){
            g_str = "pong";
            _tprintf(_T("ping!"));
        }
        ReleaseMutex(hMutex);
        Sleep(100);
    }

	return (dwResult);
}

int main(){
    hMutex = CreateMutex(NULL, FALSE, NULL);

    // Thread에 전달할 매개 변수입니다.
    DWORD dwArg = 10;
    // Thread ID를 받아 옵니다.
    DWORD dwThreadID;

    HANDLE hThread[2] = {0,};

    // hThread[0] = CreateThread(NULL, 0, ThreadFunc, (PVOID)&dwArg, 0, &dwThreadID);
    //CreateThread => _beginthreadex로 변환될 수 있습니다. 
    hThread[0] = (HANDLE)_beginthreadex(nullptr, 0, PingFunc, (PVOID)&dwArg, 0, (unsigned*)&dwThreadID);
    hThread[1] = (HANDLE)_beginthreadex(nullptr, 0, PongFunc, (PVOID)&dwArg, 0, (unsigned*)&dwThreadID);

    // 스레드가 끝날때까지 대기 합니다.
    WaitForMultipleObjects(2, hThread, TRUE, 5000);

    if (hThread[0] != NULL) CloseHandle(hThread[0]);
    if (hThread[1] != NULL) CloseHandle(hThread[1]);

    return 0;
}