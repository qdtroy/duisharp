#include "LibHook.h"

#include <Dbghelp.h>
#include <DelayImp.h>
#include <Psapi.h>

#pragma comment( lib, "Dbghelp.lib" )
#pragma comment( lib, "Psapi.lib" )

///////////////////////////////////////////////////////////////////////////////

namespace libplus
{
	//////////////////////////////////////////////////////////////////////////
	// Enumerate all the loaded modules in the current process, and search for the IAT to be processed
	void ReplaceIATEntryForAll(LPCSTR lpszDllName, LPVOID pfnCurrent, LPVOID pfnNew)
	{
		HMODULE hMods[1024] = {0};
		DWORD cbNeeded;
		HANDLE hProcess = ::GetCurrentProcess();
		if( ::EnumProcessModules( hProcess, hMods, sizeof(hMods), &cbNeeded))
		{
			for ( UINT i = 0; i < (cbNeeded / sizeof(HMODULE)); i++ )
			{
				ReplaceIATEntryInImageImportTable( hMods[i], lpszDllName, pfnCurrent, pfnNew );
			}
		}
	}

	// search in IMAGE_IMPORT_DESCRIPTOR for the special module
	BOOL ReplaceIATEntryInImageImportTable(HANDLE hBaseAddress, LPCSTR lpszDllName, LPVOID pfnCurrent, LPVOID pfnNew)
	{
		try
		{
			DWORD dwSize = 0;
			PIMAGE_SECTION_HEADER pFoundHeader = NULL;
			PIMAGE_IMPORT_DESCRIPTOR pImgImportDescriptor
				= (PIMAGE_IMPORT_DESCRIPTOR)ImageDirectoryEntryToDataEx( hBaseAddress
				, TRUE
				, IMAGE_DIRECTORY_ENTRY_IMPORT
				, &dwSize
				, &pFoundHeader
				);
			if( pImgImportDescriptor == NULL ){ return FALSE; }
			while (pImgImportDescriptor->Name)
			{
				if ( lstrcmpiA((CHAR*)((PBYTE)hBaseAddress+pImgImportDescriptor->Name), lpszDllName) == 0 )
				{
					break; // found
				}
				++pImgImportDescriptor;
			}
			if( !pImgImportDescriptor->Name )
				return ReplaceIATEntryInDelayImageImportTable( hBaseAddress, lpszDllName, pfnCurrent, pfnNew);

			// retrieve IAT
			PIMAGE_THUNK_DATA pThunk = (PIMAGE_THUNK_DATA)(((LPBYTE)hBaseAddress) + pImgImportDescriptor->FirstThunk);

			// enumerate functions in the IAT
			while(pThunk->u1.Function)
			{
				PDWORD lpAddr = (PDWORD)&(pThunk->u1.Function);
				if(*lpAddr == (DWORD)pfnCurrent)
				{
					// modify the address
					if(::WriteProcessMemory(::GetCurrentProcess(), lpAddr, &pfnNew, sizeof(DWORD), NULL))
						return TRUE;
					else
						return FALSE;
				} 
				pThunk++;
			}
		}
		catch(...)
		{

		}
		return FALSE;
	}

	// search in IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT for the special module
	BOOL ReplaceIATEntryInDelayImageImportTable(HANDLE hBaseAddress, LPCSTR lpszDllName, LPVOID pfnCurrent, LPVOID pfnNew)
	{
		DWORD dwSize = 0;
		PIMAGE_SECTION_HEADER pFoundHeader = NULL;
		PImgDelayDescr pImgDelayDescr
			= (PImgDelayDescr)ImageDirectoryEntryToDataEx( hBaseAddress
			, TRUE
			, IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT
			, &dwSize
			, &pFoundHeader
			);
		if( pImgDelayDescr == NULL ){ return FALSE; }

		while (pImgDelayDescr->rvaDLLName)
		{
			try
			{
				if ( lstrcmpiA((CHAR*)((PBYTE)hBaseAddress+pImgDelayDescr->rvaDLLName), lpszDllName) == 0 )
				{
					break;
				}
			}
			catch(...)
			{

			}
			++pImgDelayDescr;
		}
		// Not found in IMAGE_DIRECTORY_ENTRY_DELAY_IMPORT
		if( !pImgDelayDescr->rvaDLLName )
			return FALSE;

		// retrieve IAT
		PIMAGE_THUNK_DATA pThunk = NULL;
		if( (pImgDelayDescr->grAttrs & dlattrRva) == 0 )
			return FALSE;
		pThunk = (PIMAGE_THUNK_DATA)(((LPBYTE)hBaseAddress) + pImgDelayDescr->rvaIAT); 

		// enumerate functions in the IAT
		while(pThunk->u1.Function)
		{
			PDWORD lpAddr = (PDWORD)&(pThunk->u1.Function);
			if(*lpAddr == (DWORD)pfnCurrent)
			{
				// modify the address
				::WriteProcessMemory(::GetCurrentProcess(), lpAddr, &pfnNew, sizeof(DWORD), NULL);
				return TRUE;
			} 
			pThunk++;
		}

		return FALSE;
	}
}