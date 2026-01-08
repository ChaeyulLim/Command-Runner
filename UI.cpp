#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>

// 윈도우 프로시저
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_CREATE) {
        std::wcout << L"윈도우 생성!" << std::endl;
    } 
    if (uMsg == WM_DESTROY) {
        std::wcout << L"프로그램 종료" << std::endl;
        PostQuitMessage(0);
    }
    return DefWindowProc(hwnd, uMsg, wParam, lParam);
}

bool Register(HINSTANCE hInstance)
{
    WNDCLASSEXW wc = {};
    wc.lpfnWndProc = WindowProc;
    wc.cbSize = sizeof(WNDCLASSEXW);
    wc.hInstance = hInstance;
    wc.lpszClassName = L"CommandUI";
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);

    return RegisterClassExW(&wc);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    _setmode(_fileno(stdout), _O_U16TEXT);
    HWND hWnd = NULL;

    if (Register(hInstance)) {
        hWnd = CreateWindowEx(
            0,
            L"CommandUI",
            L"Command Runner",
            WS_OVERLAPPEDWINDOW,
            CW_USEDEFAULT, CW_USEDEFAULT, 800, 600,
            NULL, NULL, hInstance, NULL
        );
    }
    if (! hWnd) { return 0; } // 생성 불가.
    
    ShowWindow(hWnd, nCmdShow);

    // 메시지 루프
    MSG msg = {};
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}