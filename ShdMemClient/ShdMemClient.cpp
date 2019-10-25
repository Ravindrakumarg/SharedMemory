// ShdMemClient.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>

#define BUF_SIZE	256
TCHAR szName[] = TEXT("Local\\MyMappedSharedMemory");


int _tmain(int argc, _TCHAR* argv[])
{
	HANDLE	hShdMem;
	LPCTSTR szBuf;

	hShdMem = OpenFileMapping (
						FILE_MAP_ALL_ACCESS,
						FALSE,
						szName);

	if (hShdMem == NULL)
	{
		_tprintf (TEXT("Unable to open the map file=(%d).\n"), GetLastError());
		return -1;
	}

	szBuf = (LPCTSTR)MapViewOfFile (
								hShdMem,
								FILE_MAP_ALL_ACCESS,
								0,
								0,
								BUF_SIZE);

	if (szBuf == NULL)
	{
		_tprintf(TEXT("Could not map view of file (%d).\n"), GetLastError());
		CloseHandle(hShdMem);
		return -1;
	}

	MessageBox (NULL, szBuf, TEXT("Process Communicator"), MB_OK); 

	UnmapViewOfFile(szBuf);
	CloseHandle (hShdMem);

	return 0;
}

