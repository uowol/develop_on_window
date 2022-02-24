#include <./Callback.h>

unsigned int __stdcall effectNote(PVOID pvParam) {
    int key = *(int*) pvParam;

    // create effect
    gotoxy(COORDS_NUM[key][0]-3, COORDS_NUM[key][1]);
    printf("-");
    gotoxy(COORDS_NUM[key][0]+3, COORDS_NUM[key][1]);
    printf("-");

    Sleep(1000 / 4);

    // delete effect
    gotoxy(COORDS_NUM[key][0]-3, COORDS_NUM[key][1]);
    printf(" ");
    gotoxy(COORDS_NUM[key][0]+3, COORDS_NUM[key][1]);
    printf(" ");

    // create effect
    gotoxy(COORDS_NUM[key][0]-2, COORDS_NUM[key][1]);
    printf("-");
    gotoxy(COORDS_NUM[key][0]+2, COORDS_NUM[key][1]);
    printf("-");

    Sleep(1000 / 4);

    // delete effect
    gotoxy(COORDS_NUM[key][0]-2, COORDS_NUM[key][1]);
    printf(" ");
    gotoxy(COORDS_NUM[key][0]+2, COORDS_NUM[key][1]);
    printf(" ");

    // create effect
    gotoxy(COORDS_NUM[key][0]-1, COORDS_NUM[key][1]);
    printf("-");
    gotoxy(COORDS_NUM[key][0]+1, COORDS_NUM[key][1]);
    printf("-");
    
    Sleep(1000 / 4);

    // delete effect
    gotoxy(COORDS_NUM[key][0]-1, COORDS_NUM[key][1]);
    printf(" ");
    gotoxy(COORDS_NUM[key][0]+1, COORDS_NUM[key][1]);
    printf(" ");

    // reset cursor
    gotoxy(0, 13);
    
    WaitForSingleObject(hMutex, INFINITE);
    g_tIndex--;
    ReleaseMutex(hMutex);
}

unsigned int __stdcall playingSound(PVOID pvParam) {
    int key = *(int*) pvParam;
    int dwID;

    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openSounds[key]);
    dwID = openSounds[key].wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_NOTIFY, (DWORD)(LPVOID)&openSounds[key]); //음악을 한 번 재생

    Sleep(1000); //효과음이 재생될 때까지 정지했다가
    mciSendCommand(dwID, MCI_SEEK, MCI_SEEK_TO_START, (DWORD)(LPVOID)NULL); //음원 재생 위치를 처음으로 초기화    

    // thread 소멸
    WaitForSingleObject(hMutex, INFINITE);
    g_tIndex--;
    ReleaseMutex(hMutex);
}

unsigned int __stdcall startNote(struct Note score[]) {
    Sleep(5000);

    printf("3...");
    Sleep(1000);
    printf("2...");
    Sleep(1000);
    printf("1...");
    Sleep(1000);
    printf("start!");
    Sleep(500);

    for(int i=0; i<25; i++){
        gotoxy(0, 14);
        printf("=====%d=====\n", score[i].key);
        if(g_ipt[score[i].key-1]){
            printf("correct!");
        }else{
            printf("miss!   ");
        }
        Sleep(score[i].time * UNIT_BPM);
    }

}
