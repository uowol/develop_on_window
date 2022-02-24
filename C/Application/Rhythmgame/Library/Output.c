#include "Output.h"

int stage;

void setStage(int _stage){
    stage = _stage;
}

void gotoxy(int x, int y){
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD pos;
    pos.X = x;
    pos.Y = y;
    SetConsoleCursorPosition(hConsole, pos);
}

void setWindowSize(int width, int height){
    char exec[128];
    sprintf(exec, "mode con cols=%d lines=%d", width, height);
    system(exec);
}

void clear(){
    system("cls");
}

void display(char* buffer[]){
    clear();
    int i, j;
    if(stage == 1){         // Main
        for(i=0; i<60; i++){
            gotoxy(49, i);
            if(i==0 || i==47 || i==51 || i==55 || i==59)
                drawLayout(1, 100);
            else
                drawLayout(2, 100);
        }
        gotoxy(51, 49);
        printf(">게임시작");
        gotoxy(52, 53);
        printf("설정");
        gotoxy(52, 57);
        printf("나가기");
    }else if(stage == 2){   // Music List
        // list
        for(i=0; i<60; i++){
            gotoxy(0, i);
            if(i==0 || i==59 || i%4==0)
                drawLayout(1, 140);
            else
                drawLayout(2, 140);
        }
        for(i=0; i<NUM_MUSIC; i++){
            if(i == 0){
                gotoxy(2, 2 + i*4);
                printf(">");
            } else gotoxy(3, 2 + i*4);
            printf("%s", buffer[i]);
        }
        // music info
        gotoxy(143, 2);
        printf("곡 제목: %s", buffer[0]);
        gotoxy(143, 6);
        printf("랭크: %s", "A");
        gotoxy(143, 10);
        printf("점수: %s", "102345");
    }else if(stage == 3){   // inGame
        // numpad
        int w = 60;
        int h = 14;
        for(i=0; i<3; i++){
            gotoxy(6, 1+(3 + h)*i);
            drawLayout(1, w);
            gotoxy(70, 1+(3 + h)*i);
            drawLayout(1, w);
            gotoxy(134, 1+(3 + h)*i);
            drawLayout(1, w);
            for(j=0;j<h;j++){
                gotoxy(6, 1+(3 + h)*i+1+j);
                drawLayout(2, w);
                gotoxy(70, 1+(3 + h)*i+1+j);
                drawLayout(2, w);
                gotoxy(134, 1+(3 + h)*i+1+j);
                drawLayout(2, w);
            }
            gotoxy(6, 1+(3 + h)*i+1+j);
            drawLayout(1, w);
            gotoxy(70, 1+(3 + h)*i+1+j);
            drawLayout(1, w);
            gotoxy(134, 1+(3 + h)*i+1+j);
            drawLayout(1, w);
        }
    }
}

void drawLayout(int type, int size){
    char wall = '#';
    if(type == 1){          // TOP
        for(int i=0; i<size; i++){
            printf("%c", wall);
        }
    }else if(type == 2){    // MIDDLE
        printf("%c", wall);
        for(int i=0; i<size-2; i++){
            printf(" ");
        }
        printf("%c", wall);        
    }
}