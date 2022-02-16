#include <stdio.h>
#include <tchar.h>
#include <windows.h>

TCHAR strData[] =
_T("aaaaaaaaaaaaaaaaaaaaaaaaaa\n")
_T("bbbbbbbbbbbbbbbbbbbbbbbbbbbbbbb\n")
_T("ccccccccccccccccccccccccccccccc\n")
_T("ddddddddddddddddd\n");

void WINAPI FileIOCompletionRoutine(DWORD, DWORD, LPOVERLAPPED);

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("data.txt");
	HANDLE hFile = CreateFile(fileName, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, 0);
	if (hFile == INVALID_HANDLE_VALUE)
	{
		_tprintf(_T("File creation fault!\n"));
		return -1;
	}

	OVERLAPPED overlappedInst;
	memset(&overlappedInst, 0, sizeof(overlappedInst));
	overlappedInst.hEvent = (HANDLE)1234;
	WriteFileEx(hFile, strData, sizeof(strData), &overlappedInst, FileIOCompletionRoutine);
	  
	SleepEx(INFINITE, TRUE);
	CloseHandle(hFile);
	return 1;
}

VOID WINAPI FileIOCompletionRoutine(DWORD errorCode, DWORD numOfBytesTransfered, LPOVERLAPPED overlapped)
{
	_tprintf(_T("File write result\n"));
	_tprintf(_T("Error code : %u\n"), errorCode);
	_tprintf(_T("Other info : %u\n"), (DWORD)overlapped->hEvent);
}