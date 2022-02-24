#include "../Library/Output.c"
#include "../Library/Input.c"

int pos = 0;

// 임시방편
char* musiclist[] = {"비행기", "산토끼", "NULL", "NULL", "NULL"};
char* musicinfolist[][3] = {
    {"비행기", "A", "102345"},
    {"산토끼", "-", "-"},
    {"NULL", "-", "-"},
    {"NULL", "-", "-"},
    {"NULL", "-", "-"}
};

int main(){
    // Thread ID를 받아 옵니다.
    DWORD dwThreadID, cNumRead, fdwMode;

    // display main window
    setStage(1);
    setWindowSize(200, 60);
    display(NULL);

    // start input
    initEventListener();
    startInput();

    getchar();
    return 0;
}

VOID KeyEventProc(KEY_EVENT_RECORD ker)
{
    DWORD dwThreadID;
    int key = ker.wVirtualKeyCode;

    if(ker.bKeyDown){
        switch(stage){
            case 1: // Main window
                if(key<37 || key>40) 
                    if(key!=13) return;
                gotoxy(51, 49+4*pos);
                printf(" ");
                switch(key){
                    case KEY_UP:
                    case KEY_LEFT:
                        if(--pos<0) pos = 0;
                        gotoxy(51, 49+4*pos);
                        printf(">");
                        break;
                    case KEY_DOWN:
                    case KEY_RIGHT:
                        if(++pos>2) pos = 2;
                        gotoxy(51, 49+4*pos);
                        printf(">");
                        break;
                    case KEY_ENTER:
                        if(pos == 0){
                            setStage(2);
                            display(musiclist);
                        }else if(pos == 1){
                            
                        }else if(pos == 2){
                            exit(0);
                        }
                        return;
                }
                break;
            case 2: 
                if(key<37 || key>40) 
                    if(key!=13) return;
                gotoxy(2, 2+4*pos);
                printf(" ");
                switch(key){
                    case KEY_UP:
                    case KEY_LEFT:
                        if(--pos<0) pos = 0;
                        gotoxy(2, 2+4*pos);
                        printf(">");
                        break;
                    case KEY_DOWN:
                    case KEY_RIGHT:
                        if(++pos>=NUM_MUSIC) pos = NUM_MUSIC-1;
                        gotoxy(2, 2+4*pos);
                        printf(">");
                        break;
                    case KEY_ENTER:
                        // 원래는 여기에서 곡 속도, 난이도 설정
                        
                        // 지금은 스킵
                        setStage(3);
                        display(NULL);
                        return;
                }
                gotoxy(152, 2);
                printf("%-10s", musicinfolist[pos][0]);
                gotoxy(149, 6);
                printf("%-10s", musicinfolist[pos][1]);
                gotoxy(149, 10);
                printf("%-10s", musicinfolist[pos][2]);
                break;
            case 3:
            default:
                break;
        }
        // Sleep(10);
    } else {
    }
}
