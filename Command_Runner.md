# 프로젝트 이름 : Command Runner
## 프로젝트 설명
```base
해당 프로젝트는 단순히 명령어 입력 -> 저장된 명령 시행
하는 프로그램이다. v1 으로 나중에 버전관리를 통해 더 좋은 프로그램으로 발전할 예정이다.

```
프로그램 컴파일 링크 목록 및 컴파일 방법
```
g++ UI.cpp -o CommandRunner.exe -mwindows -lgdi32 -luser32 -DUNICODE -D_UNICODE
```



## v1 프로그램 (current)
```base
커맨드 : 매크로 실행
직접 하드코딩으로 ShellExecuteW을 통해 모든 명령어 실행
```
현재 등록된 커맨드
```base
백준 과제, baekjoon : github, baekjoon, vscode 실행
vscode, vsc : vscode 실행
git, github : github/ChaeyulLim 으로 이동
exit : 종료
shutdown : pc를 완전히 종료한다.
reboot : 컴퓨터를 다시 시작한다.
```

추가 예정
```base
```

## v2 프로그램 (Next Prototype)
```base
커맨드 : 매크로 실행
text 파일을 한개 두어 그곳에 명령어들을 전부 기입,
그 후 실행 할 때 마다 파일의 내용을 읽어 실시간으로 적용할 예정
```

## v3 프로그램 (Next Prototype)
```base
명령어 시스템을 도입해 명령어를 추가하거나 삭제하는 등 관리 할 수 있도록 제작할 예정.
```