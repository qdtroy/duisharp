#ifndef __UICOMMONCONTROLS_H__
#define __UICOMMONCONTROLS_H__

namespace duisharp {

#define IA_TOP				0x00000000
#define IA_LEFT				0x00000000
#define IA_CENTER				0x00000001
#define IA_RIGHT				0x00000002
#define IA_VCENTER			0x00000004
#define IA_BOTTOM				0x00000008

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CUILabel : public CUIControl
	{
	public:
		CUILabel();

	public:
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

	public:
		SIZE EstimateSize(SIZE szAvailable, bool bSized = true);

		LPCTSTR GetIconImage();
		void SetIconImage(LPCTSTR pStrIcon);
		LPCTSTR GetDisabledIconImage();
		void SetDisabledIconImage(LPCTSTR pIconImage);
		UINT GetIconAlign();
		void SetIconAlign(UINT uAlign);
		SIZE GetIconSize();
		void SetIconSize(SIZE szIcon);
		RECT GetIconPadding();
		void SetIconPadding(RECT rcIconPadding);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void PaintIconImage(HDC hDC);
		void PaintText(HDC hDC);

	protected:
		RECT CalIconRect();

	protected:
		CStdString m_sIconImage;
		CStdString m_sDisabledIconImage;
		SIZE m_szIcon;
		RECT m_rcIconPadding;
		UINT m_uIconAlign;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CUIButton : public CUILabel
	{
	public:
		CUIButton();
		~CUIButton();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;

	public:
		void SetManager(CUIManager* pManager, CUIControl* pParent, bool bInit = true);
		bool Activate();
		void DoEvent(TUIEvent& event);

		void SetEnabled(bool bEnable = true);

	public:
		virtual LPCTSTR GetNormalImage();
		virtual void SetNormalImage(LPCTSTR pStrImage);
		virtual LPCTSTR GetHotImage();
		virtual void SetHotImage(LPCTSTR pStrImage);
		virtual LPCTSTR GetPushedImage();
		virtual void SetPushedImage(LPCTSTR pStrImage);
		virtual LPCTSTR GetFocusedImage();
		virtual void SetFocusedImage(LPCTSTR pStrImage);
		virtual LPCTSTR GetDisabledImage();
		virtual void SetDisabledImage(LPCTSTR pStrImage);

		virtual LPCTSTR GetHotIconImage();
		virtual void SetHotIconImage(LPCTSTR pIconImage);
		virtual LPCTSTR GetPushedIconImage();
		virtual void SetPushedIconImage(LPCTSTR pIconImage);
		virtual LPCTSTR GetFocusedIconImage();
		virtual void SetFocusedIconImage(LPCTSTR pIconImage);
		virtual LPCTSTR GetSelectedIconImage();
		virtual void SetSelectedIconImage(LPCTSTR pStrImage);

		virtual LPCTSTR GetSelectedImage();
		virtual void SetSelectedImage(LPCTSTR pStrImage);
		virtual LPCTSTR GetSelectedHotImage();
		virtual void SetSelectedHotImage(LPCTSTR pStrImage);
		virtual LPCTSTR GetSelectedPushedImage();
		virtual void SetSelectedPushedImage(LPCTSTR pStrImage);
		virtual LPCTSTR GetSelectedFocusedImage();
		virtual void SetSelectedFocusedImage(LPCTSTR pStrImage);
		virtual LPCTSTR GetSelectedDisabledImage();
		virtual void SetSelectedDisabledImage(LPCTSTR pStrImage);

		virtual void SetHotTextColor(DWORD dwColor);
		virtual DWORD GetHotTextColor() const;
		virtual void SetPushedTextColor(DWORD dwColor);
		virtual DWORD GetPushedTextColor() const;
		virtual void SetFocusedTextColor(DWORD dwColor);
		virtual DWORD GetFocusedTextColor() const;
		virtual void SetSelectedTextColor(DWORD dwTextColor);
		virtual DWORD GetSelectedTextColor();
		
		virtual bool IsOption() const;
		virtual void SetOption(bool bOption = true);
		virtual LPCTSTR GetGroup() const;
		virtual void SetGroup(LPCTSTR pStrGroupName = NULL);
		virtual bool IsSelected() const;
		virtual void Selected(bool bSelected);

		// 渐隐渐显特效参数
		virtual bool IsFade() const;
		virtual void SetFade(bool bFade);
		virtual void SetFadeSpeed(int fadespeed);
		virtual void SetFadeInSpeed(int fadespeed);
		virtual int GetFadeInSpeed() const;
		virtual void SetFadeOutSpeed(int fadespeed);
		virtual int GetFadeOutSpeed() const;

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void PaintText(HDC hDC);
		void PaintStatusImage(HDC hDC);
		void PaintIconImage(HDC hDC);
		// 特效绘制函数
		void EffectPaint(HDC hDC, RECT rcPaint, UINT &uRet);

	protected:
		bool m_bSelected;
		bool m_bOption;

		bool m_bFade;
		int m_nFadeInSpeed;
		int m_nFadeOutSpeed;
		UINT m_uButtonState;

		DWORD m_dwHotTextColor;
		DWORD m_dwPushedTextColor;
		DWORD m_dwFocusedTextColor;
		DWORD m_dwSelectedTextColor;

		CStdString m_sNormalImage;
		CStdString m_sHotImage;
		CStdString m_sPushedImage;
		CStdString m_sFocusedImage;
		CStdString m_sDisabledImage;

		CStdString m_sSelectedImage;
		CStdString m_sSelectedHotImage;
		CStdString m_sSelectedPushedImage;
		CStdString m_sSelectedFocusedImage;
		CStdString m_sSelectedDisabledImage;

		CStdString m_sHotIconImage;
		CStdString m_sPushedIconImage;
		CStdString m_sFocusedIconImage;
		CStdString m_sSelectedIconImage;

		CStdString m_sGroupName;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//
	enum enImageTimer
	{
		TIMER_IMAGE = UITIMER_ID_ANIMATION,
	};

	class DUISHARP_API CUIImage : public CUILabel
	{
	public:
		CUIImage();
		~CUIImage();

		LPCTSTR GetClass() const;
		UINT GetControlFlags() const;
		LPVOID GetInterface(LPCTSTR pstrName);

	public:
		bool Play();
		void Stop();
		bool IsPlaying() const;

	public:
		bool IsAutoPlay();
		void SetAutoPlay(bool bAutoPlay);
		UINT GetFrameCount();
		void SetFrameCount(UINT uFrameCount);
		UINT GetFrameElapse();
		void SetFrameElapse(UINT uFrameElapse);
		SIZE GetFrameSize();
		void SetFrameSize(SIZE szSize);

		void SetBkImage(LPCTSTR pstrImage);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void PaintBkImage(HDC hDC);
		void DoEvent(TUIEvent& event);

	protected:
		Image* m_pImage;
		bool m_bPlaying;
		bool m_bAutoPlay;
		UINT m_uImageType;
		UINT m_uFrameElapse;
		UINT *m_pFrameElapse;
		UINT m_uFrameCount;
		LONG m_uCurFrame;
		SIZE m_szFrame;
	};
	
	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CUIDataImage : public CUILabel
	{
	public:
		CUIDataImage();
		~CUIDataImage();

	public:
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

	public:
		HBITMAP GetImage();
		SIZE GetImageSize();
		void SetImageAlign(UINT uAlign);
		void SetImage(HBITMAP hBitmap);
		void SetImageData(BYTE* pData, DWORD dwSize);
		void SetImageData_RGB(BYTE* pData, DWORD dwSize, int nWidth, int nHeight, BOOL bAlpha = FALSE);

		void PaintBkImage(HDC hDC);

	protected:
		HBITMAP m_hBitmap;
		SIZE m_szBitmap;
		BOOL m_bAlpha;
		UINT m_uAlign;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CUIText : public CUILabel
	{
	public:
		CUIText();
		~CUIText();

		LPCTSTR GetClass() const;
		UINT GetControlFlags() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		CStdString* GetLinkContent(int iIndex);

		void DoEvent(TUIEvent& event);
		SIZE EstimateSize(SIZE szAvailable, bool bSized = true);

		void PaintText(HDC hDC);

	protected:
		enum { MAX_LINK = 8 };
		int m_nLinks;
		RECT m_rcLinks[MAX_LINK];
		CStdString m_sLinks[MAX_LINK];
		int m_nHoverLink;
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CUIProgress : public CUILabel
	{
	public:
		CUIProgress();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		bool IsHorizontal();
		void SetHorizontal(bool bHorizontal = true);
		bool IsStretchForeImage();
		void SetStretchForeImage(bool bStretchForeImage = true);
		int GetMinValue() const;
		void SetMinValue(int nMin);
		int GetMaxValue() const;
		void SetMaxValue(int nMax);
		int GetValue() const;
		void SetValue(int nValue);
		
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void PaintForeImage(HDC hDC);

	protected:
		bool m_bHorizontal;
		bool m_bStretchForeImage;
		int m_nMax;
		int m_nMin;
		int m_nValue;

		CStdString m_sForeImageModify;
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CUISlider : public CUIProgress
	{
	public:
		CUISlider();

		LPCTSTR GetClass() const;
		UINT GetControlFlags() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void SetEnabled(bool bEnable = true);

		int GetChangeStep();
		void SetChangeStep(int step);
		void SetThumbSize(SIZE szXY);
		RECT GetThumbRect() const;
		LPCTSTR GetThumbImage() const;
		void SetThumbImage(LPCTSTR pStrImage);
		LPCTSTR GetThumbHotImage() const;
		void SetThumbHotImage(LPCTSTR pStrImage);
		LPCTSTR GetThumbPushedImage() const;
		void SetThumbPushedImage(LPCTSTR pStrImage);

		void DoEvent(TUIEvent& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void PaintStatusImage(HDC hDC);

	protected:
		SIZE m_szThumb;
		UINT m_uButtonState;
		int m_nStep;
		int m_nOldValue;

		CStdString m_sThumbImage;
		CStdString m_sThumbHotImage;
		CStdString m_sThumbPushedImage;

		CStdString m_sImageModify;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class IUIEdit;

	class DUISHARP_API CUIEdit : public CUILabel
	{
		friend IUIEdit;
	public:
		CUIEdit();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;

		virtual void CreateEdit();
		virtual void DestroyEdit();

		void SetEnabled(bool bEnable = true);
		void SetText(LPCTSTR pstrText);
		void SetMaxChar(UINT uMax);
		UINT GetMaxChar();
		void SetReadOnly(bool bReadOnly);
		bool IsReadOnly() const;
		void SetPasswordMode(bool bPasswordMode);
		bool IsPasswordMode() const;
		void SetNumberMode(bool bNumberMode);
		bool IsNumberMode() const;
		void SetPasswordChar(TCHAR cPasswordChar);
		TCHAR GetPasswordChar() const;
		void SetComposited(bool bComposited);
		bool IsComposited() const;
		virtual CStdString GetHint() const;
		virtual void SetHint(LPCTSTR pstrHint);
		HWND GetNativeEdit();

		LPCTSTR GetNormalImage();
		void SetNormalImage(LPCTSTR pStrImage);
		LPCTSTR GetHotImage();
		void SetHotImage(LPCTSTR pStrImage);
		LPCTSTR GetFocusedImage();
		void SetFocusedImage(LPCTSTR pStrImage);
		LPCTSTR GetDisabledImage();
		void SetDisabledImage(LPCTSTR pStrImage);

		void SetNativeEditBkColor(DWORD dwBkColor);
		DWORD GetNativeEditBkColor() const;

		void SetPos(RECT rc);
		void SetVisible(bool bVisible = true);
		void SetInternVisible(bool bVisible = true);
		SIZE EstimateSize(SIZE szAvailable, bool bSized = true);
		void DoEvent(TUIEvent& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void PaintStatusImage(HDC hDC);
		void PaintText(HDC hDC);

		// 计算输入区域
		RECT CalEditRect();

	protected:
		IUIEdit* m_pWindow;

		UINT m_uMaxChar;
		bool m_bReadOnly;
		bool m_bPasswordMode;
		bool m_bNumberMode;
		bool m_bComposited;
		TCHAR m_cPasswordChar;
		UINT m_uButtonState;
		CStdString m_sHint;
		CStdString m_sStatusImage;
		CStdString m_sNormalImage;
		CStdString m_sHotImage;
		CStdString m_sFocusedImage;
		CStdString m_sDisabledImage;
		DWORD m_dwEditbkColor;
	};

	class IUIEdit
	{
	public:
		IUIEdit();

	public:
		virtual void Init(CUIEdit* pOwner) = 0;
		virtual HWND GetEditWnd() = 0;
		virtual bool IsWindow();
		virtual RECT CalPos();
		virtual void SetSelAll();
		virtual LRESULT OnKillFocus(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnEditChanged(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
		virtual LRESULT OnCtrlColor(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	protected:
		CUIEdit* m_pOwner;
		HBRUSH m_hBkBrush;
		bool m_bInit;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//
	class IUIContainer;

	class DUISHARP_API CUIScrollBar : public CUIControl
	{
	public:
		CUIScrollBar();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		IUIContainer* GetOwner() const;
		void SetOwner(IUIContainer* pOwner);

		void SetVisible(bool bVisible = true);
		void SetEnabled(bool bEnable = true);
		void SetFocus();

		bool IsHorizontal();
		void SetHorizontal(bool bHorizontal = true);
		int GetScrollRange() const;
		void SetScrollRange(int nRange);
		int GetScrollPos() const;
		void SetScrollPos(int nPos);
		int GetLineSize() const;
		void SetLineSize(int nSize);
		int GetScrollSize() const;
		void SetScrollSize(int nSize);

		bool GetShowButton1();
		void SetShowButton1(bool bShow);
		LPCTSTR GetButton1NormalImage();
		void SetButton1NormalImage(LPCTSTR pStrImage);
		LPCTSTR GetButton1HotImage();
		void SetButton1HotImage(LPCTSTR pStrImage);
		LPCTSTR GetButton1PushedImage();
		void SetButton1PushedImage(LPCTSTR pStrImage);
		LPCTSTR GetButton1DisabledImage();
		void SetButton1DisabledImage(LPCTSTR pStrImage);

		bool GetShowButton2();
		void SetShowButton2(bool bShow);
		LPCTSTR GetButton2NormalImage();
		void SetButton2NormalImage(LPCTSTR pStrImage);
		LPCTSTR GetButton2HotImage();
		void SetButton2HotImage(LPCTSTR pStrImage);
		LPCTSTR GetButton2PushedImage();
		void SetButton2PushedImage(LPCTSTR pStrImage);
		LPCTSTR GetButton2DisabledImage();
		void SetButton2DisabledImage(LPCTSTR pStrImage);

		LPCTSTR GetThumbNormalImage();
		void SetThumbNormalImage(LPCTSTR pStrImage);
		LPCTSTR GetThumbHotImage();
		void SetThumbHotImage(LPCTSTR pStrImage);
		LPCTSTR GetThumbPushedImage();
		void SetThumbPushedImage(LPCTSTR pStrImage);
		LPCTSTR GetThumbDisabledImage();
		void SetThumbDisabledImage(LPCTSTR pStrImage);

		LPCTSTR GetRailNormalImage();
		void SetRailNormalImage(LPCTSTR pStrImage);
		LPCTSTR GetRailHotImage();
		void SetRailHotImage(LPCTSTR pStrImage);
		LPCTSTR GetRailPushedImage();
		void SetRailPushedImage(LPCTSTR pStrImage);
		LPCTSTR GetRailDisabledImage();
		void SetRailDisabledImage(LPCTSTR pStrImage);

		LPCTSTR GetBkNormalImage();
		void SetBkNormalImage(LPCTSTR pStrImage);
		LPCTSTR GetBkHotImage();
		void SetBkHotImage(LPCTSTR pStrImage);
		LPCTSTR GetBkPushedImage();
		void SetBkPushedImage(LPCTSTR pStrImage);
		LPCTSTR GetBkDisabledImage();
		void SetBkDisabledImage(LPCTSTR pStrImage);

		void SetPos(RECT rc);
		void DoEvent(TUIEvent& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void DoPaint(HDC hDC, const RECT& rcPaint, UINT uType = 0);

		void PaintBk(HDC hDC);
		void PaintButton1(HDC hDC);
		void PaintButton2(HDC hDC);
		void PaintThumb(HDC hDC);
		void PaintRail(HDC hDC);

	protected:

		enum { 
			DEFAULT_SCROLLBAR_SIZE = 16,
			DEFAULT_TIMERID = 10,
		};

		bool m_bHorizontal;
		int m_nRange;
		int m_nScrollPos;
		int m_nLineSize;
		int m_nScrollSize;
		IUIContainer* m_pOwner;
		POINT ptLastMouse;
		int m_nLastScrollPos;
		int m_nLastScrollOffset;
		int m_nScrollRepeatDelay;

		CStdString m_sBkNormalImage;
		CStdString m_sBkHotImage;
		CStdString m_sBkPushedImage;
		CStdString m_sBkDisabledImage;

		bool m_bShowButton1;
		RECT m_rcButton1;
		UINT m_uButton1State;
		CStdString m_sButton1NormalImage;
		CStdString m_sButton1HotImage;
		CStdString m_sButton1PushedImage;
		CStdString m_sButton1DisabledImage;

		bool m_bShowButton2;
		RECT m_rcButton2;
		UINT m_uButton2State;
		CStdString m_sButton2NormalImage;
		CStdString m_sButton2HotImage;
		CStdString m_sButton2PushedImage;
		CStdString m_sButton2DisabledImage;

		RECT m_rcThumb;
		UINT m_uThumbState;
		CStdString m_sThumbNormalImage;
		CStdString m_sThumbHotImage;
		CStdString m_sThumbPushedImage;
		CStdString m_sThumbDisabledImage;

		CStdString m_sRailNormalImage;
		CStdString m_sRailHotImage;
		CStdString m_sRailPushedImage;
		CStdString m_sRailDisabledImage;

		CStdString m_sImageModify;
	};
} // namespace duisharp

#endif // __UICOMMONCONTROLS_H__

