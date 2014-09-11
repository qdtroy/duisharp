#ifndef __UICONTROL_H__
#define __UICONTROL_H__

namespace duisharp {
	/////////////////////////////////////////////////////////////////////////////////////
	//

	typedef CUIControl* (CALLBACK* FINDCONTROLPROC)(CUIControl*, LPVOID);

	class DUISHARP_API CUIControl
	{
	public:
		CUIControl();
		virtual ~CUIControl();

	public:
		virtual CStdString GetName() const;
		virtual void SetName(LPCTSTR pstrName);
		virtual LPCTSTR GetClass() const;
		virtual LPVOID GetInterface(LPCTSTR pstrName);
		virtual UINT GetControlFlags() const;

		virtual bool Activate();
		virtual CUIManager* GetManager() const;
		virtual void SetManager(CUIManager* pManager, CUIControl* pParent, bool bInit = true);
		virtual CUIControl* GetParent() const;
		
		// 文本相关
		virtual CStdString GetText() const;
		virtual void SetText(LPCTSTR pstrText);
		virtual void SetFont(LPCTSTR pstrName);
		virtual CStdString GetFont() const;
		virtual UINT GetTextStyle() const;
		virtual void SetTextStyle(UINT uStyle);
		virtual DWORD GetTextColor() const;
		virtual void SetTextColor(DWORD dwTextColor);
		virtual void SetDisabledTextColor(DWORD dwTextColor);
		virtual DWORD GetDisabledTextColor() const;
		virtual void SetTextPadding(RECT rc);
		virtual RECT GetTextPadding() const;
		virtual bool IsShowHtml();
		virtual void SetShowHtml(bool bShowHtml = true);
		virtual int GetGlowSize() const;
		virtual void SetGlowSize(int nGlowSize);

		// 图形相关
		DWORD GetBkColor() const;
		void SetBkColor(DWORD dwBackColor);
		LPCTSTR GetBkImage();
		void SetBkImage(LPCTSTR pStrImage);
		DWORD GetForeColor() const;
		void SetForeColor(DWORD dwForeColor);
		LPCTSTR GetForeImage();
		void SetForeImage(LPCTSTR pStrImage);
		DWORD GetBorderColor() const;
		void SetBorderColor(DWORD dwBorderColor);
		DWORD GetFocusBorderColor() const;
		void SetFocusBorderColor(DWORD dwBorderColor);
		bool IsColorHSL() const;
		void SetColorHSL(bool bColorHSL);
		int GetBorderSize() const;
		void SetBorderSize(int nSize);
		SIZE GetBorderRound() const;
		void SetBorderRound(SIZE cxyRound);
		bool DrawImage(HDC hDC, LPCTSTR pStrImage, LPCTSTR pStrModify = NULL);
		
		// 位置相关
		virtual const RECT& GetPos() const;
		virtual void SetPos(RECT rc);
		virtual int GetWidth() const;
		virtual int GetHeight() const;
		virtual int GetX() const;
		virtual int GetY() const;
		virtual RECT GetPadding() const;
		virtual void SetPadding(RECT rcPadding); // 设置外边距，由上层窗口绘制
		virtual SIZE GetFixedXY() const;         // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
		virtual void SetFixedXY(SIZE szXY);      // 仅float为true时有效
		virtual int GetFixedWidth() const;       // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
		virtual void SetFixedWidth(int cx);      // 预设的参考值
		virtual int GetFixedHeight() const;      // 实际大小位置使用GetPos获取，这里得到的是预设的参考值
		virtual void SetFixedHeight(int cy);     // 预设的参考值
		virtual int GetMinWidth() const;
		virtual void SetMinWidth(int cx);
		virtual int GetMaxWidth() const;
		virtual void SetMaxWidth(int cx);
		virtual int GetMinHeight() const;
		virtual void SetMinHeight(int cy);
		virtual int GetMaxHeight() const;
		virtual void SetMaxHeight(int cy);
		
		// 浮动控件
		virtual bool IsFloat() const;
		virtual void SetFloat(bool bFloat = true);
		virtual UINT GetFloatAlign() const;
		virtual void SetFloatAlign(UINT uAlign);
		virtual void SetFloatPadding(RECT rcPadding);
		virtual RECT GetFloatPadding() const;


		// 自动适应大小
		virtual bool IsAutoWidth() const;
		virtual void SetAutoWidth(bool bAuto);
		virtual bool IsAutoHeight() const;
		virtual void SetAutoHeight(bool bAuto);

		// 锁定状态
		virtual UINT GetLockStatus();
		virtual void SetLockStatus(UINT uLock);

		// 鼠标提示
		virtual CStdString GetToolTip() const;
		virtual void SetToolTip(LPCTSTR pstrText);

		// 光标
		virtual WORD GetCursor();
		virtual void SetCursor(WORD wCursor);

		// 快捷键
		virtual TCHAR GetShortcut() const;
		virtual void SetShortcut(TCHAR ch);

		// 菜单
		virtual bool IsContextMenuUsed() const;
		virtual void SetContextMenuUsed(bool bMenuUsed);

		// 用户属性
		virtual const CStdString& GetUserData(); // 辅助函数，供用户使用
		virtual void SetUserData(LPCTSTR pstrText); // 辅助函数，供用户使用
		virtual UINT_PTR GetTag() const; // 辅助函数，供用户使用
		virtual void SetTag(UINT_PTR pTag); // 辅助函数，供用户使用

		// 一些重要的属性
		virtual bool IsVisible() const;
		virtual void SetVisible(bool bVisible = true);
		virtual void SetInternVisible(bool bVisible = true); // 仅供内部调用，有些UI拥有窗口句柄，需要重写此函数
		virtual bool IsEnabled() const;
		virtual void SetEnabled(bool bEnable = true);
		virtual bool IsMouseEnabled() const;
		virtual void SetMouseEnabled(bool bEnable = true);
		virtual bool IsKeyboardEnabled() const;
		virtual void SetKeyboardEnabled(bool bEnable = true);
		virtual bool IsFocused() const;
		virtual void SetFocus();

		// 定时器函数
		bool SetTimer(UINT nTimerID, UINT iElapse);
		void KillTimer(UINT nTimerID);

		// 通知消息函数
<<<<<<< HEAD
		void SendNotify(LPCTSTR pstrMessage, WPARAM wParam = 0, LPARAM lParam = 0, bool bAsync = false);
		void SendNotify(TUINotify& Msg, bool bAsync = false);
=======
		void SendNotify(LPCTSTR pstrMessage, WPARAM wParam = 0, LPARAM lParam = 0, BOOL bAsync = FALSE);
		void SendNotify(TUINotify& Msg, BOOL bAsync = FALSE);
>>>>>>> origin/master

		// 特效函数
		virtual bool IsEffectRunning(UINT uEffect);
		virtual UINT GetEffect();
		virtual void SetEffect(UINT uEffect);
		virtual UINT GetEffectTime();
		virtual void SetEffectTime(UINT uTime = 300);
		// uFlag:1-截图，0-动作
		virtual void StartEffect(UINT uTime = 0, UINT uFlag = 1, bool bClear = true);
		virtual void StopEffect(bool bMsg = true, bool bClear = true);

		virtual CUIControl* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);

		void Invalidate();
		bool IsUpdateNeeded() const;
		void NeedUpdate();
		void NeedParentUpdate();
		void NeedLayout();
		void NeedParentLayout();
		DWORD GetAdjustColor(DWORD dwColor);

	public:

		virtual void Init();
		virtual void DoInit();

		virtual void Event(TUIEvent& event);
		virtual void DoEvent(TUIEvent& event);

		virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		virtual void SetStyle(LPCTSTR pstrValue);
		CUIControl* ApplyAttributeList(LPCTSTR pstrList);

		virtual SIZE EstimateSize(SIZE szAvailable, bool bSized = true);

		virtual void DoPaint(HDC hDC, const RECT& rcPaint, UINT uType = 0);
		virtual bool PaintPre(HDC hDC, const RECT& rcPaint, UINT uType = 0);
		virtual bool PaintPost(HDC hDC, const RECT& rcPaint, UINT uType = 0);
		virtual void PaintBkColor(HDC hDC);
		virtual void PaintBkImage(HDC hDC);
		virtual void PaintStatusImage(HDC hDC);
		virtual void PaintForeColor(HDC hDC);
		virtual void PaintForeImage(HDC hDC);
		virtual void PaintText(HDC hDC);
		virtual void PaintBorder(HDC hDC);
		virtual void PaintIconImage(HDC hDC);

		virtual void DoPostPaint(HDC hDC, const RECT& rcPaint, UINT uType = 0);
		// 特效绘制函数
		virtual void EffectPaint(HDC hDC, RECT rcPaint, UINT &uRet);

	public:
		CEventSource OnInit;
		CEventSource OnDestroy;
		CEventSource OnSize;
		CEventSource OnEvent;
		CEventSource OnNotify;

	protected:
		CUIManager* m_pManager;
		CUIControl* m_pParent;
		CStdString m_sName;
		bool m_bUpdateNeeded;
		bool m_bLayoutNeeded;
		bool m_bMenuUsed;
		RECT m_rcItem;
		RECT m_rcPadding;
		SIZE m_cXY;
		SIZE m_cxyFixed;
		SIZE m_cxyMin;
		SIZE m_cxyMax;
		bool m_bVisible;
		bool m_bInternVisible;
		bool m_bEnabled;
		bool m_bMouseEnabled;
		bool m_bKeyboardEnabled ;
		bool m_bFocused;
		bool m_bFloat;
		UINT m_uFloatAlign;
		RECT m_rcFloatPadding;
		bool m_bSetPos; // 防止SetPos循环调用
		bool m_bSized;

		CStdString m_sFont;
		CStdString m_sText;
		DWORD m_dwTextColor;
		DWORD m_dwDisabledTextColor;
		UINT m_uTextStyle;
		RECT m_rcTextPadding;
		bool m_bShowHtml;
		int m_nGlowSize;
		bool m_bAutoWidth;
		bool m_bAutoHeight;
		UINT m_uLockStatus;

		CStdString m_sToolTip;
		WORD m_wCursor;
		TCHAR m_chShortcut;
		CStdString m_sUserData;
		UINT_PTR m_pTag;

		DWORD m_dwBackColor;
		CStdString m_sBkImage;
		DWORD m_dwForeColor;
		CStdString m_sForeImage;
		DWORD m_dwBorderColor;
		DWORD m_dwFocusBorderColor;
		bool m_bColorHSL;
		int m_nBorderSize;
		SIZE m_cxyBorderRound;
		RECT m_rcPaint;
		// 动画特效变量
		bool m_bEffect;
		UINT m_uEffect;
		UINT m_uEffectTime;
		UINT m_uHalfEffectTime;
		double m_fXDistance;
		double m_fYDistance;
		double m_fXSpeed;
		double m_fYSpeed;
		double m_fXStep;
		double m_fYStep;
		RECT m_rcEffect;
		HBITMAP m_hBitmap;
		RECT m_rcWnd;
	};

} // namespace duisharp

#endif // __UICONTROL_H__
