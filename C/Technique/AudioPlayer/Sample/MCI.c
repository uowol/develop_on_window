#include <Windows.h>    //키보드 입력
#pragma comment (lib, "winmm.lib") //음악
#include <mmsystem.h>   // 음악
#include <Digitalv.h>   // 음악
#include <stdio.h>
#include <conio.h>      // 입력버퍼를 사용하지 않는 키 입력 : getch()
#include <process.h>    // _beginthreadex

MCI_OPEN_PARMS openBgm;
MCI_PLAY_PARMS playBgm;
MCI_OPEN_PARMS openShuffleSound;
MCI_PLAY_PARMS playShuffleSound;

// Define path
#define BGM     "Lofi zoo - Nightscape.mp3" // BGM 경로 지정
#define SHUFFLE "button-3.mp3"              // 효과음 경로 지정
// Define key
#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_LEFT    75
#define KEY_RIGHT   77
#define KEY_SPACE   32

int dwID;
int g_tIndex;
HANDLE hMutex;

void playingBgm(void) {
    openBgm.lpstrElementName = TEXT(BGM); //파일 오픈
    openBgm.lpstrDeviceType = TEXT("mpegvideo"); //mp3 형식
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
    dwID = openBgm.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm); //음악 반복 재생
}

unsigned int __stdcall playingShuffleSound(PVOID pvParam) {
    openShuffleSound.lpstrElementName = TEXT(SHUFFLE); //파일 오픈
    openShuffleSound.lpstrDeviceType = TEXT("mpegvideo"); //mp3 형식
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openShuffleSound);
    dwID = openShuffleSound.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openShuffleSound); //음악을 한 번 재생
    Sleep(1000); //효과음이 재생될 때까지 정지했다가
    mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL); //음원 재생 위치를 처음으로 초기화
    
    WaitForSingleObject(hMutex, INFINITE);
    g_tIndex--;
    ReleaseMutex(hMutex);
}

int main(){
     // Thread에 전달할 매개 변수입니다.
    DWORD dwArg = 10;
    // Thread ID를 받아 옵니다.
    DWORD dwThreadID;

    HANDLE hThread[10] = {0,};
    g_tIndex = 0;

    hMutex = CreateMutex(NULL, FALSE, NULL);

    playingBgm();

    int key = 0;
    while(1){
        key = _getch();
        printf("%d", key);
        if (key == KEY_UP){
            if(g_tIndex >= 10) continue;
            WaitForSingleObject(hMutex, INFINITE);
            hThread[g_tIndex++] = (HANDLE)_beginthreadex(NULL, 0, playingShuffleSound, (PVOID)&dwArg, 0, (unsigned*)&dwThreadID);
            printf("index: %d", g_tIndex);
            ReleaseMutex(hMutex);
        }
        if (key == KEY_DOWN){
            break;
        }
        Sleep(10);
    }
    WaitForMultipleObjects(10, hThread, TRUE, 1000000);
    for(int i=0;i<10;i++)
        if (hThread[i] != NULL) CloseHandle(hThread[i]);
}