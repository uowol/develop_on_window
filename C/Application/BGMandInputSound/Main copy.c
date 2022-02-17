#include <Windows.h>    
#pragma comment (lib, "winmm.lib")  // 음악
#include <mmsystem.h>               // 음악
#include <Digitalv.h>               // 음악
#include <stdio.h>
// #include <iostream>
#include <conio.h>      // 입력버퍼를 사용하지 않는 키 입력 : getch()
#include <process.h>    // _beginthreadex
#include <string.h>

MCI_OPEN_PARMS openBgm;
MCI_PLAY_PARMS playBgm;
MCI_OPEN_PARMS openSounds[9];
MCI_PLAY_PARMS playSounds[9];

HANDLE hStdin;          // 기본 입출력 이벤트를 처리할 핸들
DWORD fdwSaveOldMode;   // 이전 Console mode를 저장, 프로그램 종료 또는 오류 발생시 복구

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);
VOID MouseEventProc(MOUSE_EVENT_RECORD);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

// Define path
#define BGM         "Assets\\airplane.mp3"

// Define key
#define KEY_UP      72
#define KEY_DOWN    80
#define KEY_LEFT    75
#define KEY_RIGHT   77
#define KEY_SPACE   32
#define KEY_ONE     49              
#define KEY_TWO     50              
#define KEY_THREE   51           
#define KEY_FOUR    52              
#define KEY_FIVE    53            
#define KEY_SIX     54            
#define KEY_SEVEN   55            
#define KEY_EIGHT   56
#define KEY_NINE    57

// Define unit
#define UNIT_BPM    150

const int COORDS_NUM[9][2] = {
    {5, 10},
    {14, 10},
    {23, 10},
    {5, 6},
    {14, 6},
    {23, 6},
    {5, 2},
    {14, 2},
    {23, 2}
};
const char* PATH_SOUND[9] = {
    "Assets\\do.mp3",
    "Assets\\re.mp3",
    "Assets\\mi.mp3",
    "Assets\\pa.mp3",
    "Assets\\sol.mp3",
    "Assets\\ra.mp3",
    "Assets\\si.mp3",
    "Assets\\do_high.mp3",
    "Assets\\button-3.mp3"
};

struct Note{
    int time;
    int key;
};

int g_tIndex;
int g_ipt[9] = {0,};
HANDLE hThread[20] = {0,};
HANDLE hMutex;
HANDLE iptMutex;
const struct Note score[25] = {
    {3, 3},
    {1, 2},
    {2, 1},
    {2, 2},
    {2, 3},
    {2, 3},
    {4, 3},
    {2, 2},
    {2, 2},
    {4, 2},
    {2, 3},
    {2, 3},
    {4, 3},
    {3, 3},
    {1, 2},
    {2, 1},
    {2, 2},
    {2, 3},
    {2, 3},
    {4, 3},
    {2, 2},
    {2, 2},
    {2, 3},
    {2, 2},
    {8, 1}
};

void gotoxy(int x, int y){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}

void playingBgm(void) {
    mciSendCommand(0, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_OPEN_TYPE, (DWORD)(LPVOID)&openBgm);
    int dwID = openBgm.wDeviceID;
    mciSendCommand(dwID, MCI_PLAY, MCI_DGV_PLAY_REPEAT, (DWORD)(LPVOID)&openBgm); //음악 반복 재생
}

void soundInit(){
    openBgm.lpstrElementName = TEXT(BGM); //파일 오픈
    openBgm.lpstrDeviceType = TEXT("mpegvideo"); //mp3 형식
    for(int i=0;i<9;i++){
        openSounds[i].lpstrElementName = PATH_SOUND[i]; //파일 오픈
        openSounds[i].lpstrDeviceType = TEXT("mpegvideo"); //mp3 형식
    }
}

// 수정 필요
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

// unsigned int __stdcall inputNote(PVOID pvParam) {
//     int key = *(int *)pvParam;
    
//     WaitForSingleObject(iptMutex, INFINITE);
//     g_ipt[key] = 1;
//     ReleaseMutex(iptMutex);
    
//     Sleep(500);
    
//     WaitForSingleObject(iptMutex, INFINITE);
//     g_ipt[key] = 0;
//     ReleaseMutex(iptMutex);

//     WaitForSingleObject(hMutex, INFINITE);
//     g_tIndex--;
//     ReleaseMutex(hMutex);
// }

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

void display(){
    int i, j, k;
    unsigned char a = 0xa6;
    unsigned char b[12];

    for(i=1; i<12; i++) {
        b[i] = 0xa0 + i;
    }
    //  ─  -  0xa1(161)
    //  │  -  0xa2(162)
    //  ┌  -  0xa3(163)
    //  ┐  -  0xa4(164)
    //  ┘  -  0xa5(165)
    //  └  -  0xa6(166)
    //  ├  -  0xa4(167)
    //  ┬  -  0xa5(168)
    //  ┤  -  0xa6(169)
    //  ┴  -  0xa4(170)
    //  ┼  -  0xa5(171)

    // lint-top
    printf("%c%c", a, b[3]);
    for(i=0; i<8; i++) printf("%c%c", a, b[1]);
    printf("%c%c", a, b[8]);
    for(i=0; i<8; i++) printf("%c%c", a, b[1]);
    printf("%c%c", a, b[8]);
    for(i=0; i<8; i++) printf("%c%c", a, b[1]);
    printf("%c%c\n", a, b[4]);
    
    for(k=0; k<2; k++){
        // line-blank
        for(j=0; j<3; j++){
            printf("%c%c", a, b[2]);
            for(i=0; i<8; i++) printf(" ");
            printf("%c%c", a, b[2]);
            for(i=0; i<8; i++) printf(" ");
            printf("%c%c", a, b[2]);
            for(i=0; i<8; i++) printf(" ");
            printf("%c%c\n", a, b[2]);
        }

        // line-middle
        printf("%c%c", a, b[7]);
        for(i=0; i<8; i++) printf("%c%c", a, b[1]);
        printf("%c%c", a, b[11]);
        for(i=0; i<8; i++) printf("%c%c", a, b[1]);
        printf("%c%c", a, b[11]);
        for(i=0; i<8; i++) printf("%c%c", a, b[1]);
        printf("%c%c\n", a, b[9]);
    }
    
    // line-blank
    for(j=0; j<3; j++){
        printf("%c%c", a, b[2]);
        for(i=0; i<8; i++) printf(" ");
        printf("%c%c", a, b[2]);
        for(i=0; i<8; i++) printf(" ");
        printf("%c%c", a, b[2]);
        for(i=0; i<8; i++) printf(" ");
        printf("%c%c\n", a, b[2]);
    }

    // lint-bottom
    printf("%c%c", a, b[6]);
    for(i=0; i<8; i++) printf("%c%c", a, b[1]);
    printf("%c%c", a, b[10]);
    for(i=0; i<8; i++) printf("%c%c", a, b[1]);
    printf("%c%c", a, b[10]);
    for(i=0; i<8; i++) printf("%c%c", a, b[1]);
    printf("%c%c\n", a, b[5]);

    // char* line_top =    "┌─────┬─────┬─────┐";
    // char* line_blank =  "│     │     │     │";
    // char* line_middle = "├─────┼─────┼─────┤";
    // char* line_bottom = "└─────┴─────┴─────┘";

    // printf("%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n%s\n", 
    //     line_top,
    //     line_blank,line_blank,line_blank,line_middle,
    //     line_blank,line_blank,line_blank,line_middle,
    //     line_blank,line_blank,line_blank,line_middle,
    //     line_bottom);

    // numbering
    for(i=0;i<9;i++){
        gotoxy(COORDS_NUM[i][0], COORDS_NUM[i][1]);
        printf("%d", i+1);
    }
    gotoxy(0, 13);  // reset

    return;
}

int main(){
    // Thread ID를 받아 옵니다.
    DWORD dwThreadID, cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[128];
    g_tIndex = 0;
    hMutex = CreateMutex(NULL, FALSE, NULL);
    iptMutex = CreateMutex(NULL, FALSE, NULL);

    soundInit();

    display();

    playingBgm();
    
    WaitForSingleObject(hMutex, INFINITE);
    hThread[g_tIndex++] = (HANDLE)_beginthreadex(NULL, 0, startNote, score, 0, (unsigned*)&dwThreadID);
    ReleaseMutex(hMutex);

    int counter = 0;

    // Get the standard input handle;
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE) 
        ErrorExit("GetStdHandle");

    // Save the current input mode, to be restored on exit.
    if (! GetConsoleMode(hStdin, &fdwSaveOldMode) )
        ErrorExit("GetConsoleMode");

    // Enable the window and mouse input events.
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT; // 키보드는 default?    // 마우스는 작동하지 않음.
    if (! SetConsoleMode(hStdin, fdwMode) )             // fdwMode에 있는 정보를 핸들에 입력
        ErrorExit("SetConsoleMode");

    // Start input
    while(counter++ <= 1000){
         // Wait for the events.
        if (! ReadConsoleInput(
                hStdin,      // input buffer handle
                irInBuf,     // buffer to read into
                128,         // size of read buffer
                &cNumRead) ) // number of records read
            ErrorExit("ReadConsoleInput");

        // Dispatch the events to the appropriate handler.
        for (i = 0; i < cNumRead; i++){
            switch(irInBuf[i].EventType){
                case KEY_EVENT: // keyboard input
                    KeyEventProc(irInBuf[i].Event.KeyEvent);
                    break;
                case MOUSE_EVENT:               // disregard focus events
                case WINDOW_BUFFER_SIZE_EVENT:  // disregard menu events
                case FOCUS_EVENT:               // disregard focus events
                case MENU_EVENT:                // disregard menu events
                    break;
                default:
                    ErrorExit("Unknown event type");
                    break;
            }
        }
    }

    WaitForMultipleObjects(10, hThread, TRUE, 1000000);
    for(int i=0;i<10;i++)
        if (hThread[i] != NULL) CloseHandle(hThread[i]);

    // Restore input mode on exit.
    SetConsoleMode(hStdin, fdwSaveOldMode);

    return 0;
}

VOID ErrorExit (LPSTR lpszMessage){
    fprintf(stderr, "%s\n", lpszMessage);   // !

    // Restore input mode on exit.
    SetConsoleMode(hStdin, fdwSaveOldMode);

    Sleep(10000);

    ExitProcess(0);     // !
}

VOID KeyEventProc(KEY_EVENT_RECORD ker){
    DWORD dwThreadID;
    // printf("Key event: ");
    if(ker.bKeyDown){
        // printf("key pressed : %d\n", ker.wVirtualKeyCode);
        int num = ker.wVirtualKeyCode - 97;
        if(num < 0 || num >= 9) return;

        WaitForSingleObject(iptMutex, INFINITE);
        if(g_ipt[num]) return;
        g_ipt[num] = 1;
        ReleaseMutex(iptMutex);

        // effect
        gotoxy(COORDS_NUM[num][0], COORDS_NUM[num][1]+1);
        printf("-");

        int dwArg = num;
        if(g_tIndex >= 20) return;
        WaitForSingleObject(hMutex, INFINITE);
        hThread[g_tIndex++] = (HANDLE)_beginthreadex(NULL, 0, playingSound, (PVOID)&dwArg, 0, (unsigned*)&dwThreadID);
        // hThread[g_tIndex++] = (HANDLE)_beginthreadex(NULL, 0, effectNote, (PVOID)&dwArg, 0, (unsigned*)&dwThreadID);
        ReleaseMutex(hMutex);

        // Sleep(10);
    } else {
        // printf("key released\n");
        int num = ker.wVirtualKeyCode - 97;
        if(num < 0 || num >= 9) return;

        // effect 소멸
        gotoxy(COORDS_NUM[num][0], COORDS_NUM[num][1]+1);
        printf(" ");

        WaitForSingleObject(iptMutex, INFINITE);
        g_ipt[num] = 0;
        ReleaseMutex(iptMutex);
    }
}