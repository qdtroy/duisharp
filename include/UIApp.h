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
		std::vector<IUIMessageFilter*> m_aMsgFilter;
		std::vector<IUIIdleHandler*> m_aIdleHandler;
		MSG m_msg;	
	};

	class DUISHARP_API CUIApp
	{
	public:
		CUIApp();
		~CUIApp();

	public:
		virtual BOOL Init(HINSTANCE hInstance);
		virtual int Run();
		virtual void Term();
	
	public:
		virtual HINSTANCE GetInstance();
		virtual HINSTANCE GetResInstance();
		virtual CStdString GetInstancePath();
		virtual CUIResManager* GetResMgr();
		virtual CUIMessageLoop* GetMessageLoop();
		
	public:
		virtual int LoadSkin(TUISkin skin);
		std::vector<LPCREATECONTROL> GetPlusgins();
		virtual int LoadPlugin(LPCTSTR pstrModule);
		
		virtual void SetHSL(short H, short S, short L);
		virtual void GetHSL(short* H, short* S, short* L);

		virtual void AddManager(CUIManager* pManager);
		virtual void RemoveManager(CUIManager* pManager);

		virtual void AddMessageFilter(IUIMessageFilter* pFilter);
		virtual void RemoveMessageFilter(IUIMessageFilter* pFilter);
	protected:
		HINSTANCE m_hInstance;
		HINSTANCE m_hResInstance;
		CUIResManager m_ResMgr;
		CUIMessageLoop m_MessageLoop;
		std::vector<CUIManager*> m_aManagers;
		std::vector<LPCREATECONTROL> m_aPlugins;

		short m_H;
		short m_S;
		short m_L;
	};

	extern "C" { extern DUISHARP_API CUIApp* _App; }

}//

#endif