#ifndef __UIBASE_H__
#define __UIBASE_H__

#include <Shlwapi.h>
#include <vector>

namespace duisharp {

	/////////////////////////////////////////////////////////////////////////////////////
	// define useful macros from windowsx.h
#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lParam)	((int)(short)LOWORD(lParam))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lParam)	((int)(short)HIWORD(lParam))
#endif

	/////////////////////////////////////////////////////////////////////////////////////
	//
#ifndef FREE_APTR
#define FREE_APTR(x)					if(x){ delete [] x; x = NULL; }
#endif
#ifndef FREE_PTR
#define FREE_PTR(x)						if(x){ delete (x); x = NULL; }
#endif
#ifndef FREE_COM_PTR
#define FREE_COM_PTR(x)					if(x){ x->Release(); x = NULL; }
#endif
#ifndef IS_PTR
#define IS_PTR(x)						( 0!=(x) )
#endif

#ifndef CountArray
#define CountArray(x) (sizeof(x)/sizeof(*x))
#endif
#ifndef MAX
#define MAX max
#endif
#ifndef MIN
#define MIN min
#endif
#ifndef CLAMP
#define CLAMP(x,a,b) (MIN(b,MAX(a,x)))
#endif
#ifndef ASSERT
#define ASSERT(expr)  _ASSERTE(expr)
#endif

#ifdef _DEBUG
#ifndef TRACE
#ifdef USE_WTL
#define TRACE ATLTRACE
#else
#define TRACE __Trace
#endif
#endif
#define TRACEMSG __TraceMsg
#else
#ifndef TRACE
#define TRACE
#endif
#define TRACEMSG _T("")
#endif

#ifdef _DEBUG
#ifndef LOG
#define INITLOG __InitLog
#define LOG __Log
#endif
#else
#ifndef LOG
#define INITLOG __InitLog
#define LOG __Log
#endif
#endif

	/////////////////////////////////////////////////////////////////////////////////////
	//

	// 跟踪函数
	void __Trace(LPCTSTR pstrFormat, ...);
	LPCTSTR __TraceMsg(UINT uMsg);

	// 日志函数
	void __InitLog(LPCTSTR pstrFile);
	void __Log(LPCTSTR pstrFormat, ...);

	// 性能函数
	bool StartMilliSecond();
	int GetMilliSecond();
	int GetCurMilliSecond();

	/////////////////////////////////////////////////////////////////////////////////////
	//

	// 运行时函数
	HRESULT GetDllVersion(HINSTANCE hInstDLL, DLLVERSIONINFO* pDllVersionInfo);
	HRESULT GetDllVersion(LPCTSTR lpstrDllName, DLLVERSIONINFO* pDllVersionInfo);
	// Common Control Versions:
	//   Win95/WinNT 4.0    maj=4 min=00
	//   IE 3.x     maj=4 min=70
	//   IE 4.0     maj=4 min=71
	HRESULT GetCommCtrlVersion(LPDWORD pdwMajor, LPDWORD pdwMinor);
	// Shell Versions:
	//   Win95/WinNT 4.0                    maj=4 min=00
	//   IE 3.x, IE 4.0 without Web Integrated Desktop  maj=4 min=00
	//   IE 4.0 with Web Integrated Desktop         maj=4 min=71
	//   IE 4.01 with Web Integrated Desktop        maj=4 min=72
	HRESULT GetShellVersion(LPDWORD pdwMajor, LPDWORD pdwMinor);

	/////////////////////////////////////////////////////////////////////////////////////
	//
	bool IsCommCtrl6();
	bool IsVistaLower();
	bool IsVista();
	bool IsWin7();
	bool IsWin8();
	bool IsThemeAvailable();
	bool IsRibbonUIAvailable();
	bool IsAeroSupported();
	bool IsComposing();
	bool IsOpaqueBlend();

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class STRINGorID
	{
	public:
		STRINGorID(LPCTSTR lpString) : m_lpstr(lpString)
		{ }
		STRINGorID(UINT nID) : m_lpstr(MAKEINTRESOURCE(nID))
		{ }
		LPCTSTR m_lpstr;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CPoint : public tagPOINT
	{
	public:
		CPoint();
		CPoint(const POINT& src);
		CPoint(int x, int y);
		CPoint(LPARAM lParam);
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CSize : public tagSIZE
	{
	public:
		CSize();
		CSize(const SIZE& src);
		CSize(const RECT rc);
		CSize(int cx, int cy);
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CRect : public tagRECT
	{
	public:
		CRect();
		CRect(const RECT& src);
		CRect(int iLeft, int iTop, int iRight, int iBottom);

		int GetWidth() const;
		int GetHeight() const;
		void Empty();
		bool IsNull() const;
		void Join(const RECT& rc);
		void ResetOffset();
		void Normalize();
		void Offset(int cx, int cy);
		void Inflate(int cx, int cy);
		void Deflate(int cx, int cy);
		void Union(CRect& rc);
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CStdPtrArray
	{
	public:
		CStdPtrArray(int iPreallocSize = 0);
		CStdPtrArray(const CStdPtrArray& src);
		~CStdPtrArray();

		void Empty();
		void Resize(int iSize);
		bool IsEmpty() const;
		int Find(LPVOID iIndex) const;
		bool Add(LPVOID pData);
		bool SetAt(int iIndex, LPVOID pData);
		bool InsertAt(int iIndex, LPVOID pData);
		bool Remove(int iIndex);
		int GetSize() const;
		LPVOID* GetData();

		LPVOID GetAt(int iIndex) const;
		LPVOID operator[] (int nIndex) const;

	protected:
		LPVOID* m_ppVoid;
		int m_nCount;
		int m_nAllocated;
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CStdValArray
	{
	public:
		CStdValArray(int iElementSize, int iPreallocSize = 0);
		~CStdValArray();

		void Empty();
		bool IsEmpty() const;
		bool Add(LPCVOID pData);
		bool Remove(int iIndex);
		int GetSize() const;
		LPVOID GetData();

		LPVOID GetAt(int iIndex) const;
		LPVOID operator[] (int nIndex) const;

	protected:
		LPBYTE m_pVoid;
		int m_iElementSize;
		int m_nCount;
		int m_nAllocated;
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CStdString
	{
	public:
		enum { MAX_LOCAL_STRING_LEN = 63 };

		CStdString();
		CStdString(const TCHAR ch);
		CStdString(const CStdString& src);
		CStdString(LPCTSTR lpsz, int nLen = -1);
		~CStdString();

		void Empty();
		int GetLength() const;
		bool IsEmpty() const;
		TCHAR GetAt(int nIndex) const;
		void Append(LPCTSTR pstr);
		void Assign(LPCTSTR pstr, int nLength = -1);
		LPCTSTR GetData() const;

		void SetAt(int nIndex, TCHAR ch);
		operator LPCTSTR() const;

		TCHAR operator[] (int nIndex) const;
		const CStdString& operator=(const CStdString& src);
		const CStdString& operator=(const TCHAR ch);
		const CStdString& operator=(LPCTSTR pstr);
#ifdef _UNICODE
		const CStdString& CStdString::operator=(LPCSTR lpStr);
		const CStdString& CStdString::operator+=(LPCSTR lpStr);
#else
		const CStdString& CStdString::operator=(LPCWSTR lpwStr);
		const CStdString& CStdString::operator+=(LPCWSTR lpwStr);
#endif
		CStdString operator+(const CStdString& src) const;
		CStdString operator+(LPCTSTR pstr) const;
		const CStdString& operator+=(const CStdString& src);
		const CStdString& operator+=(LPCTSTR pstr);
		const CStdString& operator+=(const TCHAR ch);

		bool operator == (LPCTSTR str) const;
		bool operator != (LPCTSTR str) const;
		bool operator <= (LPCTSTR str) const;
		bool operator <  (LPCTSTR str) const;
		bool operator >= (LPCTSTR str) const;
		bool operator >  (LPCTSTR str) const;

		int Compare(LPCTSTR pstr) const;
		int CompareNoCase(LPCTSTR pstr) const;

		void MakeUpper();
		void MakeLower();

		CStdString Left(int nLength) const;
		CStdString Mid(int iPos, int nLength = -1) const;
		CStdString Right(int nLength) const;

		int Find(TCHAR ch, int iPos = 0) const;
		int Find(LPCTSTR pstr, int iPos = 0) const;
		int ReverseFind(TCHAR ch) const;
		int Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo);

		int __cdecl Format(LPCTSTR pstrFormat, ...);
		int __cdecl SmallFormat(LPCTSTR pstrFormat, ...);

	protected:
		LPTSTR m_pstr;
		TCHAR m_szBuffer[MAX_LOCAL_STRING_LEN + 1];
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	struct TITEM
	{
		CStdString Key;
		LPVOID Data;
		struct TITEM* pPrev;
		struct TITEM* pNext;
	};

	class DUISHARP_API CStdStringPtrMap
	{
	public:
		CStdStringPtrMap(int nSize = 83);
		~CStdStringPtrMap();

		void Resize(int nSize = 83);
		LPVOID Find(LPCTSTR key, bool optimize = true) const;
		bool Insert(LPCTSTR key, LPVOID pData);
		LPVOID Set(LPCTSTR key, LPVOID pData);
		bool Remove(LPCTSTR key);
		void RemoveAll();
		int GetSize() const;
		LPCTSTR GetAt(int iIndex) const;
		LPCTSTR operator[] (int nIndex) const;

	protected:
		TITEM** m_aT;
		int m_nBuckets;
		int m_nCount;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class CStdFile
	{
	public:
		CStdFile();
		CStdFile(PVOID lpBuffer, DWORD dwLength);
		~CStdFile();

	public:
		void SetData(PVOID lpBuffer, DWORD dwLength);
		BOOL ReadFile(LPVOID lpBuffer, DWORD nNumberOfBytesToRead, LPDWORD lpNumberOfBytesRead);
		BOOL WriteFile(LPCVOID lpBuffer, DWORD nNumberOfBytesToWrite, LPDWORD lpNumberOfBytesWritten);
		DWORD SetFilePointer(ULONG lDistanceToMove, PLONG lpDistanceToMoveHigh, DWORD dwMoveMethod);
		BOOL CloseHandle();

	private:
		LPBYTE m_pBuffer;
		DWORD m_dwBuffer;
		DWORD m_dwCurrentPos;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//
	typedef void (*PONTIMERFUNC)(int nID,LPARAM lParam);

	typedef struct _tagStdTimerInfo
	{
		int nID;
		PONTIMERFUNC pOnTimerFunc;
		LPARAM lParam;
		DWORD dwMS;
		DWORD dwTickCount;
		int cnRun;
		BOOL bDeleted;
	}STDTIMERINFO,*PSTDTIMERINFO;

	class CStdTimer
	{
	public:
		CStdTimer();
		virtual ~CStdTimer();

	public:
		BOOL CreateTimer();
		BOOL SetTimer(int nID, DWORD dwMS, PONTIMERFUNC pFunc, LPARAM lParam = NULL);
		BOOL DeleteTimer(int nID,LPARAM lParam);
		DWORD ThreadFunc();

	private:
		void DestroyTimer();

	private:
		CRITICAL_SECTION m_cs;
		HANDLE m_hEvent;
		HANDLE m_hThread;
		std::vector<PSTDTIMERINFO> m_listTimer;
		BOOL m_bTerminate;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CWindowWnd
	{
	public:
		CWindowWnd();

		HWND GetHWND() const;
		operator HWND() const;

		bool RegisterWindowClass();
		bool RegisterSuperclass();

		HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, const RECT rc, HMENU hMenu = NULL);
		HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, int x = CW_USEDEFAULT, int y = CW_USEDEFAULT, int cx = CW_USEDEFAULT, int cy = CW_USEDEFAULT, HMENU hMenu = NULL);
		HWND CreateDuiWindow(HWND hwndParent, LPCTSTR pstrWindowName,DWORD dwStyle =0, DWORD dwExStyle =0);
		HWND Subclass(HWND hWnd);
		void Unsubclass();
		void ShowWindow(bool bShow = true, bool bTakeFocus = true);
		UINT ShowModal();
		void Close(UINT nRet = IDOK);
		void CenterWindow();
		void SetIcon(UINT nRes);

		LRESULT SendMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
		LRESULT PostMessage(UINT uMsg, WPARAM wParam = 0, LPARAM lParam = 0L);
		void ResizeClient(int cx = -1, int cy = -1);

	protected:
		virtual LPCTSTR GetWindowClassName() const = 0;
		virtual LPCTSTR GetSuperClassName() const;
		virtual UINT GetClassStyle() const;
		virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		virtual void OnFinalMessage(HWND hWnd);

		static LRESULT CALLBACK __WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		static LRESULT CALLBACK __ControlProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

	protected:
		HWND m_hWnd;
		WNDPROC m_OldWndProc;
		bool m_bSubclassed;
	};


	class DUISHARP_API CFindWnd
	{
	public:
		CFindWnd(HWND hParent, LPCTSTR pstrClassName, BOOL bVisible = TRUE);

	private:
		static BOOL CALLBACK FindChildClassHwnd(HWND hParent, LPARAM lParam);

	public:
		HWND m_hWnd;
		BOOL m_bVisible;
		LPCTSTR m_pstrClassName;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CWaitCursor
	{
	public:
		CWaitCursor();
		~CWaitCursor();

	protected:
		HCURSOR m_hOrigCursor;
	};

} // namespace duisharp

#endif // __UIBASE_H__
