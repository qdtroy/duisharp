#pragma once

namespace duisharp {
	/////////////////////////////////////////////////////////////////////////////////////
	//

	typedef enum _enMenuAlignment
	{
		eMenuAlignment_Left = 1 << 1,
		eMenuAlignment_Top = 1 << 2,
		eMenuAlignment_Right = 1 << 3,
		eMenuAlignment_Bottom = 1 << 4,
	}MenuAlignment;

	typedef enum _enMenuCmd
	{
		eMenuCmd_RemoveSubMenu = 0,
		eMenuCmd_RemoveAllMenu,
		eMenuCmd_SelectMenu,
	}MenuCmd;

	typedef struct _tagTUIMenuParam
	{
		WPARAM wParam;	// 1-销毁所有菜单项，2-销毁子菜单项
		int nMenuCmd;		// 菜单命令:从1开始
		HWND hWnd;
	}TUIMenuParam;

	typedef class CObserverImpl<BOOL, TUIMenuParam> ContextMenuObserver;
	typedef class CReceiverImpl<BOOL, TUIMenuParam> ContextMenuReceiver;

	class DUISHARP_API CUIMenu : public CUIList
	{
	public:
		CUIMenu();
		~CUIMenu();

	public:
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

	public:
		virtual void DoEvent(TUIEvent& event);

		virtual bool Add(CUIControl* pControl);
		virtual bool AddAt(CUIControl* pControl, int iIndex);

		virtual int GetItemIndex(CUIControl* pControl) const;
		virtual bool SetItemIndex(CUIControl* pControl, int iIndex);
		virtual bool Remove(CUIControl* pControl);

		SIZE EstimateSize(SIZE szAvailable, bool bSized = true);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//
	class CUIMenuItem;
	class DUISHARP_API CUIMenuWnd : public CUIWindow, public ContextMenuReceiver
	{
	public:
		CUIMenuWnd(HWND hParent = NULL);

	public:
		void CreateMenu(CUIMenuItem* pOwner, STRINGorID xml, LPCTSTR pSkinType, POINT point);

	public:
		LPCTSTR GetWindowClassName() const;
		void OnFinalMessage(HWND hWnd);

	public:
		BOOL HandleWindowMessage(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lResult);
		BOOL Receive(TUIMenuParam param);

	public:
		HWND m_hParent;
		POINT m_BasedPoint;
		STRINGorID m_xml;
		CStdString m_sType;
		CUIMenuItem* m_pOwner;
		CUIMenu* m_pLayout;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//
	class DUISHARP_API CUIMenuItem : public CUIListItem
	{
		friend CUIMenuWnd;
	public:
		CUIMenuItem();
		~CUIMenuItem();

	public:
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

	public:
		CUIMenuWnd* GetMenuWnd();
		void CreateMenuWnd();

	public:
		void DoPaint(HDC hDC, const RECT& rcPaint, UINT uType = 0);
		void DrawItemText(HDC hDC, const RECT& rcItem);
		SIZE EstimateSize(SIZE szAvailable, bool bSized = true);
		bool Activate();
		void DoEvent(TUIEvent& event);

		void SetMenuCmd(int nCmd);
		int GetMenuCmd() const;

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
	protected:
		CUIMenuWnd* m_pWindow;
		int m_nMenuCmd;
	};
}