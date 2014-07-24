#include "stdafx.h"
#include "resource.h"
#include "..\UIBase\ControlEx.h"
#include "..\UIBase\SkinManager.h"

class CChatFrame : public CUIWindow, public CSkinChangedReceiver
{
public:
	CChatFrame()
	{
		Create(NULL, _T("chatframe"), WS_OVERLAPPEDWINDOW | WS_VISIBLE, 0);
	} 

public:
	BEGIN_UIMSG_MAP(CChatFrame)
		UIMESSAGE_HANDLER(WM_SYSCOMMAND, OnSysCommand)
		CHAIN_UIMSG_MAP(CUIWindow)
	END_UIMSG_MAP()
	
	BEGIN_UINOTIFY_MAP(CMainFrame)
		UINM_WINDOWINIT(_T("root"), OnWindowInit)
		UINM_LCLICK(_T("minbtn"), OnSysBtnLClick)
		UINM_LCLICK(_T("maxbtn"), OnSysBtnLClick)
		UINM_LCLICK(_T("restorebtn"), OnSysBtnLClick)
		UINM_LCLICK(_T("closebtn"), OnSysBtnLClick)
		UINM_LCLICK(_T("restorebtn"), OnSysBtnLClick)

		UINM_LCLICK(_T("cancelbtn"), OnCancelBtnLClick)
		UINM_LCLICK(_T("sendbtn"), OnSendBtnLClick)
		UINM_LCLICK(_T("menubtn"), OnMenuBtnLClick)
		UINM_RETURN(_T("inputedit"), OnSendBtnLClick)

		UINM_SELECTCHANGED(_T("fontbtn"), OnFontBtnSelectChanged)
		UINM_SELECTCHANGED(_T("splitbtn"), OnSplitBtnSelectChanged)

	END_UINOTIFY_MAP()
public:
	LPCTSTR GetWindowClassName() const 
	{
		return _T("UIChatFrame"); 
	}

	UINT GetClassStyle() const 
	{ 
		return CS_DBLCLKS; 
	}

	void OnFinalMessage(HWND hWnd) 
	{ 
		CSkinManager::GetSkinManager()->RemoveReceiver(this);
		CUIWindow::OnFinalMessage(hWnd); 
		delete this; 
	}

public:
	virtual LPCTSTR GetResFile() 
	{
		return _T("IDX_CHATFRAME"); 
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

		UIFINDCONTROL(CUIRichEdit, pRichEdit, _T("wordedit"));
		for(int i = 0; i < 6; i++)
		{
			CStdString sGif;
			sGif.Format(_T("images/face/%d.gif"), i);
			pRichEdit->InsertGIF(sGif, i, 0);
		}
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

	void OnCancelBtnLClick(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		Close(0);
	}

	void OnSendBtnLClick(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		SendMsg();
	}
	
	void OnMenuBtnLClick(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
	}

	void OnFontBtnSelectChanged(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		REALCONTROL(CUIEXButton, pFontBtn, pControl);
		UIFINDCONTROL(CUIControl, pFontPanel, _T("fontbar"));
		if(pFontPanel != NULL && pFontBtn != NULL)
		{
			pFontPanel->SetVisible(pFontBtn->IsSelected());
		}
	}

	void OnSplitBtnSelectChanged(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		REALCONTROL(CUIEXButton, pSplitBtn, pControl);
		UIFINDCONTROL(CUIControl, pLeftPanel, _T("body.right"));
		if(pLeftPanel != NULL && pSplitBtn != NULL)
		{
			pLeftPanel->SetVisible(!pSplitBtn->IsSelected());
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

	void SendMsg()
	{
		UIFINDCONTROL(CUIRichEdit, pInputEdit, _T("inputedit"));
		UIFINDCONTROL(CUIRichEdit, pRichEdit, _T("wordedit"));

		if( pInputEdit == NULL ) return;
		pInputEdit->SetFocus();
		CStdString sText = pInputEdit->GetTextRange(0, pInputEdit->GetTextLength());
		if( sText.IsEmpty() ) return;
		pInputEdit->SetText(_T(""));

		if( pRichEdit == NULL ) return;
		long lSelBegin = 0, lSelEnd = 0;
		CHARFORMAT2 cf;
		ZeroMemory(&cf, sizeof(CHARFORMAT2));
		cf.cbSize = sizeof(cf);
		cf.dwReserved = 0;
		cf.dwMask = CFM_COLOR | CFM_LINK | CFM_UNDERLINE | CFM_UNDERLINETYPE;
		cf.dwEffects = CFE_LINK;
		cf.bUnderlineType = CFU_UNDERLINE;
		cf.crTextColor = RGB(220, 0, 0);

		lSelEnd = lSelBegin = pRichEdit->GetTextLength();
		pRichEdit->SetSel(lSelEnd, lSelEnd);
		pRichEdit->ReplaceSel(_T("duisharp "), false);
		lSelEnd = lSelBegin = pRichEdit->GetTextLength();

		pRichEdit->SetSel(lSelEnd, lSelEnd);
		pRichEdit->ReplaceSel(_T("(1494621855)"), false);
		lSelEnd = pRichEdit->GetTextLength();
		pRichEdit->SetSel(lSelBegin + 1, lSelEnd - 1);
		pRichEdit->SetSelectionCharFormat(cf);

		lSelEnd = lSelBegin = pRichEdit->GetTextLength();
		pRichEdit->SetSel(lSelEnd, lSelEnd);
		SYSTEMTIME st;
		::GetLocalTime(&st);
		CStdString sTime;
		sTime.SmallFormat(_T("  %02d:%02d:%02d\n"), st.wHour, st.wMinute, st.wSecond);

		pRichEdit->ReplaceSel(sTime, false);
		cf.dwMask = CFM_COLOR;
		cf.crTextColor = RGB(0, 0, 0);
		cf.dwEffects = 0;
		lSelEnd = pRichEdit->GetTextLength();
		pRichEdit->SetSel(lSelBegin, lSelEnd);
		pRichEdit->SetSelectionCharFormat(cf);

		PARAFORMAT2 pf;
		ZeroMemory(&pf, sizeof(PARAFORMAT2));
		pf.cbSize = sizeof(pf);
		pf.dwMask = PFM_STARTINDENT;
		pf.dxStartIndent = 0;
		pRichEdit->SetParaFormat(pf);

		lSelEnd = lSelBegin = pRichEdit->GetTextLength();

		pRichEdit->SetSel(-1, -1);
		pRichEdit->ReplaceSel(sText.GetData(), false);

		pRichEdit->SetSel(-1, -1);
		pRichEdit->ReplaceSel(_T("\n"), false);

		cf.crTextColor = RGB(0, 0, 0);
		lSelEnd = pRichEdit->GetTextLength();
		pRichEdit->SetSel(lSelBegin, lSelEnd);
		pRichEdit->SetSelectionCharFormat(cf);

		ZeroMemory(&pf, sizeof(PARAFORMAT2));
		pf.cbSize = sizeof(pf);
		pf.dwMask = PFM_STARTINDENT;
		pf.dxStartIndent = 220;
		pRichEdit->SetParaFormat(pf);

		pRichEdit->EndDown();
	}

private:
	CUIButton* m_pCloseBtn;
	CUIButton* m_pMaxBtn;
	CUIButton* m_pRestoreBtn;
	CUIButton* m_pMinBtn;
};