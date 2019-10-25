// ShdMem.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include <WinNT.h>
#include <tchar.h>
#include <conio.h>

#define BUF_SIZE 256
TCHAR szName[]=TEXT("Local\\MyMappedSharedMemory");
TCHAR szMsg[]=TEXT("Hello ! MEssage from first process ShdMEM");

int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE	hMapFileHndr;
	LPCTSTR	shdBuf;

	hMapFileHndr = CreateFileMapping (
								INVALID_HANDLE_VALUE,
								NULL,
								PAGE_READWRITE,
								0,
								BUF_SIZE,
								szName);

	if (hMapFileHndr == NULL)
	{
		_tprintf (TEXT("Could not create file mapping object (%d).\n"), GetLastError());
		return -1;
	}

	shdBuf = (LPTSTR) MapViewOfFile (
								hMapFileHndr,
								FILE_MAP_ALL_ACCESS,
								0,
								0,
								BUF_SIZE);

	if (!shdBuf)
	{
		_tprintf (TEXT("Unable to map the file (%d).\n"), GetLastError());
		CloseHandle (hMapFileHndr);
		return -1;
	}

	CopyMemory ((PVOID)shdBuf, szMsg, sizeof(szMsg));
	_getch();

	UnmapViewOfFile (shdBuf);
	CloseHandle (hMapFileHndr);

	return 0;
}
