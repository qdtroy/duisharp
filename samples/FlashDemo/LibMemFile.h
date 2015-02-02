//////////////////////////////////////////////////////////////////////////////
// LibMemFile.h
#pragma once

namespace libplus
{
	class CLibMemFile;

	//////////////////////////////////////////////////////////////////////////////
	// 结构体
	struct MFHANDLE
	{
		HANDLE hHandle;
		LPBYTE pCurPointer;
		MFHANDLE *pNext;
	};
	struct MFFINDHANDLE
	{
		HANDLE hHandle;
		CLibMemFile *pCurMemoryFile;
		MFFINDHANDLE *pNext;
	};

	//////////////////////////////////////////////////////////////////////////////
	// CLibMemFile
	class CLibMemFile
	{
	public:
		CLibMemFile( LPCSTR pFileName, LPVOID lpFileBuffer, int nFileSize, \
			DWORD dwFileAttributes = FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_READONLY);
		CLibMemFile( LPCWSTR pFileName, LPVOID lpFileBuffer, int nFileSize, \
			DWORD dwFileAttributes = FILE_ATTRIBUTE_ARCHIVE | FILE_ATTRIBUTE_READONLY);
		virtual ~CLibMemFile(void);

	public:
		static BOOL Init(void);
		static BOOL Release(void);
		static CLibMemFile* IsMemoryFile(LPCWSTR lpFileName);

	protected:
		// 是否内存文件
		static CLibMemFile* IsMemoryFile(HANDLE hHandle, MFHANDLE** ppMfHandle);

		// 系统函数
		static HANDLE (WINAPI *OCreateFileW)(LPCWSTR lpFileName, DWORD dwDesiredAccess, \
			DWORD dwShareMode, LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, \
			DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
		static BOOL (WINAPI *OReadFile)(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, \
			LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
		static DWORD (WINAPI *OSetFilePointer)( HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
		static DWORD (WINAPI *OGetFileSize)( HANDLE hFile, LPDWORD lpFileSizeHigh);
		static DWORD (WINAPI *OGetFileAttributesW)(LPCWSTR);
		static BOOL (WINAPI *OCloseHandle)(HANDLE hHandle);
		static DWORD (WINAPI *OGetFullPathNameW)( LPCWSTR lpFileName, DWORD nBufferLength, LPWSTR lpBuffer, LPWSTR *lpFilePart);
		static HANDLE (WINAPI *OFindFirstFileW)( LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);
		static BOOL (WINAPI *OFindNextFileW)( HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData);
		static BOOL (WINAPI *OFindClose)( HANDLE hFindFile);

		// 拦截函数
		static HANDLE WINAPI HCreateFileW(LPCWSTR lpFileName, DWORD dwDesiredAccess, DWORD dwShareMode, \
			LPSECURITY_ATTRIBUTES lpSecurityAttributes, DWORD dwCreationDisposition, DWORD dwFlagsAndAttributes, HANDLE hTemplateFile);
		static BOOL WINAPI HReadFile(HANDLE hFile, LPVOID lpBuffer, DWORD nNumberOfBytesToRead, \
			LPDWORD lpNumberOfBytesRead, LPOVERLAPPED lpOverlapped);
		static DWORD WINAPI HSetFilePointer(HANDLE hFile, LONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
		static DWORD WINAPI HGetFileSize(HANDLE hFile, LPDWORD lpFileSizeHigh);
		static BOOL WINAPI HCloseHandle(HANDLE hObject);
		static DWORD WINAPI HGetFileAttributesW(LPCWSTR lpFileName);
		static DWORD WINAPI HGetFullPathNameW(LPCWSTR lpFileName, DWORD nBufferLength, LPWSTR lpBuffer, LPWSTR *lpFilePart);
		static HANDLE WINAPI HFindFirstFileW(LPCWSTR lpFileName, LPWIN32_FIND_DATAW lpFindFileData);
		static BOOL WINAPI HFindNextFileW(HANDLE hFindFile, LPWIN32_FIND_DATAW lpFindFileData);
		static BOOL WINAPI HFindClose(HANDLE hFindFile);

	private:
		// 阻止拷贝构造函数
		CLibMemFile(CLibMemFile& obj);
		CLibMemFile& operator=(CLibMemFile& obj);

	protected:
		// 变量
		MFHANDLE *mpHandleHead;
		WCHAR* mlpFileName;
		LPBYTE mlpFileBuffer;
		DWORD mdwFileSizeLow;
		DWORD mdwFileSizeHigh;
		DWORD mdwFileAttributes;
		CLibMemFile *mpNext;

		static MFFINDHANDLE *spFindHandleHead;
		static CLibMemFile *spHead;
		// 同步锁
		static CRITICAL_SECTION sCSFind;
		static CRITICAL_SECTION sCSFile;
		static CRITICAL_SECTION sCSHandle;
	};
}