#include "input.h"

HANDLE hStdin;          // 기본 입출력 이벤트를 처리할 핸들
DWORD fdwSaveOldMode;   // 이전 Console mode를 저장, 프로그램 종료 또는 오류 발생시 복구

void initEventListener(){
    DWORD fdwMode;
    
    // Get the standard input handle.
    hStdin = GetStdHandle(STD_INPUT_HANDLE);
    if (hStdin == INVALID_HANDLE_VALUE)
        ErrorExit("GetStdHandle");

    // Save the current input mode, to be restored on exit.
    if (! GetConsoleMode(hStdin, &fdwSaveOldMode) )
        ErrorExit("GetConsoleMode");

    // Enable the window and mouse input events.
    fdwMode = ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT; // 키보드는 default?    // 마우스는 작동하지 않음.
    if (! SetConsoleMode(hStdin, fdwMode) ) // fdwMode에 있는 정보를 핸들에 입력
        ErrorExit("SetConsoleMode");
}

void startInput(){
    DWORD cNumRead;
    INPUT_RECORD irInBuf[128];
    int counter = 0;
    while(counter++ < 10000){
        // Wait for the events.
        if (! ReadConsoleInput(
                hStdin,      // input buffer handle
                irInBuf,     // buffer to read into
                128,         // size of read buffer
                &cNumRead) ) // number of records read
            ErrorExit("ReadConsoleInput");

        // Dispatch the events to the appropriate handler.
        for (int i = 0; i < cNumRead; i++){
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
}

VOID ErrorExit (LPSTR lpszMessage)
{
    fprintf(stderr, "%s\n", lpszMessage);   // !

    // Restore input mode on exit.

    SetConsoleMode(hStdin, fdwSaveOldMode);

    ExitProcess(0);     // !
}