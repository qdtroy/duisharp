#pragma once

#include "stdafx.h"
#include "resource.h"
#include "..\UIBase\ControlEx.h"
#include "flash10a.tlh"

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
		UIMESSAGE_HANDLER(UIWM_MENU, OnMenuCmd)
		CHAIN_UIMSG_MAP(CUIWindow)
	END_UIMSG_MAP()

	BEGIN_UINOTIFY_MAP(CMainFrame)
		UINM_WINDOWINIT(_T("root"), OnWindowInit)
		UINM_LCLICK(_T("menubtn"), OnSysBtnLClick)
		UINM_LCLICK(_T("minbtn"), OnSysBtnLClick)
		UINM_LCLICK(_T("maxbtn"), OnSysBtnLClick)
		UINM_LCLICK(_T("restorebtn"), OnSysBtnLClick)
		UINM_LCLICK(_T("closebtn"), OnSysBtnLClick)
		UINM_SELECTCHANGED(_T("qqtab"), OnSelectChanged)
		UINM_ITEMCLICK(_T("listitem"), OnItemClick)
		UINM_ITEMACTIVE(_T("listitem"), OnItemActive)
		UINM_MOUSEENTER(_T("listitem"), OnMouseEnter)
		UINM_SHOWACTIVEX(_T("flash"), OnShowFlash)

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

	void OnThemeChanged()
	{
		if(m_ui.IsAero())
		{
			m_ui.GetRoot()->SetBkColor(0);
		}
		else
		{
			m_ui.GetRoot()->SetBkColor(0xFF76A8D0);
		}
	}

public:
	void OnWindowInit(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
	}

	void OnSysBtnLClick(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		CStdString sName = pControl->GetName();

		if( pControl == m_pCloseBtn ) {
			PostQuitMessage(0);
			return; 
		}
		else if( pControl == m_pMinBtn ) {
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, 0); return; 
		}
		else if( pControl == m_pMaxBtn ) {
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, 0); return; }
		else if( pControl == m_pRestoreBtn ) {
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, 0); return; }
		else if( sName.CompareNoCase(_T("menubtn")) == 0 ) {
			CUIMenuWnd* pMenu = new CUIMenuWnd(m_hWnd);
			POINT ptMenu = {0};
			::GetCursorPos(&ptMenu);
			pMenu->CreateMenu(NULL, _T("IDX_MENU"), NULL, ptMenu);
		}
	}

	void OnSelectChanged(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		CStdString sUserData = pControl->GetUserData();
		UIFINDCONTROL(CUITabLayout, pMainTab, _T("main_tab"));
		if(pMainTab != NULL)
		{
			int nCurSel = pMainTab->GetCurSel();

			UIFINDCONTROL(CUIList, pList, sUserData);
			if(pList != NULL)
			{
				int nIndex = pMainTab->GetItemIndex(pList);
				pMainTab->SelectItem(nIndex);
				srand(GetTickCount());
				int aEffects[] = {
					Effect_LR_2,
					Effect_RL_2,
					Effect_TB_2,
					Effect_BT_2,

					Effect_ExpandCenter,
					Effect_VExpandCenter,
					Effect_HExpandCenter
				};

				int nEffect = aEffects[rand() % (sizeof(aEffects) / sizeof(int))];

				if(nIndex > nCurSel)
					pList->SetEffect(nEffect);
				else
					pList->SetEffect(nEffect);
				pList->StartEffect(40, 1, false);
			}
		}
	}

	void OnItemClick(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		if( _tcsicmp(pControl->GetName(), _T("listitem")) == 0 ) {
			CUIQQList* pGameList = static_cast<CUIQQList*>(pControl->GetParent());
			CUIQQList::Node* node = (CUIQQList::Node*)pControl->GetTag();
			if(node) pGameList->ExpandNode(node, !node->data()._expand);
		}
	}

	void OnItemActive(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		if( _tcsicmp(pControl->GetName(), _T("listitem")) == 0 ) {
			CUIQQList* pGameList = static_cast<CUIQQList*>(pControl->GetParent());
			CUIQQList::Node* node = (CUIQQList::Node*)pControl->GetTag();       
			if(node && !node->has_children())
			{
			}
		}
	}

	void OnMouseEnter(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
	}

	void OnShowFlash(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		// 初始化Flash数据
		IShockwaveFlash* pFlash = NULL;
		CUIActiveX* pActiveX = static_cast<CUIActiveX*>(m_ui.FindControl(_T("flash")));
		pActiveX->GetControl(IID_IUnknown, (void**)&pFlash);
		if( pFlash != NULL ) {
			CStdString sPath = _App->GetInstancePath();
			sPath.Format(_T("%sskin\\duires\\waterdrop.swf"), sPath.GetData());
			pFlash->put_WMode(_bstr_t(_T("Transparent")));
			pFlash->put_Movie(_bstr_t(sPath.GetData()));
			pFlash->DisableLocalSecurity();
			pFlash->put_AllowScriptAccess(L"always");
			pFlash->Release();
		}
	}

public:
	void OnInit()
	{
		SetIcon(IDR_MAINFRAME);
		LONG styleValue = ::GetWindowLong(*this, GWL_STYLE);
		styleValue &= ~WS_CAPTION;
		::SetWindowLong(*this, GWL_STYLE, styleValue | WS_CLIPSIBLINGS | WS_CLIPCHILDREN);
		
		m_pCloseBtn = static_cast<CUIButton*>(m_ui.FindControl(_T("closebtn")));
		m_pMaxBtn = static_cast<CUIButton*>(m_ui.FindControl(_T("maxbtn")));
		m_pRestoreBtn = static_cast<CUIButton*>(m_ui.FindControl(_T("restorebtn")));
		m_pMinBtn = static_cast<CUIButton*>(m_ui.FindControl(_T("minbtn")));

		// 初始化QQList列表数据
		CStdString sList = _T("group_list");
		CUIQQList::Node* pCategoryNode1 = AddFirstNode(sList, _T("我的QQ群"), 1);
		CUIQQList::Node* pCategoryNode2 = AddFirstNode(sList, _T("专业群"), 1);
		CUIQQList::Node* pCategoryNode3 = AddFirstNode(sList, _T("朋友群"), 1);

		for( int i = 0; i < 6; ++i )
		{
			AddSecondNode(sList, _T("duisharp开发交流群(221499948)"), pCategoryNode1, i);
			AddSecondNode(sList, _T("duisharp群(221499948)"), pCategoryNode2, i);
			AddSecondNode(sList, _T("dui群(221499948)"), pCategoryNode3, i);
		}
		// 初始化RichEdit数据
		UIFINDCONTROL(CUIRichEdit, pRichEdit, _T("wordedit"));
		for(int i = 0; i < 6; i++)
		{
			CStdString sGif;
			sGif.Format(_T("images/face/%d.gif"), i % 3);
			pRichEdit->InsertGIF(sGif, i, 0);
		}
		// 多列ListView
		UIFINDCONTROL(CUIList, pList, _T("listview"));
		for(int i = 0; i < 12; i++)
		{
			CUIListItem* pElement = new CUIListItem;
			pElement->SetName(_T("listelement"));
			pElement->SetTag(i);
			pList->Add(pElement);

			pElement->SetItemText(0, _T("one"));
			pElement->SetItemText(1, _T("one"));
			pElement->SetItemText(2, _T("one"));
		}

		// 数据控件使用
		UIFINDCONTROL(CUIDataImage, pDataImage, _T("dataimage"));
		if(pDataImage)	
		{
			HBITMAP hBmp = _App->GetResMgr()->GetImage(_T("1.png"))->hBitmap;
			BITMAP bmp;
			::GetObjectA(hBmp, sizeof(bmp), (LPVOID)&bmp);
			LPBYTE pData = (LPBYTE)bmp.bmBits;
			int nWidth = bmp.bmWidth;
			int nHeight = bmp.bmHeight;
			pDataImage->SetImageData_RGB(pData, bmp.bmWidthBytes * nHeight, nWidth, nHeight);
		}
	}

	CUIQQList::Node* AddFirstNode(CStdString sList, CStdString sText, int nID)
	{
		CUIQQList* pList = static_cast<CUIQQList*>(m_ui.FindControl(sList));

		CStdString sFormat;
		sFormat.Format(_T("{x 4}{x 4}%s"), sText.GetData());
		CUIQQList::Node* pCategoryNode = pList->AddNode(sFormat, nID);

		return pCategoryNode;
	}

	CUIQQList::Node* AddSecondNode(CStdString sList, CStdString sText, CUIQQList::Node *pFirst, int nID)
	{
		CUIQQList* pGameList = static_cast<CUIQQList*>(m_ui.FindControl(sList));

		CStdString sIcon = _T("1.png");
		CStdString sFormat;
		sFormat.Format(_T("{x 4}{i %s 1 1}{x 4}%s"), sIcon.GetData(), sText.GetData());

		CUIQQList::Node* pGameNode = pGameList->AddNode(sFormat, nID, pFirst);

		return pGameNode;
	}


	LRESULT OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;

		CUIWindow::OnDestroy(uMsg, wParam, lParam, bHandled);

		::PostQuitMessage(0L);

		return 0;
	}

	LRESULT OnMenuCmd(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
	{
		bHandled = FALSE;
		int nMenu = (int)wParam;
		if(nMenu != 0)
		{
			MessageBox(NULL, _T("MenuCMd"), _T("UIMenu"), 0);
		}
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
};