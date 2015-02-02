#include "stdafx.h"
#include "resource.h"
#include "..\UIBase\ControlEx.h"

class CMessageBox : public CUIWindow
{
public:
	CMessageBox() { };

public:
	BEGIN_UIMSG_MAP(CMessageBox)
		UIMESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
		CHAIN_UIMSG_MAP(CUIWindow)
	END_UIMSG_MAP()

public:
	LPCTSTR GetWindowClassName() const 
	{
		return _T("UIMessageBox"); 
	}

	UINT GetClassStyle() const 
	{ 
		return CS_DBLCLKS; 
	}

	void OnFinalMessage(HWND hWnd) 
	{ 
		CUIWindow::OnFinalMessage(hWnd); 
		delete this; 
	}

public:
	virtual LPCTSTR GetResFile() 
	{
		return _T("IDX_MESSAGEBOX"); 
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
		return ::CreateControlEx(pstrClass);
	}

public:
	void OnInit() {
		SetIcon(IDR_MAINFRAME);
		LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
		styleValue &= ~WS_CAPTION;
		::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

		m_pCloseBtn = static_cast<CUIButton*>(m_ui.FindControl(_T("closebtn")));
		m_pMaxBtn = static_cast<CUIButton*>(m_ui.FindControl(_T("maxbtn")));
		m_pRestoreBtn = static_cast<CUIButton*>(m_ui.FindControl(_T("restorebtn")));
		m_pMinBtn = static_cast<CUIButton*>(m_ui.FindControl(_T("minbtn")));
	}

	void Notify(TUINotify& msg)
	{
		if( msg.sType == _T("click") ) {
			if( msg.pSender == m_pCloseBtn ) {
				PostMessage(WM_CLOSE, 0, 0); return; }
			else if( msg.pSender == m_pMinBtn ) { 
				::ShowWindow(m_hWnd, SW_MINIMIZE); return; }
			else if( msg.pSender == m_pMaxBtn ) { 
				::ShowWindow(m_hWnd, SW_MAXIMIZE); return; }
			else if( msg.pSender == m_pRestoreBtn ) { 
				::ShowWindow(m_hWnd, SW_RESTORE); return; }
		}
	}

public:
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
		if( wParam == SC_CLOSE ) {
			bHandled = TRUE;
			return 0;
		}
		BOOL bZoomed = ::IsZoomed(*this);
		LRESULT lRes = CStdWindow::HandleMessage(uMsg, wParam, lParam);
		if( ::IsZoomed(*this) != bZoomed ) {
			if( !bZoomed ) {
				CUIControl* pControl = static_cast<CUIControl*>(m_ui.FindControl(_T("maxbtn")));
				if( pControl ) pControl->SetVisible(false);
				pControl = static_cast<CUIControl*>(m_ui.FindControl(_T("restorebtn")));
				if( pControl ) pControl->SetVisible(true);
			}
			else {
				CUIControl* pControl = static_cast<CUIControl*>(m_ui.FindControl(_T("maxbtn")));
				if( pControl ) pControl->SetVisible(true);
				pControl = static_cast<CUIControl*>(m_ui.FindControl(_T("restorebtn")));
				if( pControl ) pControl->SetVisible(false);
			}
		}
		return lRes;
	}

private:
	CUIButton* m_pCloseBtn;
	CUIButton* m_pMaxBtn;
	CUIButton* m_pRestoreBtn;
	CUIButton* m_pMinBtn;
	//...
};