﻿#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hFile = CreateFile(_T("data.dat"), GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("Could not open file."));
	}
		
	HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_WRITECOPY, 0, 0, NULL);
	if (hMapFile == NULL)
	{
		_tprintf(_T("Could not create map of file\n"));
	}

	TCHAR* pWrite = (TCHAR*)MapViewOfFile(hMapFile, FILE_MAP_COPY, 0, 0, 0);
	if (pWrite == NULL)
	{
		_tprintf(_T("Could not map view of file\n"));
	}

	pWrite[0] = 1, pWrite[1] = 3; pWrite[2] = 0;
	pWrite[3] = 2; pWrite[4] = 4; pWrite[5] = 5;

	_tprintf(_T("%d %d %d\n"), pWrite[0], pWrite[1], pWrite[2]);

	UnmapViewOfFile(pWrite);
	CloseHandle(hMapFile);
	CloseHandle(hFile);
	_tprintf(_T("End of process!\n"));
	return 0;

}