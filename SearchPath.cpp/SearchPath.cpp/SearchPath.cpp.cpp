#define _CRT_SECURE_NO_WARNINGS
//1.실행중 프로그램 로드된 디렉터리
//2.현재 디렉터리
//3.시스템 디렉터리 (c:windows\system32)
//4.윈도우즈 디렉터리 (c:windows)
//5.PATH에 등록된 디렉터리
//순으로 검색
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[MAX_PATH];
	TCHAR bufFIlePath[MAX_PATH];
	LPTSTR lpFilePart;
	DWORD result;

	_tprintf(_T("Insert name of the file to find: "));
	_tscanf(_T("%s"), fileName);

	result = SearchPath(NULL, fileName, NULL, MAX_PATH, bufFIlePath, &lpFilePart);

	if (result == 0)
	{
		_tprintf(_T("File not found!\n"));
	}
	else
	{
		_tprintf(_T("File path :%s\n"),bufFIlePath);
		_tprintf(_T("File name only: %s\n"),lpFilePart);
	}
	return 0;
}