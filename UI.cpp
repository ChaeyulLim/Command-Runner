#include <iostream>
#include <windows.h>
#include <io.h>
#include <fcntl.h>
#include "function.h"

HWND hWnd = NULL;
HWND hEdit = NULL;
WNDPROC oldEditProc = NULL;
HFONT hFont = NULL;

LRESULT CALLBACK EditSubclassProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_CHAR && wParam == VK_RETURN) {
        wchar_t buffer[256];
        GetWindowTextW(hwnd, buffer, 256);
        if (CommandRun(buffer) == L"success") { // 명령어 실행

           std::wcout << buffer << L" 명령 실행 완료" << '\n'; // log
           MessageBoxW(NULL, L"명령이 실행되었습니다!", L"알림", MB_RIGHT);
           SetWindowTextW(hwnd, L""); // 입력창 비우기

        } else if (CommandRun(buffer) == L"exit"){
            DestroyWindow(hWnd); // exit
        } else {
            std::wcout << buffer << L" 명령이 존재하지 않습니다." << '\n';
            MessageBoxW(NULL, L" 명령이 존재하지 않습니다.\n다시 확인해주세요.", L"알림", MB_RIGHT);
        }
        
        SetFocus(hEdit);
        return 0; // 엔터 키 소리 안나게
    }
    return CallWindowProc(oldEditProc, hwnd, uMsg, wParam, lParam);
}


// 윈도우 프로시저
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    if (uMsg == WM_CREATE) {
        std::wcout << L"윈도우 생성!" << std::endl;

        hFont = CreateFontW(
            20,                    // 높이 (폰트 크기)
            0,                     // 너비 (0이면 자동)
            0, 0,                  // 각도
            FW_NORMAL,             // 두께 (FW_BOLD, FW_NORMAL 등)
            FALSE,                 // 이탤릭
            FALSE,                 // 밑줄
            FALSE,                 // 취소선
            DEFAULT_CHARSET,       // 문자셋
            OUT_DEFAULT_PRECIS,
            CLIP_DEFAULT_PRECIS,
            DEFAULT_QUALITY,
            DEFAULT_PITCH | FF_DONTCARE,
            L"Cascadia Code"           // 폰트 이름
        );

        hEdit = hEdit = CreateWindowExW(
            WS_EX_CLIENTEDGE,
            L"EDIT",
            L"",
            WS_CHILD | WS_VISIBLE | ES_LEFT | ES_AUTOHSCROLL,
            10, 10, 200, 30,
            hwnd, (HMENU)1, NULL, NULL
        );

        // Edit에 폰트 적용
        SendMessageW(hEdit, WM_SETFONT, (WPARAM)hFont, TRUE);

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

    if (Register(hInstance)) {
        hWnd = CreateWindowEx(
            0,
            L"CommandUI",
            L"Command",
            WS_OVERLAPPEDWINDOW,
            1600, 70, 240, 90,
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