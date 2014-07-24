#ifndef __UIMANAGER_H__
#define __UIMANAGER_H__

namespace duisharp {
	/////////////////////////////////////////////////////////////////////////////////////
	//

	class CUIControl;

	/////////////////////////////////////////////////////////////////////////////////////
	//

	typedef enum EVENTTYPE_UI
	{
		UIEVENT__FIRST = 1,
		UIEVENT__KEYBEGIN,
		UIEVENT_KEYDOWN,
		UIEVENT_KEYUP,
		UIEVENT_CHAR,
		UIEVENT_SYSKEY,
		UIEVENT__KEYEND,
		UIEVENT__MOUSEBEGIN,
		UIEVENT_MOUSEMOVE,
		UIEVENT_MOUSELEAVE,
		UIEVENT_MOUSEENTER,
		UIEVENT_MOUSEHOVER,

		UIEVENT_LBUTTONDOWN,
		UIEVENT_LBUTTONUP,
		UIEVENT_LDBCLICK,
		UIEVENT_RBUTTONDOWN,
		UIEVENT_RBUTTONUP,
		UIEVENT_RDBCLICK,
		UIEVENT_MBUTTONDOWN,
		UIEVENT_MBUTTONUP,
		UIEVENT_MDBCLICK,

		UIEVENT_CONTEXTMENU,
		UIEVENT_SCROLLWHEEL,
		UIEVENT__MOUSEEND,
		UIEVENT_KILLFOCUS,
		UIEVENT_SETFOCUS,
		UIEVENT_WINDOWSIZE,
		UIEVENT_SETCURSOR,
		UIEVENT_TIMER,
		UIEVENT_NOTIFY,
		UIEVENT_COMMAND,
		UIEVENT__LAST,
	};

	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Notify 消息
#ifndef UINM_DEFINE
#define UINM_DEFINE(id, value)	const TCHAR* const id = value
#endif

	UINM_DEFINE(UINM_WINDOWINIT,		_T("windowinit"));
	UINM_DEFINE(UINM_WINDOWSHOW,		_T("windowshow"));
	UINM_DEFINE(UINM_WINDOWSIZED,		_T("windowsized"));
	UINM_DEFINE(UINM_KILLFOCUS,		_T("killfocus"));
	UINM_DEFINE(UINM_SETFOCUS,			_T("setfocus"));
	UINM_DEFINE(UINM_SHOWACTIVEX,		_T("showactivex"));
	UINM_DEFINE(UINM_ITEMSELECT,		_T("itemselect"));
	UINM_DEFINE(UINM_ITEMACTIVE,		_T("itemactive"));
	UINM_DEFINE(UINM_ITEMCLICK,		_T("itemclick"));
	UINM_DEFINE(UINM_HEADERCLICK,		_T("headerclick"));
	UINM_DEFINE(UINM_TABSELECT,		_T("tabselect"));
	UINM_DEFINE(UINM_DROPDOWN,			_T("dropdown"));
	UINM_DEFINE(UINM_TIMER,			_T("timer"));
	UINM_DEFINE(UINM_MENU,				_T("menu"));
	UINM_DEFINE(UINM_LINK,				_T("link"));
	UINM_DEFINE(UINM_RETURN,			_T("return"));
	UINM_DEFINE(UINM_SCROLL,			_T("scroll"));
	UINM_DEFINE(UINM_MOUSEENTER,		_T("mouseenter"));
	UINM_DEFINE(UINM_MOUSEHOVER,		_T("mousehover"));
	UINM_DEFINE(UINM_MOUSELEAVE,		_T("mouseleave"));
	UINM_DEFINE(UINM_INDEXCHANGED,		_T("indexchanged"));
	UINM_DEFINE(UINM_SELECTCHANGED,		_T("selectchanged"));
	UINM_DEFINE(UINM_VALUECHANGED,		_T("valuechanged"));
	UINM_DEFINE(UINM_TEXTCHANGED,		_T("textchanged"));
	UINM_DEFINE(UINM_LDOWN,			_T("ldown"));
	UINM_DEFINE(UINM_RDOWN,			_T("rdown"));
	UINM_DEFINE(UINM_MDOWN,			_T("mdown"));
	UINM_DEFINE(UINM_LUP,				_T("lup"));
	UINM_DEFINE(UINM_RUP,				_T("rup"));
	UINM_DEFINE(UINM_MUP,				_T("mup"));
	UINM_DEFINE(UINM_LCLICK,			_T("lclick"));
	UINM_DEFINE(UINM_RCLICK,			_T("rclick"));
	UINM_DEFINE(UINM_MCLICK,			_T("mclick"));
	UINM_DEFINE(UINM_LDBCLICK,			_T("ldbclick"));
	UINM_DEFINE(UINM_RDBCLICK,			_T("rdbclick"));
	UINM_DEFINE(UINM_MDBCLICK,			_T("mdbclick"));
	UINM_DEFINE(UINM_EFFECTFINISH,     _T("effectfinish"));
	/////////////////////////////////////////////////////////////////////////////////////////////////
	// Notify消息映射

#define BEGIN_UINOTIFY_MAP(theClass) \
public: \
	virtual void Notify(TUINotify& msg) \
	{ \
	if(msg.pSender == NULL) return; \
	CUIControl *pObject = msg.pSender; \
	CStdString sName = pObject->GetName(); \
	CStdString sType = msg.sType; \
	WPARAM wParam = msg.wParam;	\
	LPARAM lParam = msg.lParam; \
	if(sType.GetLength() <= 0) \
	{ \
	return; \
	}

#define UINM_HANDLER(name, type, func) \
	else if((_tcsicmp(sName, name) == 0) && (_tcsicmp(sType, type) == 0)) \
	{ \
	func(pObject, wParam, lParam); \
	}

#define UINM_WINDOWINIT(name,	func)		UINM_HANDLER(name, UINM_WINDOWINIT,		func)
#define UINM_WINDOWSHOW(name,	func)		UINM_HANDLER(name, UINM_WINDOWSHOW,		func)
#define UINM_WINDOWSIZED(name,	func)		UINM_HANDLER(name, UINM_WINDOWSIZED,	func)
#define UINM_KILLFOCUS(name,	func)		UINM_HANDLER(name, UINM_KILLFOCUS,		func)
#define UINM_SETFOCUS(name,	func)		UINM_HANDLER(name, UINM_SETFOCUS,		func)
#define UINM_SHOWACTIVEX(name,	func)		UINM_HANDLER(name, UINM_SHOWACTIVEX,	func)
#define UINM_ITEMSELECT(name,	func)		UINM_HANDLER(name, UINM_ITEMSELECT,		func)
#define UINM_ITEMACTIVE(name,	func)		UINM_HANDLER(name, UINM_ITEMACTIVE,		func)
#define UINM_ITEMCLICK(name,	func)		UINM_HANDLER(name, UINM_ITEMCLICK,		func)
#define UINM_HEADERCLICK(name,	func)		UINM_HANDLER(name, UINM_HEADERCLICK,	func)
#define UINM_TABSELECT(name,	func)		UINM_HANDLER(name, UINM_TABSELECT,		func)
#define UINM_DROPDOWN(name,	func)		UINM_HANDLER(name, UINM_DROPDOWN,		func)
#define UINM_TIMER(name,		func)		UINM_HANDLER(name, UINM_TIMER,			func)
#define UINM_MENU(name,		func)		UINM_HANDLER(name, UINM_MENU,			func)
#define UINM_LINK(name,		func)		UINM_HANDLER(name, UINM_LINK,			func)
#define UINM_RETURN(name,		func)		UINM_HANDLER(name, UINM_RETURN,		func)
#define UINM_SCROLL(name,		func)		UINM_HANDLER(name, UINM_SCROLL,		func)
#define UINM_MOUSEENTER(name,	func)		UINM_HANDLER(name, UINM_MOUSEENTER,		func)
#define UINM_MOUSEHOVER(name,	func)		UINM_HANDLER(name, UINM_MOUSEHOVER,		func)
#define UINM_MOUSELEAVE(name,	func)		UINM_HANDLER(name, UINM_MOUSELEAVE,		func)
#define UINM_INDEXCHANGED(name,func)		UINM_HANDLER(name, UINM_INDEXCHANGED,	func)
#define UINM_SELECTCHANGED(name,func)		UINM_HANDLER(name, UINM_SELECTCHANGED,	func)
#define UINM_VALUECHANGED(name,func)		UINM_HANDLER(name, UINM_VALUECHANGED,	func)
#define UINM_TEXTCHANGED(name,	func)		UINM_HANDLER(name, UINM_TEXTCHANGED,	func)
#define UINM_LDOWN(name,		func)		UINM_HANDLER(name, UINM_LDOWN,			func)
#define UINM_RDOWN(name,		func)		UINM_HANDLER(name, UINM_RDOWN,			func)
#define UINM_MDOWN(name,		func)		UINM_HANDLER(name, UINM_MDOWN,			func)
#define UINM_LUP(name,			func)		UINM_HANDLER(name, UINM_LUP,			func)
#define UINM_RUP(name,			func)		UINM_HANDLER(name, UINM_RUP,			func)
#define UINM_MUP(name,			func)		UINM_HANDLER(name, UINM_MUP,			func)
#define UINM_LCLICK(name,		func)		UINM_HANDLER(name, UINM_LCLICK,		func)
#define UINM_RCLICK(name,		func)		UINM_HANDLER(name, UINM_RCLICK,		func)
#define UINM_MCLICK(name,		func)		UINM_HANDLER(name, UINM_MCLICK,		func)
#define UINM_LDBCLICK(name,	func)		UINM_HANDLER(name, UINM_LDBCLICK,		func)
#define UINM_RDBCLICK(name,	func)		UINM_HANDLER(name, UINM_RDBCLICK,		func)
#define UINM_MDBCLICK(name,	func)		UINM_HANDLER(name, UINM_MDBCLICK,		func)
#define UINM_EFFECTFINISH(name,func)		UINM_HANDLER(name, UINM_EFFECTFINISH,	func)

#define UINM_FILTER(type, func) \
	if((_tcsicmp(sType, type) == 0)) \
	{ \
	func(sName, pObject, wParam, lParam); \
	}

#define CHAIN_UINOTIFY_MAP(chainClass) chainClass::Notify(msg);

#define END_UINOTIFY_MAP() \
	return ; \
	}

	/////////////////////////////////////////////////////////////////////////////////////
	//

	// Flags for CUIControl::GetControlFlags()
#define UIFLAG_TABSTOP       0x00000001
#define UIFLAG_SETCURSOR     0x00000002
#define UIFLAG_WANTRETURN    0x00000004

	// Flags for FindControl()
#define UIFIND_ALL           0x00000000
#define UIFIND_VISIBLE       0x00000001
#define UIFIND_ENABLED       0x00000002
#define UIFIND_HITTEST       0x00000004
#define UIFIND_TOP_FIRST     0x00000008
#define UIFIND_ME_FIRST      0x80000000

	// Flags used for controlling the paint
#define UISTATE_FOCUSED      0x00000001
#define UISTATE_SELECTED     0x00000002
#define UISTATE_DISABLED     0x00000004
#define UISTATE_HOT          0x00000008
#define UISTATE_PUSHED       0x00000010
#define UISTATE_READONLY     0x00000020
#define UISTATE_CAPTURED     0x00000040

	/////////////////////////////////////////////////////////////////////////////////////
	// 浮动控件布局标识	
#define UIICON_TOP			0x00000000
#define UIICON_LEFT			0x00000000
#define UIICON_CENTER		0x00000001
#define UIICON_RIGHT		0x00000002
#define UIICON_VCENTER		0x00000004
#define UIICON_BOTTOM		0x00000008

	/////////////////////////////////////////////////////////////////////////////////////
	// 浮动控件布局标识
#define UIFLOAT_NULL		0x00000000
#define UIFLOAT_LEFT		0x00000001
#define UIFLOAT_CENTER		0x00000002
#define UIFLOAT_RIGHT		0x00000004
#define UIFLOAT_AUTO		0x00000008
#define UIFLOAT_TOP			0x00000010
#define UIFLOAT_VCENTER		0x00000020
#define UIFLOAT_BOTTOM		0x00000040
#define UIFLOAT_VAUTO		0x00000080

/////////////////////////////////////////////////////////////////////////////////////
// 内部消息ID
typedef enum enUIWM
{
	UIWM_TIMER = WM_USER + 10,
	UIWM_MENU,
	
	//...

	UIWM_USER = WM_USER + 100,
};

/////////////////////////////////////////////////////////////////////////////////////
// 定时器ID
typedef enum enUITIMER
{
	UITIMER_ID_SETFOCUS = 10,
	UITIMER_ID_SCROLLBAR,
	UITIMER_ID_SLIDER,
	UITIMER_ID_EFFECT,
	//...
	UITIMER_ID_ANIMATION = 50,
	//...
	UITIMER_ID_USER = 100,
};

	/////////////////////////////////////////////////////////////////////////////////////
	//
	// 动画类型
	typedef enum _enEffectType
	{
		Effect_None = -1,
		Effect_Min = 0,

		Effect_FadeIn,
		Effect_FadeOut,

		Effect_LR,
		Effect_RL,
		Effect_TB,
		Effect_BT,

		Effect_LR_2,
		Effect_RL_2,
		Effect_TB_2,
		Effect_BT_2,

		Effect_Center,
		Effect_VCenter,
		Effect_HCenter,

		Effect_ExpandCenter,
		Effect_VExpandCenter,
		Effect_HExpandCenter,

		Effect_Expand,
		Effect_VExpand,
		Effect_HExpand,
		Effect_RBExpand,
		Effect_RTExpand,
		Effect_LBExpand,
		Effect_LTExpand,

		Effect_Max,
	};

#define UIEFFECT_ELAPSE	5

	/////////////////////////////////////////////////////////////////////////////////////
	//

	// Structure for notifications from the system
	// to the control implementation.
	typedef struct tagTUIEvent
	{
		int Type;
		CUIControl* pSender;
		DWORD dwTimestamp;
		POINT ptMouse;
		TCHAR chKey;
		WORD wKeyState;
		WPARAM wParam;
		LPARAM lParam;
	} TUIEvent;

	// Structure for notifications to the outside world
	typedef struct tagTUINotify 
	{
		CStdString sType;
		CUIControl* pSender;
		DWORD dwTimestamp;
		POINT ptMouse;
		WPARAM wParam;
		LPARAM lParam;
	} TUINotify;

	// Listener interface
	class IUINotify
	{
	public:
		virtual void Notify(TUINotify& msg) = 0;
	};

	// MessageFilter interface
	class IUISubMessageFilter
	{
	public:
		virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled) = 0;
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//
	typedef CUIControl* (*LPCREATECONTROL)(LPCTSTR pstrType);


	class DUISHARP_API CUIManager
	{
	public:
		CUIManager();
		~CUIManager();

	public:
		void Init(HWND hWnd);
		void NeedUpdate();
		void Invalidate(RECT& rcItem);
		void ReloadRes();

		HDC GetPaintDC() const;
		HWND GetUIWindow() const;
		HWND GetTTWindow() const;

		POINT GetMousePos() const;
		SIZE GetClientSize() const;
		SIZE GetInitSize();
		void SetInitSize(int cx, int cy);
		RECT& GetSizeBox();
		void SetSizeBox(RECT& rcSizeBox);
		RECT& GetCaptionRect();
		void SetCaptionRect(RECT& rcCaption);
		SIZE GetRoundCorner() const;
		void SetRoundCorner(int cx, int cy);
		SIZE GetMinInfo() const;
		void SetMinInfo(int cx, int cy);
		SIZE GetMaxInfo() const;
		void SetMaxInfo(int cx, int cy);
		int GetTransparent() const;
		void SetTransparent(int nOpacity);
		bool IsBackgroundTransparent() const;
		void SetBackgroundTransparent(bool bTrans);
		bool IsAero(bool bAero = false) const;
		void SetAero(bool bAero);
		void SetMargins(MARGINS mar);
		MARGINS GetMargins() const;
		bool IsBlur() const;
		void SetBlur(bool bBlur);
		void SetRgn();
		bool IsShowUpdateRect() const;
		void SetShowUpdateRect(bool show);

		bool IsShadowEnable();
		void SetShadowEnable(bool bEnable = true);
		void SetShadowImage(LPCTSTR pImage);
		void SetShadowBorder(RECT rcBorder);
		void SetShadowTrans(bool bTrans);

		void SetPreventLostFocus(bool bPrevent);
		bool IsPreventLostFocus() const;

		bool UseParentResource(CUIManager* pm);
		CUIManager* GetParentResource() const;

		// 窗口默认属性
		DWORD GetDefaultDisabledFontColor() const;
		void SetDefaultDisabledFontColor(DWORD dwColor);
		DWORD GetDefaultFontColor() const;
		void SetDefaultFontColor(DWORD dwColor);
		DWORD GetDefaultLinkFontColor() const;
		void SetDefaultLinkFontColor(DWORD dwColor);
		DWORD GetDefaultLinkHoverFontColor() const;
		void SetDefaultLinkHoverFontColor(DWORD dwColor);
		DWORD GetDefaultSelectedBkColor() const;
		void SetDefaultSelectedBkColor(DWORD dwColor);
		// 默认字体
		TFontInfo* GetDefaultFontInfo();
		HFONT GetDefaultFont();
		void SetDefaultFont(LPCTSTR pStrFontName);
		void SetDefaultFont(LPCTSTR pStrFaceName, int nSize, bool bBold, bool bUnderline, bool bItalic);

		DWORD GetCustomFontCount() const;
		HFONT AddFont(LPCTSTR pStrFontName, LPCTSTR pStrFaceName, int nSize, bool bBold, bool bUnderline, bool bItalic);
		HFONT AddFont(LPCTSTR pStrFaceName, int nSize, bool bBold, bool bUnderline, bool bItalic);
		HFONT AddFontAt(int index, LPCTSTR pStrFaceName, int nSize, bool bBold, bool bUnderline, bool bItalic);
		HFONT GetFont(LPCTSTR pStrFontName);
		HFONT GetFont(int index);
		HFONT GetFont(LPCTSTR pStrFaceName, int nSize, bool bBold, bool bUnderline, bool bItalic);
		bool FindFont(HFONT hFont);
		bool FindFont(LPCTSTR pStrFaceName, int nSize, bool bBold, bool bUnderline, bool bItalic);
		int GetFontIndex(HFONT hFont);
		int GetFontIndex(LPCTSTR pStrFaceName, int nSize, bool bBold, bool bUnderline, bool bItalic);
		bool RemoveFont(HFONT hFont);
		bool RemoveFontAt(int index);
		void RemoveAllFonts();
		TFontInfo* GetFontInfo(int index);
		TFontInfo* GetFontInfo(LPCTSTR pStrFontName);
		TFontInfo* GetFontInfo(HFONT hFont);

		void AddDefaultAttributeList(LPCTSTR pStrControlName, LPCTSTR pStrControlAttrList);
		LPCTSTR GetDefaultAttributeList(LPCTSTR pStrControlName) const;
		bool RemoveDefaultAttributeList(LPCTSTR pStrControlName);
		const CStdStringPtrMap& GetDefaultAttribultes() const;
		void RemoveAllDefaultAttributeList();

		void AddStyle(LPCTSTR pStrAttrName, LPCTSTR pStrAttr);
		LPCTSTR GetStyle(LPCTSTR pStrAttrName) const;
		bool RemoveStyle(LPCTSTR pStrAttrName);
		const CStdStringPtrMap& GetStyles() const;
		void RemoveAllStyles();

		bool AttachDialog(CUIControl* pControl);
		bool InitControls(CUIControl* pControl, CUIControl* pParent = NULL);
		void ReapObjects(CUIControl* pControl);

		bool AddOptionGroup(LPCTSTR pStrGroupName, CUIControl* pControl);
		CStdPtrArray* GetOptionGroup(LPCTSTR pStrGroupName);
		void RemoveOptionGroup(LPCTSTR pStrGroupName, CUIControl* pControl);
		void RemoveAllOptionGroups();

		CUIControl* GetFocus() const;
		void SetFocus(CUIControl* pControl);
		void SetFocusNeeded(CUIControl* pControl);

		bool SetNextTabControl(bool bForward = true);

		bool SetTimer(CUIControl* pControl, UINT nTimerID, UINT uElapse);
		bool KillTimer(CUIControl* pControl, UINT nTimerID);
		void KillTimer(CUIControl* pControl);
		void RemoveAllTimers();

		void SetCapture();
		void ReleaseCapture();
		bool IsCaptured();

		bool AddNotifier(IUINotify* pControl);
		bool RemoveNotifier(IUINotify* pControl);   
		void SendNotify(TUINotify& Msg, bool bAsync = false);
		void SendNotify(CUIControl* pControl, LPCTSTR pstrMessage, WPARAM wParam = 0, LPARAM lParam = 0, bool bAsync = false);

		int GetPostPaintCount() const;
		bool AddPostPaint(CUIControl* pControl);
		bool RemovePostPaint(CUIControl* pControl);
		bool SetPostPaintIndex(CUIControl* pControl, int iIndex);

		void AddDelayedCleanup(CUIControl* pControl);

		CUIControl* GetRoot() const;
		CUIControl* FindControl(POINT pt) const;
		CUIControl* FindControl(LPCTSTR pstrName) const;
		CUIControl* FindSubControlByPoint(CUIControl* pParent, POINT pt) const;
		CUIControl* FindSubControlByName(CUIControl* pParent, LPCTSTR pstrName) const;
		CUIControl* FindSubControlByClass(CUIControl* pParent, LPCTSTR pstrClass, int iIndex = 0);
		CStdPtrArray* FindSubControlsByClass(CUIControl* pParent, LPCTSTR pstrClass);
		CStdPtrArray* GetSubControlsByClass();

		bool AddPreMessageFilter(IUISubMessageFilter* pFilter);
		bool RemovePreMessageFilter(IUISubMessageFilter* pFilter);
		bool AddMessageFilter(IUISubMessageFilter* pFilter);
		bool RemoveMessageFilter(IUISubMessageFilter* pFilter);

		bool MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);
		bool PreMessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, LRESULT& lRes);

	private:
		static CUIControl* CALLBACK __FindControlFromNameHash(CUIControl* pThis, LPVOID pData);
		static CUIControl* CALLBACK __FindControlFromCount(CUIControl* pThis, LPVOID pData);
		static CUIControl* CALLBACK __FindControlFromPoint(CUIControl* pThis, LPVOID pData);
		static CUIControl* CALLBACK __FindControlFromTab(CUIControl* pThis, LPVOID pData);
		static CUIControl* CALLBACK __FindControlFromShortcut(CUIControl* pThis, LPVOID pData);
		static CUIControl* CALLBACK __FindControlFromUpdate(CUIControl* pThis, LPVOID pData);
		static CUIControl* CALLBACK __FindControlFromName(CUIControl* pThis, LPVOID pData);
		static CUIControl* CALLBACK __FindControlFromClass(CUIControl* pThis, LPVOID pData);
		static CUIControl* CALLBACK __FindControlsFromClass(CUIControl* pThis, LPVOID pData);

	private:
		HWND m_hUIWnd;
		int m_nOpacity;
		HDC m_hDcPaint;
		HDC m_hDcBuffer;
		HBITMAP m_hBmpBuffer;
		LPBYTE m_pBufferBits;
		BP_PAINTPARAMS m_PaintParams;
		CUIBufferedPaint m_BufferedPaint;
		HWND m_hToolTip;
		TOOLINFO m_ToolTip;
		bool m_bShowUpdateRect;

		//
		CUIControl* m_pRoot;
		CUIControl* m_pFocus;
		CUIControl* m_pEventHover;
		CUIControl* m_pEventClick;
		CUIControl* m_pEventKey;
		//
		POINT m_ptLastMousePos;
		SIZE m_szMinWindow;
		SIZE m_szMaxWindow;
		SIZE m_szInitWindowSize;
		RECT m_rcSizeBox;
		SIZE m_szRoundCorner;
		RECT m_rcCaption;
		UINT m_uTimerID;
		bool m_bFirstLayout;
		bool m_bFirstPaint;
		bool m_bUpdateNeeded;
		bool m_bFocusNeeded;
		bool m_bAlphaBackground;
		bool m_bAero;
		bool m_bBlur;
		MARGINS m_Margins;
		bool m_bMouseTracking;
		bool m_bMouseCapture;
		bool m_bPreventLostFocus;
		//
		CStdPtrArray m_aNotifiers;
		CStdPtrArray m_aTimers;
		CStdPtrArray m_aPreMessageFilters;
		CStdPtrArray m_aMessageFilters;
		CStdPtrArray m_aPostPaintControls;
		CStdPtrArray m_aDelayedCleanup;
		CStdPtrArray m_aAsyncNotify;
		CStdPtrArray m_aFoundControls;
		CStdStringPtrMap m_mNameHash;
		CStdStringPtrMap m_mOptionGroup;
		//
		CUIManager* m_pParentManager;
		DWORD m_dwDefaultDisabledColor;
		DWORD m_dwDefaultFontColor;
		DWORD m_dwDefaultLinkFontColor;
		DWORD m_dwDefaultLinkHoverFontColor;
		DWORD m_dwDefaultSelectedBkColor;
		TFontInfo* m_pDefaultFontInfo;
		CStdPtrArray m_aCustomFonts;

		CStdStringPtrMap m_mImageHash;
		CStdStringPtrMap m_StyleHash;
		CStdStringPtrMap m_DefaultAttrHash;

		// 阴影辅助功能
		CUIShadow m_Shadow;
	};

} // namespace duisharp

#endif // __UIMANAGER_H__
