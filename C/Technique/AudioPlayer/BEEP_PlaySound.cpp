#include <iostream>
#include <Windows.h>
#include <process.h>
#include <mmsystem.h>
#include <string>
#pragma comment (lib, "strmiids.lib")
#pragma comment (lib, "winmm.lib")

using namespace std;

unsigned int __stdcall BGMFunc(PVOID pvParam)
{
    Sleep(3000);

    DWORD dwResult = 0;
    int repeatTime = 0;

    string file_name = *(string *)pvParam;
	
    while(repeatTime++ < 10){
        cout << "2: I'm working!!" << endl;
        PlaySound(file_name.c_str(), NULL, SND_FILENAME);
        Sleep(500);
    }
    return (dwResult);
}

unsigned int __stdcall BeepFunc(PVOID pvParam)
{
	DWORD dwResult = 0;
    int repeatTime = 0;

    string file_name = *(string *)pvParam;

    while(repeatTime++ < 10){
        cout << "1: I'm working!!" << endl;
        PlaySound(file_name.c_str(), NULL, SND_FILENAME);
        Sleep(500);
    }
	return (dwResult);
}

int main(void)
{
    string path_bgm = "C:\\Users\\uowol\\Documents\\GitHub\\solo-study\\c++\\WindowTerminalGame\\Technique\\AudioPlayer\\Sample\\button-7.wav";
    string path_beep = "C:\\Users\\uowol\\Documents\\GitHub\\solo-study\\c++\\WindowTerminalGame\\Technique\\AudioPlayer\\Sample\\button-3.wav";

    // Thread에 전달할 매개 변수입니다.
    DWORD dwArg = 10;
    // Thread ID를 받아 옵니다.
    DWORD dwThreadID;

    HANDLE hThread[2] = {0,};

    // hThread[0] = CreateThread(NULL, 0, ThreadFunc, (PVOID)&dwArg, 0, &dwThreadID);
    //CreateThread => _beginthreadex로 변환될 수 있습니다. 
    hThread[0] = (HANDLE)_beginthreadex(nullptr, 0, BeepFunc, (PVOID)&path_beep, 0, (unsigned*)&dwThreadID);
    hThread[1] = (HANDLE)_beginthreadex(nullptr, 0, BGMFunc, (PVOID)&path_bgm, 0, (unsigned*)&dwThreadID);

    // 스레드가 끝날때까지 대기 합니다.
    WaitForMultipleObjects(2, hThread, TRUE, INFINITE);

    if (hThread[0] != NULL) CloseHandle(hThread[0]);
    if (hThread[1] != NULL) CloseHandle(hThread[1]);

    CoUninitialize();
    return 0;
}