#include "stdafx.h"
#include "resource.h"
#include "..\UIBase\ControlEx.h"
#include "flash10a.tlh"
class CQQFrame : public CUIWindow
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
		UINM_LCLICK(_T("minbtn"), OnSysBtnLClick)
		UINM_LCLICK(_T("maxbtn"), OnSysBtnLClick)
		UINM_LCLICK(_T("restorebtn"), OnSysBtnLClick)
		UINM_LCLICK(_T("closebtn"), OnSysBtnLClick)
		UINM_SHOWACTIVEX(_T("flash"), OnShowFlash)
		UINM_VALUECHANGED(_T("redbtn"), OnValueChanged)
		UINM_VALUECHANGED(_T("greenbtn"), OnValueChanged)
		UINM_VALUECHANGED(_T("bluebtn"), OnValueChanged)
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

	void OnSysBtnLClick(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		if( pControl == m_pCloseBtn ) {
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

	void OnShowFlash(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		IShockwaveFlash* pFlash = NULL;
		CUIActiveX* pActiveX = static_cast<CUIActiveX*>(m_ui.FindControl(_T("flash")));
		pActiveX->GetControl(IID_IUnknown, (void**)&pFlash);
		if( pFlash != NULL ) {
			CStdString sPath = _App->GetInstancePath();
			sPath.Format(_T("%sskin\\FlashRes\\test.swf"), sPath.GetData());
			pFlash->put_WMode(_bstr_t(_T("Transparent")));
			pFlash->put_Movie(_bstr_t(sPath.GetData()));
			pFlash->DisableLocalSecurity();
			pFlash->put_AllowScriptAccess(L"always");
			pFlash->Release();
		}
	}

	void OnValueChanged(CUIControl* pControl, WPARAM wParam, LPARAM lParam)
	{
		CStdString sName = pControl->GetName();

		CUISlider* pSliderR = static_cast<CUISlider*>(m_ui.FindControl(_T("redbtn")));
		CUISlider* pSliderG = static_cast<CUISlider*>(m_ui.FindControl(_T("greenbtn")));
		CUISlider* pSliderB = static_cast<CUISlider*>(m_ui.FindControl(_T("bluebtn")));

		BYTE red = pSliderR->GetValue();
		BYTE green = pSliderG->GetValue();
		BYTE blue = pSliderB->GetValue();
		COLORREF crColor = RGB(red, green, blue);
		TCHAR szBuf[MAX_PATH] = {0};
		_stprintf_s(szBuf, MAX_PATH - 1, _T("88%02X%02X%02X"), GetRValue(crColor), GetGValue(crColor), GetBValue(crColor));
		LPTSTR pstr = NULL;
		DWORD dwColor = _tcstoul(szBuf, &pstr, 16);

		m_ui.GetRoot()->SetBkColor(dwColor);
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