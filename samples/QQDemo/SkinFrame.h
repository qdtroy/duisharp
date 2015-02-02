#include "stdafx.h"
#include "resource.h"
#include "..\UIBase\ControlEx.h"
#include "..\UIBase\SkinManager.h"

class CSkinFrame : public CUIWindow, public CSkinChangedReceiver
{
public:
	CSkinFrame()
	{
		if( m_hSkinWnd == NULL ) {
			Create(NULL, _T("skinframe"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0);
			m_hSkinWnd = m_hWnd;
		}
		else {
			::ShowWindow(m_hSkinWnd, SW_SHOWNOACTIVATE);
		}
	}

public:
	BEGIN_UIMSG_MAP(CSkinFrame)
		UIMESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
		CHAIN_UIMSG_MAP(CUIWindow)
	END_UIMSG_MAP()
	
	BEGIN_UINOTIFY_MAP(CMainFrame)
		UINM_WINDOWINIT(_T("root"), OnWindowInit)
		UINM_LCLICK(_T("closebtn"), OnSysBtnLClick)
		UINM_SELECTCHANGED(_T("skintab"), OnSelectChanged)
		UINM_LCLICK(_T("skin_image_btn"), OnSkinImageLClick)
		UINM_LCLICK(_T("skin_color_btn"), OnSkinColorLClick)
	END_UINOTIFY_MAP()

public:
	LPCTSTR GetWindowClassName() const 
	{
		return _T("UISkinFrame"); 
	}

	UINT GetClassStyle() const 
	{ 
		return CS_DBLCLKS; 
	}

	void OnFinalMessage(HWND hWnd) 
	{
		CSkinManager::GetSkinManager()->RemoveReceiver(this);
		m_hSkinWnd = NULL;
		CUIWindow::OnFinalMessage(hWnd); 
		delete this;
	}

public:
	virtual LPCTSTR GetResFile() 
	{
		return _T("IDX_SKINFRAME"); 
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

	bool Receive(TUISkinInfo skin)
	{
		if(skin.uType == 0)
		{
			m_ui.GetRoot()->SetBkImage(_T(""));
			m_ui.GetRoot()->SetBkColor(skin.dwColor);
		}
		else
		{
			m_ui.GetRoot()->SetBkColor(0);
			CStdString sImage = skin.szBg;
			m_ui.GetRoot()->SetBkImage(sImage + _T(" fade='128'"));
		}

		return true;
	}

public:
	void OnInit()
	{
		CSkinManager::GetSkinManager()->AddReceiver(this);
		SetIcon(IDR_MAINFRAME);
		LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
		styleValue &= ~WS_CAPTION;
		::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);

		SetWindowText(m_hWnd, _T("皮肤管理"));

		m_pCloseBtn = static_cast<CUIButton*>(m_ui.FindControl(_T("closebtn")));
		m_pMaxBtn = static_cast<CUIButton*>(m_ui.FindControl(_T("maxbtn")));
		m_pRestoreBtn = static_cast<CUIButton*>(m_ui.FindControl(_T("restorebtn")));
		m_pMinBtn = static_cast<CUIButton*>(m_ui.FindControl(_T("minbtn")));

		CenterWindow();
	}
	
public:
	void OnWindowInit(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		REALCONTROL(CUIVerticalLayout, pRoot, pControl);
		//if(pRoot != NULL)
		//{
		//	pRoot->SetEffect(Effect_RBExpand);
		//	pRoot->StartEffect(15);
		//}
	}

	void OnSysBtnLClick(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		if( pControl == m_pCloseBtn ) {
			PostMessage(WM_CLOSE, 0, 0); return; }
		else if( pControl == m_pMinBtn ) {
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return; }
		else if( pControl == m_pMaxBtn ) {
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return; }
		else if( pControl == m_pRestoreBtn ) {
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return; }
	}
	
	void OnSelectChanged(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		CStdString sUserData = pControl->GetUserData();
		UIFINDCONTROL(CUITabLayout, pMainTab, _T("body.tab"));
		if(pMainTab != NULL)
		{
			int nCurSel = pMainTab->GetCurSel();

			UIFINDCONTROL(CUIControl, pTab, sUserData);
			if(pTab != NULL)
			{
				int nIndex = pMainTab->GetItemIndex(pTab);
				pMainTab->SelectItem(nIndex);
				if(nIndex > nCurSel)
					pTab->SetEffect(Effect_RL_2);
				else
					pTab->SetEffect(Effect_LR_2);
				pTab->StartEffect(40);
			}
		}
	}

	void OnSkinImageLClick(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		TUISkinInfo skin;
		skin.uType = 1;
		_tcscpy(skin.szBg, pControl->GetUserData());
		CSkinManager::GetSkinManager()->Broadcast(skin);
	}

	void OnSkinColorLClick(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		TUISkinInfo skin;
		skin.uType = 0;
		skin.dwColor = pControl->GetBkColor();
		CSkinManager::GetSkinManager()->Broadcast(skin);
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

	static HWND m_hSkinWnd;
};

HWND CSkinFrame::m_hSkinWnd = NULL;