﻿#define _CRT_SECURE_NO_WARINGS
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hParent = (HANDLE)_ttoi(argv[1]);
	DWORD isSuccess = WaitForSingleObject(hParent, INFINITE);

	_tprintf(_T("[Child Process]\n"));
	if (isSuccess == WAIT_FAILED)
	{
		_tprintf(_T("WAIT_FAILED returned!"));
		Sleep(10000);
		return -1;
	}
	else
	{
		_tprintf(_T("General Leed said, \"Don't inform ")_T("the enemy my death\""));
		Sleep(10000);
		return 0;
	}
}