// myCommandPrmpt
// (명령 프롬포트 골격)
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <locale.h>
#include <windows.h>

#define STR_LEN 256
#define CMD_TOKEN_NUM 10

TCHAR ERROR_CMD[] = _T("'%s is not executable program. \n");
TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" ,\t\n");

int CmdReadTokenize(void);
int CmdProcessing(int tokenNum);
TCHAR* StrLower(TCHAR*);

int _tmain(int argc, TCHAR* argv[])
{
    _tsetlocale(LC_ALL, _T("Korean"));

    if (argc > 2)
    {
        for (int i = 1; i < argc; i++)
            _tcscpy(cmdTokenList[i - 1], argv[i]);
        CmdProcessing(argc - 1);
    }

    DWORD isExit= NULL;
    while (1)
    {
        int tokenNum = CmdReadTokenize();
        if (tokenNum == 0)
            continue;

        isExit = CmdProcessing(tokenNum);
        if (isExit == TRUE)
        {
            _fputts(_T("End cmd processing. \n"), stdout);
            break;
        }
    }
    return 0;
}

int CmdReadTokenize(void)
{
    _fputts(_T("Best command prompt>>"), stdout);
    // _getts(cmdString);
    _getts_s(cmdString);
    TCHAR* token = _tcstok(cmdString, seps);
    int tokenNum = 0;
    while (token != NULL)
    {
        _tcscpy(cmdTokenList[tokenNum++], StrLower(token));
        token = _tcstok(NULL, seps);
    }
    return tokenNum;
}



// TCHAR int CmdProcessing(void)
// cmd

int CmdProcessing(int tokenNum)
{
    BOOL isRun;
    STARTUPINFO si = { 0, };
    PROCESS_INFORMATION pi;

    TCHAR cmdStringWithOptions[STR_LEN] = { 0, };
    TCHAR optString[STR_LEN] = { 0, };

    si.cb = sizeof(si);
    if (!_tcscmp(cmdTokenList[0], _T("exit")))
    {
        return TRUE;
    }
    else if (!_tcscmp(cmdTokenList[0], _T("start")))
    {
        if (tokenNum > 1)
        {
            for (int i = 1; i < tokenNum; i++)
            {
                _stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
                _stprintf(cmdStringWithOptions, _T("%s %s"), _T("CommandPrmpt_Three.exe"), optString);
            }
        }
        else
            _stprintf(cmdStringWithOptions, _T("%s"), _T("CmdProject.exe"));
        isRun = CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, TRUE, CREATE_NEW_CONSOLE, NULL, NULL, &si, &pi);

        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
    }
    else if (!_tcscmp(cmdTokenList[0], _T("echo")))
    {
        for (int i = 1; i < tokenNum; i++)
        {
            _stprintf(optString, _T("%s %s"), optString, cmdTokenList[i]);
        }

        _tprintf(_T("echo message: %s \n"), optString);
    }
    else
    {
        _tcscpy(cmdStringWithOptions, cmdTokenList[0]);

        for (int i = 1; i < tokenNum; i++)
            _stprintf(cmdStringWithOptions, _T("%s %s"), cmdStringWithOptions, cmdTokenList[i]);
        isRun = CreateProcess(NULL, cmdStringWithOptions, NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
        CloseHandle(pi.hProcess);
        CloseHandle(pi.hThread);
        if (isRun == FALSE)
            _tprintf(ERROR_CMD, cmdTokenList[0]);
    }
    return 0;
}

// TCHAR * StrLower(TCHAR * pStr)
// 문자열 모두 소문자로 만들고, 문자열 포인터 반환

TCHAR* StrLower(TCHAR* pStr)
{
    TCHAR* ret = pStr;

    while (*pStr)
    {
        if (_istupper(*pStr))
            *pStr = _totlower(*pStr);
        pStr++;
    }
    return ret;
}