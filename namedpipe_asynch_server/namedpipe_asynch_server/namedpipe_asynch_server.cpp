#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <iostream>

#define BUF_SIZE 1024
int CommToClient(HANDLE);

int _tmain(int argc, TCHAR* argv[])
{
	LPTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
	HANDLE hPipe;
	while (1)
	{
		hPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT, PIPE_UNLIMITED_INSTANCES, BUF_SIZE / 2, BUF_SIZE / 2, 20000, NULL);
		if (hPipe == INVALID_HANDLE_VALUE)
		{
			_tprintf(_T("CreatePipe failed"));
			return -1;
		}

		BOOL isSuccess = 0;
		isSuccess = ConnectNamedPipe(hPipe, NULL) ? TRUE : (GetLastError() == ERROR_PIPE_CONNECTED);
		if (isSuccess)
		{
			CommToClient(hPipe);
		}
		else
		{
			CloseHandle(hPipe);
		}
		return 1;
	}
}

int CommToClient(HANDLE hPipe)
{
	TCHAR fileName[MAX_PATH];
	TCHAR dataBuf[BUF_SIZE];

	BOOL isSuccess;
	DWORD fileNameSize;
	isSuccess = ReadFile(hPipe, fileName, MAX_PATH * sizeof(TCHAR), &fileNameSize, NULL);

	if (!isSuccess || fileNameSize == 0)
	{
		_tprintf(_T("Pipe read message error! \n"));
		return -1;
	}

	//TCHAR path[128];
	FILE* filePtr = _tfopen(fileName, _T("r"));
	//GetCurrentDirectory(128, path);
	//printf("%s\n", path);

	if (filePtr == NULL)
	{
		_tprintf(_T("File open fault!\n"));
		return -1;
	}

	OVERLAPPED overlappedInst;
	memset(&overlappedInst, 0, sizeof(overlappedInst));
	overlappedInst.hEvent = CreateEvent(NULL, TRUE, TRUE, NULL);

	DWORD bytesWritten = 0;
	DWORD bytesRead = 0;
	DWORD bytesWrite = 0, bytesTransfer = 0;

	while (!feof(filePtr))
	{
		bytesRead = fread(dataBuf, 1, BUF_SIZE, filePtr);
		bytesWrite = bytesRead;
		isSuccess = WriteFile(hPipe, dataBuf, bytesRead, &bytesWritten, &overlappedInst);
		if (!isSuccess && GetLastError() != ERROR_IO_PENDING) {
			_tprintf(_T("Pipe write message error!\n"));
			break;
		}
		/*if (bytesRead != bytesWritten)
		{
			_tprintf(_T("Pipe write message error! \n"));
			break;
		}*/

		WaitForSingleObject(overlappedInst.hEvent, INFINITE);
		GetOverlappedResult(hPipe, &overlappedInst, &bytesTransfer, FALSE);
		_tprintf(_T("Transferred data size : %u\n"),bytesTransfer);

	}

	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	return 1;
}