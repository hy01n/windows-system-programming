#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <cstring>

int _tmain(int argc, TCHAR* argv[])
{
	STARTUPINFO si[2];

	si[0] = { 0, };
	si[1] = { 0, };

	PROCESS_INFORMATION pi[2];
	
	DWORD return_val[2];

	TCHAR command1[] = _T("PartAdder.exe 1 5");
	TCHAR command2[] = _T("PartAdder.exe 6 10");

	DWORD sum = 0;

	for (DWORD i = 0; i < 2; i++)
	{
		si[i].cb = sizeof(si[i]);
	}

	CreateProcess(NULL, command1, NULL, NULL, TRUE, 0, NULL, NULL, &si[0], &pi[0]);
	CreateProcess(NULL, command2, NULL, NULL, TRUE, 0, NULL, NULL, &si[1], &pi[1]);


	/*for (DWORD i = 0; i < 2; i++)
	{
		CloseHandle(pi[i].hThread);
	}*/

	HANDLE h[2];
	h[0] = pi[0].hProcess;
	h[1] = pi[1].hProcess;
	WaitForMultipleObjects( 2,h,TRUE, INFINITE);
	

	for (DWORD i = 0; i < 2; i++)
	{
		GetExitCodeProcess(pi[i].hProcess, &return_val[i]);
	}

	for (DWORD i = 0; i < 2; i++)
	{
		if (return_val[i] == -1)
			return -1;
	}

	for (DWORD i = 0; i < 2; i++)
	{
		sum += return_val[i];
	}
	
	_tprintf(_T("total : %d \n"), sum);

	
	/*for (DWORD i = 0; i < 2; i++)
	{
		CloseHandle(pi[i].hProcess);
	}*/

	return 0;
}
