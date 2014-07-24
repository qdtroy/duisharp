#ifndef __UIAPP_H__
#define __UIAPP_H__

namespace duisharp {

	class DUISHARP_API IUIMessageFilter
	{
	public:
		virtual BOOL PreTranslateMessage(MSG* pMsg) = 0;
	};

	class DUISHARP_API IUIIdleHandler
	{
	public:
		virtual BOOL OnIdle() = 0;
	};

	class DUISHARP_API CUIMessageLoop
	{
	public:
		BOOL AddMessageFilter(IUIMessageFilter* pMessageFilter);
		VOID RemoveMessageFilter(IUIMessageFilter* pMessageFilter);

		BOOL AddIdleHandler(IUIIdleHandler* pIdleHandler);
		VOID RemoveIdleHandler(IUIIdleHandler* pIdleHandler);

		int Run();

		static BOOL IsIdleMessage(MSG* pMsg);

	protected:
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		virtual BOOL OnIdle(int);

	protected:
		CStdPtrArrayImpl<IUIMessageFilter*> m_aMsgFilter;
		CStdPtrArrayImpl<IUIIdleHandler*> m_aIdleHandler;
		MSG m_msg;	
	};

	class DUISHARP_API CUIApp
	{
	public:
		CUIApp();
		~CUIApp();

	public:
		virtual BOOL Init(HINSTANCE hInstance);
		virtual int Run() = 0;
		virtual void Term();
	
	public:
		virtual HINSTANCE GetInstance();
		virtual HINSTANCE GetResInstance();
		virtual CStdString GetInstancePath();
		virtual CUIResManager* GetResMgr();
		
	public:
		virtual int LoadSkin(TUISkin skin);

		virtual void SetHSL(short H, short S, short L);
		virtual void GetHSL(short* H, short* S, short* L);

		virtual void AddManager(CUIManager* pManager);
		virtual void RemoveManager(CUIManager* pManager);

		virtual void AddMessageFilter(IUIMessageFilter* pFilter);
		virtual void RemoveMessageFilter(IUIMessageFilter* pFilter);

		BOOL AddMessageLoop(CUIMessageLoop* pMsgLoop);
		BOOL RemoveMessageLoop();
		CUIMessageLoop* GetMessageLoop(DWORD dwThreadID = ::GetCurrentThreadId()) const;

	protected:
		HWND m_hMainWnd;
		HINSTANCE m_hInstance;
		HINSTANCE m_hResInstance;
		CUIResManager m_ResMgr;
		DWORD m_dwMainThreadID;
		CStdStringPtrMapImpl<CUIMessageLoop*>* m_pMsgLoopMap;
		CStdPtrArrayImpl<CUIManager*> m_aManagers;

		short m_H;
		short m_S;
		short m_L;
		
		static CRITICAL_SECTION m_Critical;
	};

	extern "C" { extern DUISHARP_API CUIApp* _App; }
}//

#endif