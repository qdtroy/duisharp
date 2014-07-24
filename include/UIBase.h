#ifndef __UIBASE_H__
#define __UIBASE_H__

namespace duisharp {

	/////////////////////////////////////////////////////////////////////////////////////
	// define useful macros from windowsx.h
#ifndef GET_X_LPARAM
#define GET_X_LPARAM(lParam)	((int)(short)LOWORD(lParam))
#endif
#ifndef GET_Y_LPARAM
#define GET_Y_LPARAM(lParam)	((int)(short)HIWORD(lParam))
#endif
	
// 怎么都没找到min，max的头文件-_-
#ifndef min
#define min(a,b) (((a) < (b)) ? (a) : (b))
#endif
#ifndef max
#define max(a,b) (((a) > (b)) ? (a) : (b))
#endif

#define lengthof(x) (sizeof(x)/sizeof(*x))
#define MAX max
#define MIN min
#define CLAMP(x,a,b) (MIN(b,MAX(a,x)))

#ifndef ASSERT
#define ASSERT(expr)  _ASSERTE(expr)
#endif

#ifdef _DEBUG
#ifndef TRACE
#define TRACE Trace
#endif
#else
#ifndef TRACE
#define TRACE
#endif
#endif

	/////////////////////////////////////////////////////////////////////////////////////
	//
	void Trace(LPCTSTR pstrFormat, ...);

	/////////////////////////////////////////////////////////////////////////////////////
	//
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
	class DUISHARP_API CStdPoint : public tagPOINT
	{
	public:
		CStdPoint();
		CStdPoint(const POINT& src);
		CStdPoint(int x, int y);
		CStdPoint(LPARAM lParam);
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//
	class DUISHARP_API CStdSize : public tagSIZE
	{
	public:
		CStdSize();
		CStdSize(const SIZE& src);
		CStdSize(const RECT rc);
		CStdSize(int cx, int cy);
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//
	class DUISHARP_API CStdRect : public tagRECT
	{
	public:
		CStdRect();
		CStdRect(const RECT& src);
		CStdRect(int iLeft, int iTop, int iRight, int iBottom);

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
		void Union(CStdRect& rc);
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//
	class DUISHARP_API CStdPtrArray
	{
	public:
		CStdPtrArray(int iPreallocSize = 0);
		CStdPtrArray(const CStdPtrArray& src);
		~CStdPtrArray();

		void RemoveAll();
		void Resize(int iSize);
		bool IsEmpty() const;
		int Find(LPVOID pData) const;
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

	template<typename T>
	class DUISHARP_API CStdPtrArrayImpl : public CStdPtrArray
	{
	public:
		CStdPtrArrayImpl(int iPreallocSize = 0) : CStdPtrArray(iPreallocSize){}
		CStdPtrArrayImpl(const CStdPtrArrayImpl& src) : CStdPtrArray(src){}

	public:
		int Find(T pData) const 
		{
			return CStdPtrArray::Find(pData);
		}

		bool Add(T pData)
		{
			return CStdPtrArray::Add(pData);
		}

		bool SetAt(int iIndex, T pData)
		{
			return CStdPtrArray::SetAt(iIndex,pData);
		}

		bool InsertAt(int iIndex, T pData)
		{
			return CStdPtrArray::InsertAt(iIndex,pData);
		}

		bool Remove(int iIndex, bool bDel = false)
		{
			if( bDel ) {
				T pT = GetAt(iIndex);
				if( pT != NULL ) {
					delete pT;
					pT = NULL;
				}
			}
			return CStdPtrArray::Remove(iIndex);
		}

		void RemoveAll(bool bDel = false)
		{
			if( bDel ) {
				for( int i = 0; i < m_nCount; i++ ) {
					T pT = GetAt(i);
					if( pT != NULL ) {
						delete pT;
						pT = NULL;
					}
				}
			}
			return CStdPtrArray::RemoveAll();
		}

		T GetData()
		{
			return static_cast<T>(CStdPtrArray::GetData());
		}

		T GetAt(int iIndex) const
		{
			return static_cast<T>(CStdPtrArray::GetAt(iIndex));
		}

		T operator[] (int nIndex) const
		{
			return static_cast<T>(CStdPtrArray::operator[](nIndex));
		}
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

		void StringFormat();

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
	
	template<typename T>
	class DUISHARP_API CStdStringPtrMapImpl : public CStdStringPtrMap
	{
	public:
		CStdStringPtrMapImpl(int nSize = 83) : CStdStringPtrMap(nSize){}

	public:
		T GetPtr(int iIndex) const 
		{
			LPCTSTR nkey = GetAt(iIndex);
			if( !nkey ) return NULL;
			return Find(nkey);
		}

		T Find(LPCTSTR key, bool optimize = true) const
		{
			return static_cast<T>(CStdStringPtrMap::Find(key, optimize));
		}

		bool Insert(LPCTSTR key,T pData)
		{
			return CStdStringPtrMap::Insert(key, pData);
		}

		T Set(LPCTSTR key,T pData)
		{
			return static_cast<T>(CStdStringPtrMap::Set(key, pData));
		}
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
	class DUISHARP_API CStdWindow
	{
	public:
		CStdWindow();

	public:
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

} // namespace duisharp

#endif // __UIBASE_H__
