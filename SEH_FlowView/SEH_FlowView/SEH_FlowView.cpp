#include <stdio.h>
#include <tchar.h>
#include <windows.h>

int _tmain(int argc, TCHAR* argv[])
{
	_tprintf(_T("start point!\n"));

	int* p = NULL;
	__try
	{
		*p = 100;
		_tprintf(_T("value: %d"), *p);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		_tprintf(_T("exception occurred!\n"));
	}
	_tprintf(_T("end point!\n"));
	return 0;
}