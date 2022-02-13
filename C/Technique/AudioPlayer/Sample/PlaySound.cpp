#include <iostream>
#include <string>
#include <windows.h>
#include <mmsystem.h>
// #pragma comment (lib, "winmm.lib")
int main(){
    std::string file_name = "C:\\Users\\uowol\\Documents\\GitHub\\solo-study\\c++\\WindowTerminalGame\\Technique\\AudioPlayer\\Sample\\button-3.wav";
    bool played = PlaySound(file_name.c_str(), NULL, SND_FILENAME);
    getchar();
    return 0;
}
