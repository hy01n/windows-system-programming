#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	DWORD n = 0;
	while (n < 100)
	{
		for (DWORD i = 00; i < 10000; i++)
			for (DWORD i = 00; i < 10000; i++);
		_fputts(_T("KernelObjProb2.exe"), stdout);
		n++;
	}
	return 0;
}