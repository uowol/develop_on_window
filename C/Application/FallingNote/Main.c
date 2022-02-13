#include <stdio.h>
#include <Windows.h>
#include <process.h>

#define FALLING_TIME    1000
#define FALLING_HEIGHT  20

void gotoxy(int x, int y){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}

unsigned int __stdcall dropNote(int notes[]){
    int i, j;
    while(1){
        for(i=0; i<FALLING_HEIGHT; i++){
            for(j=0; j<9; j++){
                if(!notes[j]) continue;
                gotoxy(2+4*j, i);
                printf("*");
            }
            Sleep(FALLING_TIME/FALLING_HEIGHT);
            for(j=0; j<9; j++){
                if(!notes[j]) continue;
                gotoxy(2+4*j, i);
                printf(" ");
            }
        }
    }
}

void drawBackground(){
    int i;
    
    gotoxy(0,0);
    for(i=0; i<FALLING_HEIGHT; i++){
        printf("|   |   |   |   |   |   |   |   |   |\n");
    }
}

int main(){
    drawBackground();
    // Thread ID를 받아 옵니다.
    DWORD dwThreadID;
    int dwArg[] = {0, 0, 1, 0, 0, 0, 1, 1, 1};
    HANDLE hThread[20] = {0,};
    hThread[0] = (HANDLE)_beginthreadex(NULL, 0, dropNote, dwArg, 0, (unsigned*)&dwThreadID);
    getchar();
    return 0;
}