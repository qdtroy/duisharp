#ifndef __UIWINDOW_H__
#define __UIWINDOW_H__

namespace duisharp {

	/////////////////////////////////////////////////////////////////////////////
	// Message map

#define BEGIN_UIMSG_MAP(theClass) \
public: \
	virtual BOOL HandleWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult) \
	{ \
	BOOL bHandled = TRUE; \

#define UIMESSAGE_HANDLER(msg, func) \
	if(uMsg == msg) \
	{ \
	bHandled = TRUE; \
	lResult = func(uMsg, wParam, lParam, bHandled); \
	if(bHandled) return TRUE; \
}

#define UIMESSAGE_RANGE_HANDLER(msgFirst, msgLast, func) \
	if(uMsg >= msgFirst && uMsg <= msgLast) \
	{ \
	bHandled = TRUE; \
	lResult = func(uMsg, wParam, lParam, bHandled); \
	if(bHandled) return TRUE; \
}

#define UICOMMAND_HANDLER(id, code, func) \
	if(uMsg == WM_COMMAND && id == LOWORD(wParam) && code == HIWORD(wParam)) \
	{ \
	bHandled = TRUE; \
	lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
	if(bHandled) return TRUE; \
}

#define UICOMMAND_ID_HANDLER(id, func) \
	if(uMsg == WM_COMMAND && id == LOWORD(wParam)) \
	{ \
	bHandled = TRUE; \
	lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
	if(bHandled) return TRUE; \
}

#define UICOMMAND_CODE_HANDLER(code, func) \
	if(uMsg == WM_COMMAND && code == HIWORD(wParam)) \
	{ \
	bHandled = TRUE; \
	lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
	if(bHandled) return TRUE; \
}

#define UICOMMAND_RANGE_HANDLER(idFirst, idLast, func) \
	if(uMsg == WM_COMMAND && LOWORD(wParam) >= idFirst  && LOWORD(wParam) <= idLast) \
	{ \
	bHandled = TRUE; \
	lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
	if(bHandled) return TRUE; \
}

#define UICOMMAND_RANGE_CODE_HANDLER(idFirst, idLast, code, func) \
	if(uMsg == WM_COMMAND && code == HIWORD(wParam) && LOWORD(wParam) >= idFirst  && LOWORD(wParam) <= idLast) \
	{ \
	bHandled = TRUE; \
	lResult = func(HIWORD(wParam), LOWORD(wParam), (HWND)lParam, bHandled); \
	if(bHandled) return TRUE; \
}

#define UINOTIFY_HANDLER(id, cd, func) \
	if(uMsg == WM_NOTIFY && id == ((LPNMHDR)lParam)->idFrom && cd == ((LPNMHDR)lParam)->code) \
	{ \
	bHandled = TRUE; \
	lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
	if(bHandled) return TRUE; \
}

#define UINOTIFY_ID_HANDLER(id, func) \
	if(uMsg == WM_NOTIFY && id == ((LPNMHDR)lParam)->idFrom) \
	{ \
	bHandled = TRUE; \
	lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
	if(bHandled) return TRUE; \
}

#define UINOTIFY_CODE_HANDLER(cd, func) \
	if(uMsg == WM_NOTIFY && cd == ((LPNMHDR)lParam)->code) \
	{ \
	bHandled = TRUE; \
	lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
	if(bHandled) return TRUE; \
}

#define UINOTIFY_RANGE_HANDLER(idFirst, idLast, func) \
	if(uMsg == WM_NOTIFY && ((LPNMHDR)lParam)->idFrom >= idFirst && ((LPNMHDR)lParam)->idFrom <= idLast) \
	{ \
	bHandled = TRUE; \
	lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
	if(bHandled) return TRUE; \
}

#define UINOTIFY_RANGE_CODE_HANDLER(idFirst, idLast, cd, func) \
	if(uMsg == WM_NOTIFY && cd == ((LPNMHDR)lParam)->code && ((LPNMHDR)lParam)->idFrom >= idFirst && ((LPNMHDR)lParam)->idFrom <= idLast) \
	{ \
	bHandled = TRUE; \
	lResult = func((int)wParam, (LPNMHDR)lParam, bHandled); \
	if(bHandled) return TRUE; \
}

#define CHAIN_UIMSG_MAP(theChainClass) \
	{ \
	if(theChainClass::HandleWindowMessage(hWnd, uMsg, wParam, lParam, lResult)) \
	return TRUE; \
}

#define END_UIMSG_MAP() \
	return FALSE; \
}

	class DUISHARP_API CUIWindow 
		: public CWindowWnd
		, public IUIMessageFilter
		, public IUINotify
		, public IUIBuilderCallback
	{
	public:
		CUIWindow();
		~CUIWindow();

	public:
		BEGIN_UIMSG_MAP(CUIWindow)
			UIMESSAGE_HANDLER(WM_CREATE, OnCreate)
			UIMESSAGE_HANDLER(WM_DESTROY, OnDestroy)
			UIMESSAGE_HANDLER(WM_SIZE, OnSize)
			UIMESSAGE_HANDLER(WM_MOVE, OnMove)
			UIMESSAGE_HANDLER(WM_NCACTIVATE, OnNcActivate)
			UIMESSAGE_HANDLER(WM_NCCALCSIZE, OnNcCalcSize)
			UIMESSAGE_HANDLER(WM_NCHITTEST, OnNcHitTest)
			UIMESSAGE_HANDLER(WM_DWMCOMPOSITIONCHANGED, OnDwmCompositionChanged)
		END_UIMSG_MAP()

	public:
		virtual LPCTSTR GetResFile();
		virtual LPCTSTR GetResType();
		virtual LPCTSTR GetResName();
		virtual bool IsLayerdWindow();

		virtual CUIControl* CreateControl(LPCTSTR pstrClass);
		virtual bool HitControl(CUIControl* pControl);

		// 回调函数
		virtual void OnInit();
		virtual void ChangeTheme();
		virtual void OnSized(UINT uCmd);
		virtual LRESULT HitTestNCA(HWND hWnd, WPARAM wParam, LPARAM lParam);
		
	public:
		virtual BOOL PreTranslateMessage(MSG* pMsg);
		virtual void OnFinalMessage(HWND hWnd);

	public:
		void Notify(TUINotify& msg);

	public:
		LRESULT OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnMove(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		LRESULT OnDwmCompositionChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

	public:
		// 辅助函数
		void SetLayeredControl(CUIControl* pControl);
		// 设置窗口RGN
		void SetRgn();
		// 设置分层窗口位置
		void SetLayeredPos(RECT rcWnd);
		// 获取分层窗口句柄
		HWND GetLayeredWnd();

	private:
		LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
		
	public:
		CUIManager m_ui;
		
	protected:
		// 窗口缩放状态
		UINT m_uSizeStatus;
		// 窗口的边距
		HWND m_hParent;
		CUIControl* m_pLayeredControl;
		static std::vector<CUIWindow*> s_vLayerdWindows;
	};


} // namespace duisharp

#endif // __UIWINDOW_H__