#include "stdafx.h"
#include "resource.h"
#include "..\UIBase\ControlEx.h"

class CSkinFrame : public CUIWindow
{
public:
	CSkinFrame(HWND hParent, CUIControl *pControl)
	{
		m_hParent = hParent;
		m_pControl = pControl;
		Create(NULL, _T("skinframe"), WS_POPUP | WS_VISIBLE, WS_EX_NOACTIVATE | WS_EX_TOOLWINDOW | WS_EX_TOPMOST);
	}

public:
	BEGIN_UIMSG_MAP(CSkinFrame)
		UIMESSAGE_HANDLER(WM_KILLFOCUS, OnKillFocus)
		CHAIN_UIMSG_MAP(CUIWindow)
	END_UIMSG_MAP()

	BEGIN_UINOTIFY_MAP(CSkinFrame)
		UINM_FILTER(UINM_LCLICK, OnLClick)	
	END_UINOTIFY_MAP()

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
		return ::CreateControlEx(pstrClass);
	}

	bool HitControl(CUIControl* pControl)
	{
		return ::HitControlEx(pControl);
	}
public:
	void OnInit() 
	{
		if(m_pControl == NULL) return;
		
		RECT rcConrol = m_pControl->GetPos();
		SIZE szWnd = m_ui.GetInitSize();
		POINT ptWnd = {0};
		ptWnd.x = rcConrol.right - szWnd.cx;
		ptWnd.y = rcConrol.bottom;
		::ClientToScreen(m_hParent, &ptWnd);
		
		SetWindowPos(m_hWnd, NULL, ptWnd.x, ptWnd.y, szWnd.cx, szWnd.cy, SWP_NOSIZE | SWP_NOACTIVATE);
	}

	void OnLClick(CStdString sName, CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		if(sName.CompareNoCase(_T("skin_image_btn")) == 0)
		{
			TUISkinInfo skin;
			skin.uType = 1;
			_tcscpy(skin.szBg, pControl->GetUserData());
			CSkinManager::GetSkinManager()->Broadcast(skin);
		}
		else if(sName.CompareNoCase(_T("skin_color_btn")) == 0)
		{
			TUISkinInfo skin;
			skin.uType = 0;
			skin.dwColor = pControl->GetBkColor();
			CSkinManager::GetSkinManager()->Broadcast(skin);
		}
		else if(sName.CompareNoCase(_T("skin_color")) == 0)
		{
			UIFINDCONTROL(CUITabLayout, pSkinTab, _T("skin_tab"));
			pSkinTab->SelectItem(1);
		}
		else if(sName.CompareNoCase(_T("skin_image")) == 0)
		{
			UIFINDCONTROL(CUITabLayout, pSkinTab, _T("skin_tab"));
			pSkinTab->SelectItem(0);
		}
	}

public:
	LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		Close(0);
		return 0;
	}

private:
	HWND m_hParent;
	CUIControl* m_pControl;
};