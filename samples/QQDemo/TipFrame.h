#include "stdafx.h"
#include "resource.h"
#include "..\UIBase\ControlEx.h"

class CTipFrame : public CUIWindow
{
public:
	CTipFrame(HWND hParent, POINT ptPos)
	{
		RECT rcWnd = {0};
		GetWindowRect(hParent, &rcWnd);
		if(m_hTipWnd == NULL)
		{
			m_hTipWnd = Create(hParent, _T("tipframe"), WS_POPUP | WS_VISIBLE, WS_EX_TOOLWINDOW | WS_EX_NOACTIVATE);
		}
		::SetWindowPos(m_hTipWnd, NULL, rcWnd.left + ptPos.x, rcWnd.top + ptPos.y, 0, 0, SWP_NOSIZE | SWP_NOACTIVATE | SWP_SHOWWINDOW);
	}

	static void CloseWindow()
	{
		if(m_hTipWnd != NULL)
		{
			::PostMessage(m_hTipWnd, WM_CLOSE, NULL, NULL);
		}
	}
public:
	BEGIN_UIMSG_MAP(CTipFrame)
		UIMESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
		//UIMESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		CHAIN_UIMSG_MAP(CUIWindow)
	END_UIMSG_MAP()
	
	BEGIN_UINOTIFY_MAP(CMainFrame)
		UINM_WINDOWINIT(_T("root"), OnWindowInit)

	END_UINOTIFY_MAP()

public:
	LPCTSTR GetWindowClassName() const 
	{
		return _T("UITipFrame"); 
	}

	UINT GetClassStyle() const 
	{ 
		return CS_DBLCLKS; 
	}

	void OnFinalMessage(HWND hWnd) 
	{
		m_hTipWnd = NULL;
		CUIWindow::OnFinalMessage(hWnd); 
		delete this;
	}

public:
	virtual LPCTSTR GetResFile() 
	{
		return _T("IDX_TIPFRAME"); 
	}

	virtual LPCTSTR GetResType() 
	{ 
		return NULL;
	}

	virtual LPCTSTR GetResName() 
	{ 
		return NULL;
	}

	CUIControl* CreateControl(LPCTSTR pstrClass)
	{
		return CreateControlEx(pstrClass);
	}

	bool HitControl(CUIControl* pControl)
	{
		return ::HitControlEx(pControl);
	}

	void ChangeTheme()
	{
		if(m_ui.IsAero())
		{
			m_ui.GetRoot()->SetBkColor(0);
		}
		else
		{
			m_ui.GetRoot()->SetBkColor(0xFFFFFFFF);
		}
	}

public:
	void OnInit()
	{
		SetIcon(IDR_MAINFRAME);
		LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
		styleValue &= ~WS_CAPTION;
		::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		SetWindowPos(m_hWnd, NULL, 0, 0, m_ui.GetInitSize().cx, m_ui.GetInitSize().cy, SWP_NOMOVE | SWP_NOACTIVATE);
	}
	
public:
	void OnWindowInit(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		//REALCONTROL(CUIEXVerticalLayout, pRoot, pControl);
		//if(pRoot != NULL)
		//{
		//	pRoot->SetEffect(Effect_Expand);
		//	pRoot->StartEffect(15);
		//}
	}

public:
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		LRESULT lRes = CStdWindow::HandleMessage(uMsg, wParam, lParam);
		
		// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
		if( wParam == SC_CLOSE ) {
			bHandled = TRUE;
			return 0;
		}
		
		return lRes;
	}

	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		Close(0);
		return 0;
	}
private:
	static HWND m_hTipWnd;
};

HWND CTipFrame::m_hTipWnd = NULL;