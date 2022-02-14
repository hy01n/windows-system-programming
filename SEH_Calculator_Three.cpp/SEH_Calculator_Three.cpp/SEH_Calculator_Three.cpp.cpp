#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

enum { DIV = 1,MUL,ADD,MIN,EXIT };

DWORD ShowMenu(void);
BOOL Calculator(void);

void Divide(int&, int&);
void Multiple(int, int);
void Add(int, int);
void Min(int, int);
DWORD FilterFunction(DWORD exptType);

int _tmain(int argc, TCHAR* argv[])
{
	BOOL state;

	__try
	{
		do {
			state = Calculator();
		} while (state == TRUE);
	}
	__except (EXCEPTION_EXECUTE_HANDLER)
	{
		_tprintf(_T("End of process\n"));
	}

	return 0;
}

DWORD ShowMenu(void)
{
	DWORD sel;
	_fputts(_T("-----Menu-----\n"), stdout);
	_fputts(_T("num 1: divide\n"), stdout);
	_fputts(_T("num 2: multiple\n"), stdout);
	_fputts(_T("num 3: add\n"), stdout);
	_fputts(_T("num 4: minus\n"), stdout);
	_fputts(_T("num 5: exit\n"), stdout);
	_fputts(_T("selection >>\n"), stdout);
	_tscanf(_T("%d"), &sel);
	return sel;
}
int num1, num2, result;

BOOL Calculator(void)
{
	DWORD sel;

	sel = ShowMenu();
	if (sel == EXIT)
	{
		return FALSE;
	}

	_fputts(_T("Input num1 num2:"), stdout);
	_tscanf(_T("%d %d"), &num1, &num2);

	__try
	{
		/*__try*/
		{
			switch (sel)
			{
			case DIV:
				Divide(num1, num2);
				break;

			case MUL:
				Multiple(num1, num2);
				break;
				
			case ADD:
				Add(num1, num2);
				break;

			case MIN:
				Min(num1, num2);
				break;
			}
		}
		/*__finally*/
		{
			_tprintf(_T("End operation\n\n"));
		}
	}
	__except (FilterFunction(GetExceptionCode()))
	{
		_tprintf(_T("except block!\n\n"));
	}
	return TRUE;
}


void Divide(int& a, int& b)
{
	_tprintf(_T("%d/%d=%d\n\n"), a, b, a / b);
}
void Multiple(int a, int b)
{
	_tprintf(_T("%d*%d=%d\n\n"), a, b, a * b);
}
void Add(int a, int b)
{
	_tprintf(_T("%d+%d=%d\n\n"), a, b, a + b);
}
void Min(int a, int b)
{
	_tprintf(_T("%d-%d=%d\n\n"), a, b, a - b);
}

DWORD FilterFunction(DWORD exptType)
{
	switch (exptType)
	{
	case EXCEPTION_INT_DIVIDE_BY_ZERO:
		_tprintf(_T("Wrong number inserted.\n"));
		_tprintf(_T("Input second number again:"));
		_tscanf(_T("%d"), &num2);
		//return EXCEPTION_CONTINUE_EXECUTION;
		return EXCEPTION_CONTINUE_SEARCH;
	default:
		return EXCEPTION_EXECUTE_HANDLER;
	}
}