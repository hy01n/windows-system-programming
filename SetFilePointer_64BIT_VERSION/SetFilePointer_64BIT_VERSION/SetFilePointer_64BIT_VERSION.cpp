#include <stdio.h>
#include <tchar.h>
#include <Windows.h>

#define STRING_LEN 100

TCHAR fileData[] = _T("abcdefghijklmnopqrstuvwxyz");

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR fileName[] = _T("abcd.dat");
	TCHAR readBuf[STRING_LEN];

	HANDLE hFile;
	DWORD numOfByteWritten = 0;
	DWORD dwPtrLow = 0;

	LONG lDistanceLow = sizeof(TCHAR) * 4;
	LONG lDistanceHigh = 0;
	
	hFile = CreateFile(fileName, GENERIC_WRITE, 0, 0, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, 0);
	WriteFile(hFile, fileData, sizeof(fileData), &numOfByteWritten,NULL);
	CloseHandle(hFile);

	hFile = CreateFile(fileName, GENERIC_READ, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("%s\n"), readBuf);

	dwPtrLow = SetFilePointer(hFile, lDistanceLow, &lDistanceHigh, FILE_BEGIN);
	// GetLastError부분이 32비트와 다른데 32비트일때는 0xFFFFFFFF 가 -1 이랑 같아서 에러코드인지 주솟값인지 판별 못함 -> 2^32-2개의 주소값을 반환할 수 있음. 64비트는 하위 4바이트가 0xFFFFFFFF가능.
	// 근데 이걸 64비트환경에서 fseek을 한다고 하면은 함수 특성상 DWORD 4바이트를 리턴인데 64비트는 8바이트이므로, 4바이트 반환에 나머지 상위 4바이트는 참조해서 알려준다.
	if ((dwPtrLow == INVALID_SET_FILE_POINTER) && (GetLastError() != NO_ERROR))
	{
		_tprintf(_T("SetFilePointer Error\n"));
	}

	ReadFile(hFile, readBuf, sizeof(readBuf), &numOfByteWritten, NULL);
	_tprintf(_T("%s\n"), readBuf);
	CloseHandle(hFile);
}