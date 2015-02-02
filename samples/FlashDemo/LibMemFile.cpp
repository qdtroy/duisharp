#include <windows.h>
#include "LibMemFile.h"
#include "LibHook.h"

namespace libplus
{
	HANDLE (WINAPI *CLibMemFile::OCreateFileW)(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile) = &::CreateFileW;
	BOOL (WINAPI *CLibMemFile::OReadFile)(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped) = &::ReadFile;
	DWORD (WINAPI *CLibMemFile::OSetFilePointer)( HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod) = &::SetFilePointer;
	DWORD (WINAPI *CLibMemFile::OGetFileSize)( HANDLE hFile, LPDWORD lpFileSizeHigh) = &::GetFileSize;
	DWORD (WINAPI *CLibMemFile::OGetFileAttributesW)(LPCWSTR) = &::GetFileAttributesW;
	BOOL (WINAPI *CLibMemFile::OCloseHandle)(HANDLE hHandle) = &::CloseHandle;
	DWORD (WINAPI *CLibMemFile::OGetFullPathNameW)( LPCWSTR lpFileName, DWORD nBufferLength, LPWSTR lpBuffer, LPWSTR *lpFilePart) = &::GetFullPathNameW;
	HANDLE (WINAPI *CLibMemFile::OFindFirstFileW)( LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData) = ::FindFirstFileW;
	BOOL (WINAPI *CLibMemFile::OFindNextFileW)( HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData) = ::FindNextFileW;
	BOOL (WINAPI *CLibMemFile::OFindClose)( HANDLE hFindFile) = ::FindClose;

	MFFINDHANDLE* CLibMemFile::spFindHandleHead = NULL;
	CLibMemFile* CLibMemFile::spHead = NULL;
	CRITICAL_SECTION CLibMemFile::sCSFind;
	CRITICAL_SECTION CLibMemFile::sCSFile;
	CRITICAL_SECTION CLibMemFile::sCSHandle;

	CLibMemFile::CLibMemFile(LPCSTR pFileName, LPVOID lpFileBuffer, int nFileSize, DWORD dwFileAttributes)
	{
		if( (lstrlenA(pFileName) == 0) || (lpFileBuffer == NULL ))
			throw -1;
		if(::IsBadReadPtr(lpFileBuffer, nFileSize))
		{
			throw -2;
		}
		Init();
		int nRet;
		LONG lRet;
		int nLen = (int)(2 * lstrlenA(pFileName));
		LPWSTR lpwFileName = new WCHAR[nLen];
		nRet = MultiByteToWideChar(CP_THREAD_ACP, MB_ERR_INVALID_CHARS, pFileName, -1, lpwFileName, nLen);
		if(!nRet)
		{
			delete[] lpwFileName;
			throw GetLastError();
		}
		if(IsMemoryFile(lpwFileName))
		{
			delete[] lpwFileName;
			throw -2;
		}
		mdwFileAttributes = dwFileAttributes;
		mdwFileSizeHigh = 0;
		mdwFileSizeLow = nFileSize;
		mlpFileBuffer = (LPBYTE)lpFileBuffer;
		mlpFileName = lpwFileName;
		mpHandleHead = NULL;
		CLibMemFile *tp = this;
		// 使用TryEnterCriticalSection是为了兼容编译为静态库时,在用new方法初次创建CLibMemFile对象时
		// 静态初始化成员memfileInit还没有初始化sCSFile,此构造函数执行完毕后才构造memfileInit,完成初始化
		if(TryEnterCriticalSection(&sCSFile))
		{
			mpNext = spHead;
			lRet = InterlockedExchange(&(LONG&)spHead, (LONG&)tp);
			LeaveCriticalSection(&sCSFile);
		}
		else
		{
			if(spHead == NULL)
			{
				mpNext = spHead;
				lRet = InterlockedExchange(&(LONG&)spHead, (LONG&)tp);
			}
			else
			{
				throw -1;
			}
		}
	}

	CLibMemFile::CLibMemFile( LPCWSTR pFileName, LPVOID lpFileBuffer, int nFileSize, DWORD dwFileAttributes)
	{       
		if( (lstrlenW(pFileName) == 0) || (lpFileBuffer == NULL ))
		{
			throw -1;
		}
		if(::IsBadReadPtr(lpFileBuffer, nFileSize))
		{
			throw -2;
		}
		if(IsMemoryFile(pFileName))
		{
			throw -2;
		}
		Init();
		LONG lRet;
		mdwFileAttributes = dwFileAttributes;
		mdwFileSizeHigh = 0;
		mdwFileSizeLow = nFileSize;
		mlpFileBuffer = (LPBYTE)lpFileBuffer;
		mlpFileName = new WCHAR[lstrlenW(pFileName) + 1];
		lstrcpyW(mlpFileName, pFileName);

		mpHandleHead = NULL;
		CLibMemFile *tp = this;
		if(TryEnterCriticalSection(&sCSFile))
		{
			mpNext = spHead;
			lRet = InterlockedExchange(&(LONG&)spHead, (LONG&)tp);
			LeaveCriticalSection(&sCSFile);
		}
		else
		{
			if(spHead == NULL)
			{
				mpNext = spHead;
				lRet = InterlockedExchange(&(LONG&)spHead, (LONG&)tp);
			}
			else
			{
				throw -1;
			}
		}
	}

	CLibMemFile::~CLibMemFile(void)
	{
		EnterCriticalSection(&sCSHandle);
		if(mpHandleHead == NULL)
		{
			delete[] mlpFileName;
			mlpFileName = NULL;
		}
		LeaveCriticalSection(&sCSHandle);
		CLibMemFile *pMemFile, *pPreMemFile;
		EnterCriticalSection(&sCSFile);
		for(pPreMemFile = NULL, pMemFile = spHead; pMemFile != NULL; pPreMemFile = pMemFile, pMemFile = pMemFile->mpNext)
		{
			if(pPreMemFile != NULL)
			{
				::InterlockedExchange(&(LONG&)pPreMemFile->mpNext, (LONG&)pMemFile->mpNext);
			}
			else
			{
				::InterlockedExchange(&(LONG&)spHead, (LONG&)pMemFile->mpNext);
			}
		}
		LeaveCriticalSection(&sCSFile);

		Release();
	}

	BOOL CLibMemFile::Init(void)
	{
		LONG lRet = 0;
		InitializeCriticalSection(&sCSFind);
		InitializeCriticalSection(&sCSFile);
		InitializeCriticalSection(&sCSHandle);

		ReplaceIATEntryForAll( "KERNEL32.dll", OCreateFileW, &HCreateFileW);
		ReplaceIATEntryForAll( "KERNEL32.dll", OReadFile, &HReadFile);
		ReplaceIATEntryForAll( "KERNEL32.dll", OSetFilePointer, &HSetFilePointer);
		ReplaceIATEntryForAll( "KERNEL32.dll", OGetFileSize, &HGetFileSize);
		ReplaceIATEntryForAll( "KERNEL32.dll", OGetFileAttributesW, &HGetFileAttributesW);
		ReplaceIATEntryForAll( "KERNEL32.dll", OCloseHandle, &HCloseHandle);
		ReplaceIATEntryForAll( "KERNEL32.dll", OGetFullPathNameW, &HGetFullPathNameW);
		ReplaceIATEntryForAll( "KERNEL32.dll", OFindFirstFileW, &HFindFirstFileW);
		ReplaceIATEntryForAll( "KERNEL32.dll", OFindNextFileW, &HFindNextFileW);
		ReplaceIATEntryForAll( "KERNEL32.dll", OFindClose, &HFindClose);

		return !lRet;
	}

	BOOL CLibMemFile::Release(void)
	{
		if(spHead != NULL)
			return FALSE;
		LONG lRet = TRUE;

		ReplaceIATEntryForAll( "KERNEL32.dll", &HCreateFileW, OCreateFileW);
		ReplaceIATEntryForAll( "KERNEL32.dll", &HReadFile, OReadFile);
		ReplaceIATEntryForAll( "KERNEL32.dll", &HSetFilePointer, OSetFilePointer);
		ReplaceIATEntryForAll( "KERNEL32.dll", &HGetFileSize, OGetFileSize);
		ReplaceIATEntryForAll( "KERNEL32.dll", &HGetFileAttributesW, OGetFileAttributesW);
		ReplaceIATEntryForAll( "KERNEL32.dll", &HCloseHandle, OCloseHandle);
		ReplaceIATEntryForAll( "KERNEL32.dll", &HGetFullPathNameW, OGetFullPathNameW);
		ReplaceIATEntryForAll( "KERNEL32.dll", &HFindFirstFileW, OFindFirstFileW);
		ReplaceIATEntryForAll( "KERNEL32.dll", &HFindNextFileW, OFindNextFileW);
		ReplaceIATEntryForAll( "KERNEL32.dll", &HFindClose, OFindClose);

		DeleteCriticalSection(&sCSHandle);
		DeleteCriticalSection(&sCSFile);
		DeleteCriticalSection(&sCSFind);
		return !lRet;
	}

	CLibMemFile* CLibMemFile::IsMemoryFile(LPCWSTR lpFileName)
	{
		CLibMemFile* p;
		for(p = spHead; (p != NULL) && (lstrcmpW(p->mlpFileName, lpFileName) != 0); p = p->mpNext);
		return p;
	}

	CLibMemFile* CLibMemFile::IsMemoryFile(HANDLE hHandle, MFHANDLE** ppMfHandle)
	{
		CLibMemFile* pMemFile;
		MFHANDLE *pHandle;
		for(pMemFile = spHead; pMemFile != NULL; pMemFile = pMemFile->mpNext)
		{
			for(pHandle = pMemFile->mpHandleHead; pHandle != NULL; pHandle = pHandle->pNext)
			{
				if(pHandle->hHandle == hHandle)
				{
					*ppMfHandle = pHandle;
					return pMemFile;
				}
			}
		}
		ppMfHandle = NULL;
		return NULL;
	}

	HANDLE CLibMemFile::HCreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, \
		LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, \
		DWORD dwFlagsAndAttributes, HANDLE hTemplateFile)
	{
		HANDLE hRet;
		CLibMemFile *pMemFile;
		if(pMemFile = IsMemoryFile(lpFileName))
		{
			EnterCriticalSection(&sCSHandle);
			MFHANDLE *pHandle = new MFHANDLE;
			pHandle->pCurPointer = pMemFile->mlpFileBuffer;
			pHandle->pNext = pMemFile->mpHandleHead;
			if(pMemFile->mpHandleHead == NULL)
			{
				pHandle->hHandle = (HANDLE)(~size_t(pMemFile->mlpFileBuffer)&(~WORD(0)<<((sizeof(HANDLE) - sizeof(WORD))*8)));
			}
			else
			{
				pHandle->hHandle = (HANDLE)((LPBYTE)pMemFile->mpHandleHead->hHandle + 1);
			}
			LONG lRet = InterlockedExchange(&(LONG&)pMemFile->mpHandleHead, (LONG&)pHandle);
			hRet = pHandle->hHandle;
			LeaveCriticalSection(&sCSHandle);
		}
		else
		{
			hRet = OCreateFileW(lpFileName, dwDesiredAccess, dwShareMode, lpSecurityAttributes, dwCreationDisposition, dwFlagsAndAttributes, hTemplateFile);
		}
		return hRet;
	}

	BOOL CLibMemFile::HReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, \
		LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped)
	{
		BOOL bRet;
		MFHANDLE *pMfHandle;
		CLibMemFile *pMemFile;
		if(pMemFile = IsMemoryFile(hFile, &pMfHandle))
		{
			LPBYTE lpFileEnd = LPBYTE(pMemFile->mlpFileBuffer + pMemFile->mdwFileSizeLow);
			DWORD dwNumOfByteRead = 0;
			if(pMfHandle->pCurPointer >= lpFileEnd)
			{
				*lpNumberOfBytesRead = 0;
			}
			else if((pMfHandle->pCurPointer + nNumberOfBytesToRead) < lpFileEnd)
			{
				dwNumOfByteRead = nNumberOfBytesToRead;
			}
			else
			{
				dwNumOfByteRead = (DWORD)(lpFileEnd - pMfHandle->pCurPointer);
			}
			memcpy(lpBuffer, pMfHandle->pCurPointer, dwNumOfByteRead);
			pMfHandle->pCurPointer = pMfHandle->pCurPointer + dwNumOfByteRead;
			*lpNumberOfBytesRead = dwNumOfByteRead;
			bRet = TRUE;
		}
		else
		{
			bRet = OReadFile(hFile, lpBuffer, nNumberOfBytesToRead, lpNumberOfBytesRead, lpOverlapped);
		}
		return bRet;
	}

	DWORD CLibMemFile::HGetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh)
	{       
		DWORD dwRet;
		MFHANDLE *pMfHandle;
		CLibMemFile *pMemFile = IsMemoryFile(hFile, &pMfHandle);
		if(pMemFile)
		{
			*lpFileSizeHigh = pMemFile->mdwFileSizeHigh;
			dwRet = pMemFile->mdwFileSizeLow;
		}
		else
		{
			dwRet = OGetFileSize(hFile, lpFileSizeHigh);
		}
		return dwRet;
	}

	DWORD CLibMemFile::HSetFilePointer(HANDLE hFile, LONG lDistanceToMove, \
		PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod)
	{
		DWORD dwRet;
		MFHANDLE *pMfHandle;
		CLibMemFile *pMemFile;
		if(pMemFile = IsMemoryFile(hFile, &pMfHandle))
		{
			switch(dwMoveMethod)
			{
			case FILE_BEGIN:
				pMfHandle->pCurPointer = pMemFile->mlpFileBuffer + lDistanceToMove;
				break;
			case FILE_CURRENT:
				pMfHandle->pCurPointer = pMfHandle->pCurPointer + lDistanceToMove;
				break;
			case FILE_END:
				pMfHandle->pCurPointer = pMemFile->mlpFileBuffer + pMemFile->mdwFileSizeLow + lDistanceToMove;
				break;
			}
			if(LPBYTE(pMfHandle->pCurPointer) < LPBYTE(pMemFile->mlpFileBuffer))
			{
				dwRet = lDistanceToMove -  DWORD(pMemFile->mlpFileBuffer - pMfHandle->pCurPointer);
				pMfHandle->pCurPointer = pMemFile->mlpFileBuffer;
			}
			if(pMfHandle->pCurPointer < (pMemFile->mlpFileBuffer + pMemFile->mdwFileSizeLow))
			{
				dwRet = lDistanceToMove - DWORD(pMfHandle->pCurPointer - pMemFile->mlpFileBuffer);
				pMfHandle->pCurPointer = LPBYTE(pMemFile->mlpFileBuffer) + pMemFile->mdwFileSizeLow;
			}
		}
		else
		{
			dwRet = OSetFilePointer(hFile, lDistanceToMove, lpDistanceToMoveHigh, dwMoveMethod);
		}
		return dwRet;
	}

	DWORD CLibMemFile::HGetFileAttributesW(LPCWSTR lpFileName)
	{
		DWORD dwRet;
		CLibMemFile *pMemFile;
		if(pMemFile = IsMemoryFile(lpFileName))
		{
			dwRet = pMemFile->mdwFileAttributes;
		}
		else
		{
			dwRet = OGetFileAttributesW(lpFileName);
		}
		return dwRet;
	}

	BOOL CLibMemFile::HCloseHandle(HANDLE hObject)
	{
		CLibMemFile* pMemFile;
		MFHANDLE *pPreHandle = NULL;
		MFHANDLE *pHandle;        
		EnterCriticalSection(&sCSHandle);
		for(pMemFile = spHead; pMemFile != NULL; pMemFile = pMemFile->mpNext)
		{
			for(pHandle = pMemFile->mpHandleHead; pHandle != NULL; pPreHandle = pHandle, pHandle = pHandle->pNext)
			{
				if(pHandle->hHandle == hObject)
				{
					if(pPreHandle)
					{
						::InterlockedExchange(&(LONG&)pPreHandle->pNext, (LONG&)pMemFile->mpNext);
					}
					else
					{
						::InterlockedExchange(&(LONG&)pMemFile->mpHandleHead, NULL);
					}
					delete pHandle;
					LeaveCriticalSection(&sCSHandle);
					return TRUE;
				}
			}
		}
		LeaveCriticalSection(&sCSHandle);
		return OCloseHandle(hObject);
	}

	DWORD CLibMemFile::HGetFullPathNameW(LPCWSTR lpFileName, DWORD nBufferLength, LPWSTR lpBuffer, LPWSTR *lpFilePart)
	{
		DWORD dwRet;
		CLibMemFile *pMemFile = IsMemoryFile(lpFileName);
		if(pMemFile)
		{
			int nStrLen = lstrlenW(lpFileName);
			LPWSTR pStr;
			if(nBufferLength < (nStrLen + 1) * sizeof(WCHAR))
				return 0;
			lstrcpyW((LPWSTR)lpBuffer, lpFileName);
			for(pStr = lpBuffer + nStrLen; (*pStr != L'//') && (pStr >= lpBuffer); pStr--);
			*lpFilePart = ++pStr;
			dwRet = nStrLen;
		}
		else
		{
			dwRet = OGetFullPathNameW(lpFileName, nBufferLength, lpBuffer, lpFilePart);
		}
		return dwRet;
	}

	HANDLE CLibMemFile::HFindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData)
	{
		HANDLE hRet;
		CLibMemFile *pMemFile;
		if(pMemFile = IsMemoryFile(lpFileName))
		{
			MFFINDHANDLE *pFindHandle = new MFFINDHANDLE;
			EnterCriticalSection(&sCSFind);
			pFindHandle->pCurMemoryFile = pMemFile;
			pFindHandle->pNext = spFindHandleHead;
			if(spFindHandleHead == NULL)
			{
				pFindHandle->hHandle = (HANDLE)(~size_t(&spFindHandleHead)&(~WORD(0)<<((sizeof(HANDLE) - sizeof(WORD))*8)));//用高位作为内存文件间的标志，而低位用来标识不同的句柄
			}
			else
			{
				pFindHandle->hHandle = (HANDLE)(PBYTE(spFindHandleHead->hHandle) + 1);
			}
			LONG lRet = InterlockedExchange(&(LONG&)spFindHandleHead, (LONG&)pFindHandle);
			hRet = pFindHandle->hHandle;
			LeaveCriticalSection(&sCSFind);
		}
		else
		{
			hRet = OFindFirstFileW(lpFileName, lpFindFileData);
		}
		return hRet;
	}

	BOOL CLibMemFile::HFindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData)
	{
		BOOL bRet;
		CLibMemFile* pMemFile;
		MFFINDHANDLE *pHandle;         
		EnterCriticalSection(&sCSFind);
		for(pMemFile = spHead; pMemFile != NULL; pMemFile = pMemFile->mpNext)
		{
			for(pHandle = spFindHandleHead; pHandle != NULL; pHandle = pHandle->pNext)
			{
				if(pHandle->hHandle == hFindFile)
				{
					lstrcpyW(lpFindFileData->cFileName, pMemFile->mlpFileName);
					lpFindFileData->nFileSizeHigh = 0;
					lpFindFileData->nFileSizeLow = pMemFile->mdwFileSizeLow;
					LeaveCriticalSection(&sCSFind);
					return TRUE;
				}
			}
		}
		LeaveCriticalSection(&sCSFind);
		bRet = OFindNextFileW(hFindFile, lpFindFileData);
		return bRet;
	}

	BOOL CLibMemFile::HFindClose(HANDLE hFindFile)
	{
		BOOL bRet;
		CLibMemFile* pMemFile;
		MFFINDHANDLE *pPreHandle = NULL;
		MFFINDHANDLE *pHandle;         
		EnterCriticalSection(&sCSFind);
		for(pMemFile = spHead; pMemFile != NULL; pMemFile = pMemFile->mpNext)
		{
			for(pHandle = spFindHandleHead; pHandle != NULL; pPreHandle = pHandle, pHandle = pHandle->pNext)
			{
				if(pHandle->hHandle == hFindFile)
				{
					if(pPreHandle)
					{
						pPreHandle->pNext = pHandle->pNext;
						::InterlockedExchange(&(LONG&)pPreHandle->pNext, (LONG&)pMemFile->mpNext);
					}
					else
					{
						spFindHandleHead = NULL;
						::InterlockedExchange(&(LONG&)spFindHandleHead,NULL);
					}
					delete pHandle;
					LeaveCriticalSection(&sCSFind);
					return TRUE;
				}
			}
		}
		LeaveCriticalSection(&sCSFind);
		bRet = OFindClose(hFindFile);
		return bRet;
	}

	CLibMemFile::CLibMemFile(CLibMemFile& obj)
	{

	}

	CLibMemFile& CLibMemFile::operator=(CLibMemFile& obj)
	{
		return obj;
	}
}