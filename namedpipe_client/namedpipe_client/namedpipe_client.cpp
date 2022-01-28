#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#define BUF_SIZE 1024

int _tmain(int argc, TCHAR* argv[])
{
	HANDLE hPipe;
	TCHAR readDataBuf[BUF_SIZE + 1];
	LPTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");

	while (1)
	{
		hPipe = CreateFile(pipeName, GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
		if (hPipe != INVALID_HANDLE_VALUE)
		{
			break;
		}

		if (GetLastError() != ERROR_PIPE_BUSY)
		{
			_tprintf(_T("Could not open pipe \n"));
			return -1;
		}


		if (!WaitNamedPipe(pipeName, 20000))
		{
			_tprintf(_T("Could not open pipe \n"));
			return -1;
		}
	}
	DWORD pipeMode = PIPE_READMODE_MESSAGE | PIPE_WAIT;
	BOOL isSuccess = SetNamedPipeHandleState(hPipe, &pipeMode, NULL, NULL);

	if (!isSuccess)
	{
		_tprintf(_T("SetNamedPipeHandleState failed"));
		return 0;
	}
		
	LPCTSTR fileName = _T("news.txt");
	DWORD bytesWritten = 0;

	isSuccess = WriteFile(hPipe, fileName, (_tcslen(fileName) + 1) * sizeof(TCHAR), &bytesWritten, NULL);
	if (!isSuccess)
	{
		_tprintf(_T("WriteFile failed"));
		return 0;
	}

	DWORD bytesRead = 0;
	while (1)
	{
		isSuccess = ReadFile(hPipe, readDataBuf, BUF_SIZE * sizeof(TCHAR), &bytesWritten, NULL);
		if (!isSuccess && GetLastError() != ERROR_MORE_DATA)
			break;
		readDataBuf[bytesRead] = 0;
		_tprintf(_T("%s \n", readDataBuf));
	}
	
	CloseHandle(hPipe);
	return 0;
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

	FILE* filePtr = _tfopen(fileName, _T("r"));
	if (filePtr == NULL)
	{
		_tprintf(_T("File open fault!\n"));
		return -1;
	}

	DWORD bytesWritten = 0;
	DWORD bytesRead = 0;

	while (!feof(filePtr))
	{
		bytesRead = fread(dataBuf, 1, BUF_SIZE, filePtr);

		WriteFile(hPipe, dataBuf, bytesRead, &bytesWritten, NULL);

		if (bytesRead != bytesWritten)
		{
			_tprintf(_T("Pipe write message error! \n"));
			break;
		}
	}

	FlushFileBuffers(hPipe);
	CloseHandle(hPipe);
	return 1;
}