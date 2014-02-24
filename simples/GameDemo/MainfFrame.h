#include "stdafx.h"
#include "resource.h"
#include "..\UIBase\ControlEx.h"
#include "..\UIBase\SkinManager.h"

#include "SkinFrame.h"

class CQQFrame : public CUIWindow, public CSkinChangedReceiver
{
public:
	CQQFrame() 
	{
		m_pCloseBtn = NULL;
		m_pMaxBtn = NULL;
		m_pMinBtn = NULL;
		m_pRestoreBtn = NULL;
	}

public:
	BEGIN_UIMSG_MAP(CQQFrame)
		UIMESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
		CHAIN_UIMSG_MAP(CUIWindow)
	END_UIMSG_MAP()

	BEGIN_UINOTIFY_MAP(CQQFrame)
		UINM_WINDOWINIT(_T("root"), OnWindowInit)
		UINM_LCLICK(_T("skinbtn"), OnSysBtnLClick)
		UINM_LCLICK(_T("minbtn"), OnSysBtnLClick)
		UINM_LCLICK(_T("maxbtn"), OnSysBtnLClick)
		UINM_LCLICK(_T("restorebtn"), OnSysBtnLClick)
		UINM_LCLICK(_T("closebtn"), OnSysBtnLClick)
		UINM_SELECTCHANGED(_T("maintab"), OnMainTabSelectChanged)
		UINM_SELECTCHANGED(_T("gametab"), OnGameTabSelectChanged)
	END_UINOTIFY_MAP()

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
		return _T("IDX_MAINFRAME"); 
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

	bool Receive(TUISkinInfo skin)
	{
		if(skin.uType == 0)
		{
			m_ui.GetRoot()->SetBkImage(_T(""));
			m_ui.GetRoot()->SetBkColor(skin.dwColor);
		}
		else
		{
			CStdString sImage;
			sImage.Format(_T("res='%s' corner='1000,750,2,2'"), skin.szBg);
			m_ui.GetRoot()->SetBkImage(sImage);
		}

		return true;
	}
public:
	void OnWindowInit(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		//REALCONTROL(CUIEXVerticalLayout, pRoot, pControl);
		//if(pRoot != NULL)
		//{
		//	pRoot->SetEffect(Effect_RBExpand);
		//	pRoot->StartEffect(30);
		//}
	}

	void OnSysBtnLClick(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		if(pControl == m_pSkinBtn){
			CSkinFrame *pFrame = new CSkinFrame(m_hWnd, pControl);
		}
		else if( pControl == m_pCloseBtn ) {
			PostQuitMessage(0);
			return; 
		}
		else if( pControl == m_pMinBtn ) {
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return; }
		else if( pControl == m_pMaxBtn ) {
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return; }
		else if( pControl == m_pRestoreBtn ) {
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return; }
	}

	void OnMainTabSelectChanged(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		CStdString sUserData = pControl->GetUserData();
		UIFINDCONTROL(CUITabLayout, pMainTabLayout, _T("main_tablayout"));
		if(pMainTabLayout != NULL)
		{
			UIFINDCONTROL(CUIControl, pTab, sUserData);
			pMainTabLayout->SelectItem(pTab);
		}
	}

	void OnGameTabSelectChanged(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		CStdString sUserData = pControl->GetUserData();
		UIFINDCONTROL(CUITabLayout, pMainTabLayout, _T("game_tablayout"));
		if(pMainTabLayout != NULL)
		{
			UIFINDCONTROL(CUITileLayout, pTab, sUserData);
			pMainTabLayout->SelectItem(pTab);
			pTab->SetEffect(Effect_LR_2);
			pTab->StartEffect(100);
		}
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
		m_pSkinBtn = static_cast<CUIButton*>(m_ui.FindControl(_T("skinbtn")));

		CSkinManager::GetSkinManager()->AddReceiver(this);
	}

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
	CUIButton* m_pSkinBtn;
};