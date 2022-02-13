#include <iostream>
#include <dshow.h>
#include <Windows.h>
#include <process.h>
#pragma comment (lib, "strmiids.lib")

using namespace std;

HRESULT hr;

// unsigned int __stdcall BGMFunc(PVOID pvParam)
// {
//     IMediaControl *pControl = NULL;
//     IMediaEvent   *pEvent = NULL;

//     hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
//     hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);

// 	DWORD dwResult = 0;

//     // Build the graph. IMPORTANT: Change this string to a file on your system.
//     hr = pGraph->RenderFile(L"C:\\Users\\uowol\\Documents\\GitHub\\solo-study\\c++\\WindowTerminalGame\\Technique\\AudioPlayer\\Sample\\Lofi zoo - Nightscape.mp3", NULL);
//     if (SUCCEEDED(hr))
//     {
//         // Run the graph.
//         hr = pControl->Run();
//         if (SUCCEEDED(hr))
//         {
//             // Wait for completion.
//             long evCode;
//             pEvent->WaitForCompletion(INFINITE, &evCode);

//             // Note: Do not use INFINITE in a real application, because it
//             // can block indefinitely.
//         }
//     }
//     pControl->Release();
//     pEvent->Release();
// 	return (dwResult);
// }

unsigned int __stdcall BeepFunc(PVOID pvParam)
{
    IGraphBuilder *pGraph = NULL;
    IMediaControl *pControl = NULL;
    IMediaEvent   *pEvent = NULL;

	DWORD dwResult = 0;
    int repeatTime = 0;

    // Build the graph. IMPORTANT: Change this string to a file on your system.
    while(1){
        cout << "?";
        // Create the filter graph manager and query for interfaces.
        hr = CoCreateInstance(CLSID_FilterGraph, NULL, CLSCTX_INPROC_SERVER, 
                            IID_IGraphBuilder, (void **)&pGraph);
        if (FAILED(hr))
        {
            printf("ERROR - Could not create the Filter Graph Manager.");
            return 0;
        }
        hr = pGraph->QueryInterface(IID_IMediaControl, (void **)&pControl);
        hr = pGraph->QueryInterface(IID_IMediaEvent, (void **)&pEvent);
        
        hr = pGraph->RenderFile(L"C:\\Users\\uowol\\Documents\\GitHub\\solo-study\\c++\\WindowTerminalGame\\Technique\\AudioPlayer\\Sample\\button-3.mp3", NULL);
        if (SUCCEEDED(hr))
        {
            // Run the graph.
            hr = pControl->Run();
            if (SUCCEEDED(hr))
            {
                // Wait for completion.
                long evCode;
                pEvent->WaitForCompletion(1000, &evCode);

                // Note: Do not use INFINITE in a real application, because it
                // can block indefinitely.
            }
        }
        pControl->Release();
        pEvent->Release();
        pGraph->Release();
        Sleep(1000);
    }
	return (dwResult);
}

int main(void)
{
    // Initialize the COM library.
    hr = CoInitialize(NULL);
    if (FAILED(hr))
    {
        printf("ERROR - Could not initialize COM library");
        return 0;
    }
    
    // Thread에 전달할 매개 변수입니다.
    DWORD dwArg = 10;
    // Thread ID를 받아 옵니다.
    DWORD dwThreadID;

    HANDLE hThread[2] = {0,};

    // hThread[0] = CreateThread(NULL, 0, ThreadFunc, (PVOID)&dwArg, 0, &dwThreadID);
    //CreateThread => _beginthreadex로 변환될 수 있습니다. 
    hThread[0] = (HANDLE)_beginthreadex(nullptr, 0, BeepFunc, (PVOID)&dwArg, 0, (unsigned*)&dwThreadID);
    // hThread[1] = (HANDLE)_beginthreadex(nullptr, 0, BeepFunc, (PVOID)&dwArg, 0, (unsigned*)&dwThreadID);

    // 스레드가 끝날때까지 대기 합니다.
    WaitForMultipleObjects(1, hThread, TRUE, 10000);

    if (hThread[0] != NULL) CloseHandle(hThread[0]);
    // if (hThread[1] != NULL) CloseHandle(hThread[1]);

    CoUninitialize();
    return 0;
}