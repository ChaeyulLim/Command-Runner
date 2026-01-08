#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "function.h"

HWND hEdit = NULL;
WNDPROC oldEditProc;

LRESULT CALLBACK EditSubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_CHAR && wParam == VK_RETURN) {
        wchar_t buffer[256];
        GetWindowTextW(hwnd, buffer, 256);
        CommandRun(buffer); // 명령어 실행
        
        SetWindowTextW(hwnd, L""); // 입력창 비우기
        return 0; // 엔터 키 소리 안나게
    }
    return CallWindowProc(oldEditProc, hwnd, uMsg, wParam, lParam);
}


// 윈도우 프로시저
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_CREATE) {
        std::wcout << L"윈도우 생성!" << std::endl;
        hEdit = hEdit = CreateWindowExW(
            WS_EX_CLIENTEDGE,
            L"EDIT",
            L"",
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,
            10, 10, 760, 30,
            hwnd, (HMENU)1, NULL, NULL
        );
        
        oldEditProc = (WNDPROC)SetWindowLongPtrW(hEdit, GWLP_WNDPROC, (LONG_PTR)EditSubclassProc);
        
        SetFocus(hEdit); // 포커스 설정
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