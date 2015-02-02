// LibHook.h
//
/////////////////////////////////////////////////////////////////////////////
#pragma once


#include <Windows.h>
#include <winternl.h>
#include <shlobj.h>
#include <atlstr.h>
///////////////////////////////////////////////////////////////////////////////

namespace libplus
{
	// Enumerate all the loaded modules in the current process, and search for the IAT to be processed
	void ReplaceIATEntryForAll(LPCSTR lpszDllName, LPVOID pfnCurrent, LPVOID pfnNew);
	// search in IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT for the special module
	BOOL ReplaceIATEntryInDelayImageImportTable(HANDLE hBaseAddress, LPCSTR lpszDllName, LPVOID pfnCurrent, LPVOID pfnNew);
	// search in IMAGE_IMPORT_DESCRIPTOR for the special module
	BOOL ReplaceIATEntryInImageImportTable(HANDLE hBaseAddress, LPCSTR lpszDllName, LPVOID pfnCurrent, LPVOID pfnNew);
}