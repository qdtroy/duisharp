#include "stdafx.h"
#include "resource.h"
#include "..\UIBase\ControlEx.h"

#include "MessageBox.h"

class CMainFrame : public CUIWindow
{
public:
	CMainFrame() 
	{
		m_pCloseBtn = NULL;
		m_pMaxBtn = NULL;
		m_pMinBtn = NULL;
		m_pRestoreBtn = NULL;
	}

public:
	BEGIN_UIMSG_MAP(CMainFrame)
		UIMESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
		CHAIN_UIMSG_MAP(CUIWindow)
	END_UIMSG_MAP()

public:
	LPCTSTR GetWindowClassName() const 
	{
		return _T("UIMainFrame"); 
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
		return _T("IDX_MAINDLG"); 
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

	bool HitControl(CUIControl* pControl)
	{
		return ::HitControlEx(pControl);
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
		if( msg.sType == _T("lclick") ) {
			if( msg.pSender == m_pCloseBtn ) {
				//CMessageBox* pFrame = new CMessageBox();
				//pFrame->Create(m_hWnd, _T("QQ软件管理"), WS_POPUPWINDOW, 0L, 0, 0, 800, 572);
				//pFrame->CenterWindow();
				//pFrame->ShowModal();
				PostQuitMessage(0);
				return; 
			}
			else if( msg.pSender == m_pMinBtn ) { 
				SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return; }
			else if( msg.pSender == m_pMaxBtn ) { 
				SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return; }
			else if( msg.pSender == m_pRestoreBtn ) { 
				SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return; }
		}
		else if(msg.sType == _T("selectchanged"))
		{
			CUITabLayout* pBody = static_cast<CUITabLayout*>(m_ui.FindControl(_T("body")));

			CStdString name = msg.pSender->GetName();
			if(name == _T("tabbar_soft"))
			{
				pBody->SelectItem(0);
			}
			else if(name == _T("tabbar_upgrade"))
			{
				pBody->SelectItem(1);
			}
			else if(name == _T("tabbar_uninstall"))
			{
				pBody->SelectItem(2);
			}
		}
		else if(msg.sType==_T("itemselect"))
		{
			CUITabLayout* pControl = static_cast<CUITabLayout*>(m_ui.FindControl(_T("body_soft_list")));
			CUIList* pList = static_cast<CUIList*>(msg.pSender);
			if(pList->GetName().CompareNoCase(_T("body_soft_catalog")) == 0)
			{
				int nIndex = (int)msg.wParam;
				CUIControl *pItem = pList->GetItemAt(nIndex);
				if(pItem != NULL)
				{
					CStdString name = pItem->GetName();
					if(name==_T("hotsoft"))
						pControl->SelectItem(0);
					else if(name==_T("ossoft"))
						pControl->SelectItem(1);
					else if(name==_T("qqsoft"))
						pControl->SelectItem(2);
				}
			}
		}
	}

public:
	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		CUIWindow::OnDestroy(uMsg, wParam, lParam, bHandled);

		::PostQuitMessage(0L);

		return 0;
	}

	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		// 有时会在收到WM_NCDESTROY后收到wParam为SC_CLOSE的WM_SYSCOMMAND
		if( wParam == SC_CLOSE ) {
			::PostQuitMessage(0L);
			bHandled = TRUE;
			return 0;
		}
		BOOL bZoomed = ::IsZoomed(*this);
		LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
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
};