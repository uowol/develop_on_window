#include <Windows.h>    
#pragma comment (lib, "winmm.lib")  // 음악
#include <mmsystem.h>               // 음악
#include <Digitalv.h>               // 음악
#include <stdio.h>
#include <conio.h>      // 입력버퍼를 사용하지 않는 키 입력 : getch()
#include <process.h>    // _beginthreadex
#include <string.h>

// Define path
#define BGM         "Assets\\airplane.mp3"

// Define key
#define KEY_LEFT    37
#define KEY_UP      38
#define KEY_RIGHT   39
#define KEY_DOWN    40
#define KEY_SPACE   32
#define KEY_ENTER   13
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

// Define Music
#define NUM_MUSIC   5