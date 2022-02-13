#include <windows.h>
#include <stdio.h>

HANDLE hStdin;          // 기본 입출력 이벤트를 처리할 핸들
DWORD fdwSaveOldMode;   // 이전 Console mode를 저장, 프로그램 종료 또는 오류 발생시 복구

VOID ErrorExit(LPSTR);
VOID KeyEventProc(KEY_EVENT_RECORD);
VOID MouseEventProc(MOUSE_EVENT_RECORD);
VOID ResizeEventProc(WINDOW_BUFFER_SIZE_RECORD);

void gotoxy(int x, int y){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}

int main(){
    DWORD cNumRead, fdwMode, i;
    INPUT_RECORD irInBuf[128];
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

    // Print default values
    printf("\n ");
    for(i=0; i<10; i++){
        printf(" 0");
    }

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
    // printf("Key event: ");

    if(ker.bKeyDown){
        // printf("key pressed : %d\n", ker.wVirtualKeyCode);
        int num = ker.wVirtualKeyCode - 96;
        if(num < 0 || num > 9) return;
        gotoxy(2*num + 2, 1);
        printf("1");
    } else {
        // printf("key released\n");
        int num = ker.wVirtualKeyCode - 96;
        if(num < 0 || num > 9) return;
        gotoxy(2*num + 2, 1);
        printf("0");
    }
}