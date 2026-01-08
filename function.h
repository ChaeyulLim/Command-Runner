#pragma once
#include <iostream>
#include <vector>
#include <string>

bool CommandRun(std::wstring command)
{
    std::wcout << "Command : " << command << '\n';

    if (command == L"백준 과제") {
        ShellExecuteW(NULL, L"open", L"https://github.com/ChaeyulLim", NULL, NULL, SW_SHOWNORMAL);
        ShellExecuteW(NULL, L"open", L"https://www.acmicpc.net/step", NULL, NULL, SW_SHOWNORMAL);
        ShellExecuteW(NULL, L"open", L"code", L"C:/Users/chaey/Project/baekjoon", NULL, SW_SHOWNORMAL);
    }
    
    
    
    else {
        return false;
    }
    return true;
}