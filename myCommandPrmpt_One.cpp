// myCommandPrmpt_One.cpp
// (��� ������Ʈ ���)

#include <stdio.h>
#include <stdlib.h>
#include <tchar.h>
#include <locale.h>
#include <windows.h>

#define STR_LEN 256
#define CMD_TOKEN_NUM 10

TCHAR ERROR_CMD[] = _T("'%s is not executable program. \n");

int CmdProcessing(void);
TCHAR * StrLower(TCHAR *);

int tmain(int agrc, TCHAR * argv[])
{
    _tsetlocale(LC_ALL,_T("Korean"));

    DWORD isExit;
    while(1)
    {
        isExit = CmdProcessing();
        if(isExit == TRUE)
        {
            _fputts(_T("End cmd processing. \n",stdout));
            break;
        }
    }
    return 0;
}

TCHAR cmdString[STR_LEN];
TCHAR cmdTokenList[CMD_TOKEN_NUM][STR_LEN];
TCHAR seps[] = _T(" ,\t\n");

// TCHAR int CmdProcessing(void)
// cmd

int CmdProceessing(void)
{
    _fputts(_T("Best command prompt>>"), stdout);
    // _getts(cmdString);
    _getts(cmdString);
    TCHAR * token = _tcstok(cmdString, seps);
    int tokenNum = 0;
    while(token != NULL)
    {
        _tcscpy(cmdTokenList[tokenNum++], StrLower(token));
        token = _tcstok(NULL, seps);
    }

    if(!_tcscmp(cmdTokenList[0], _T("exit")))
    {
        return TRUE;
    }
    else if(!_tcscmp(cmdTokenList[0], _T("more command 1")))
    {

    }
    else if(!_tcscmp(cmdTokenList[0], _T("more command 2")))
    {

    }
    else
    {
        _tprintf(ERROR_CMD, cmdTokenList[0]);
    }
    return 0;
}

// TCHAR * StrLower(TCHAR * pStr)
// ���ڿ� ��� �ҹ��ڷ� �����, ���ڿ� ������ ��ȯ

TCHAR * StrLower(TCHAR *pStr)
{
    TCHAR *ret = pStr;

    while(*pStr)
    {
        if(_istupper(*pStr))
            *pStr = _totlower(*pStr);
        pStr++;
    }
    return ret;
}