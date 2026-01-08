#pragma once
#include <iostream>
#include <vector>
#include <string>

std::wstring CommandRun(std::wstring command)
{
    std::wcout << "Command : " << command << '\n';

    if (command == L"백준 과제" || command == L"baekjoon") {
        ShellExecuteW(NULL, L"open", L"https://github.com/ChaeyulLim", NULL, NULL, SW_SHOWNORMAL);
        ShellExecuteW(NULL, L"open", L"https://www.acmicpc.net/step", NULL, NULL, SW_SHOWNORMAL);
        ShellExecuteW(NULL, L"open", L"C:\\Users\\chaey\\AppData\\Local\\Programs\\Microsoft VS Code\\Code.exe", L"C:/Users/chaey/Project/baekjoon", NULL, SW_SHOWNORMAL);
    } else if (command == L"git" || command == L"github") {
        ShellExecuteW(NULL, L"open", L"https://github.com/ChaeyulLim", NULL, NULL, SW_SHOWNORMAL);
    } else if (command == L"vscode" || command == L"vsc") {
        ShellExecuteW(NULL, L"open", L"C:\\Users\\chaey\\AppData\\Local\\Programs\\Microsoft VS Code\\Code.exe", NULL, NULL, SW_SHOWNORMAL);
    } else if (command == L"exit" || command == L"Exit" || command == L"EXIT") {
        return L"exit";
    }
    
    
    else {
        return L"failed";
    }


    return L"success";
}