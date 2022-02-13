#include <iostream>
#include <Windows.h>
#include <conio.h>
#pragma comment (lib , "winmm.lib") // Used for sound

using namespace std;

// Define key
#define KEY_UP 72       

int main()
{
    int key = 0;

    while(true)
    {
        PlaySound(TEXT("Lofi-zoo-Nightscape.wav"), NULL, SND_FILENAME | SND_ASYNC | SND_LOOP);
        key = _getch();

        if (key == KEY_UP){
            PlaySound(TEXT("button-7.wav"), NULL, SND_FILENAME | SND_ASYNC);
            Sleep(500);
        }
    }
    return 0;
}