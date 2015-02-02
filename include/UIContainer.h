#ifndef __UICONTAINER_H__
#define __UICONTAINER_H__

namespace duisharp {
	/////////////////////////////////////////////////////////////////////////////////////
	//
	// 容器子控件的对齐方式
#define CA_NULL			0x00000000
#define CA_LEFT			0x00000001
#define CA_CENTER		0x00000002
#define CA_RIGHT		0x00000004
#define CA_TOP			0x00000010
#define CA_VCENTER		0x00000020
#define CA_BOTTOM		0x00000040

	typedef int (*LPSORTPROC)(LPCVOID pCtrl1, LPCVOID pCtrl2, LPVOID pData);

	class IUIContainer
	{
	public:
		virtual CUIControl* GetItemAt(int iIndex) const = 0;
		virtual int GetItemIndex(CUIControl* pControl) const  = 0;
		virtual bool SetItemIndex(CUIControl* pControl, int iIndex)  = 0;
		virtual int GetCount() const = 0;
		virtual bool Add(CUIControl* pControl) = 0;
		virtual bool AddAt(CUIControl* pControl, int iIndex)  = 0;
		virtual bool Remove(CUIControl* pControl) = 0;
		virtual bool RemoveAt(int iIndex)  = 0;
		virtual void RemoveAll() = 0;

		virtual SIZE GetScrollPos() const = 0;
		virtual SIZE GetScrollRange() const = 0;
		virtual void SetScrollPos(SIZE szPos) = 0;
		virtual void ScrollUp() = 0;
		virtual void ScrollDown() = 0;
		virtual void LineUp() = 0;
		virtual void LineDown() = 0;
		virtual void PageUp() = 0;
		virtual void PageDown() = 0;
		virtual void HomeUp() = 0;
		virtual void EndDown() = 0;
		virtual void ScrollLeft() = 0;
		virtual void ScrollRight() = 0;
		virtual void LineLeft() = 0;
		virtual void LineRight() = 0;
		virtual void PageLeft() = 0;
		virtual void PageRight() = 0;
		virtual void HomeLeft() = 0;
		virtual void EndRight() = 0;

		virtual void SetScrollFocus() = 0;
		virtual void NeedScrollUpdate() = 0;
		virtual void DoScrollEvent(TUIEvent& event) = 0;
		virtual void KillScrollTimer(int nTimerID) = 0;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//
	class CUIScrollBar;

	class CUIContainer : public IUIContainer, public CUIButton
	{
	public:
		CUIContainer();
		  ~CUIContainer();
	public:
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

	public:
		CUIControl* GetItemAt(int iIndex) const;
		int GetItemIndex(CUIControl* pControl) const;
		bool SetItemIndex(CUIControl* pControl, int iIndex);
		int GetCount() const;
		bool Add(CUIControl* pControl);
		bool AddAt(CUIControl* pControl, int iIndex);
		bool Remove(CUIControl* pControl);
		bool RemoveAt(int iIndex);
		void RemoveAll();

	public:
		void SetVisible(bool bVisible = true);
		void SetInternVisible(bool bVisible = true);
		void SetMouseEnabled(bool bEnabled = true);

		virtual bool IsEventContainer() const;
		virtual void SetEventContainer(bool bEvent = false);
		virtual RECT GetInset() const;
		virtual void SetInset(RECT rcInset);
		virtual int GetChildPadding() const;
		virtual void SetChildPadding(int iPadding);
		virtual bool IsAutoDestroy() const;
		virtual void SetAutoDestroy(bool bAuto);
		virtual bool IsDelayedDestroy() const;
		virtual void SetDelayedDestroy(bool bDelayed);
		virtual bool IsMouseChildEnabled() const;
		virtual void SetMouseChildEnabled(bool bEnable = true);
		virtual int GetAlign();
		virtual void SetAlign(int uAlign);

		CStdString GetSubControlText(LPCTSTR pstrSubControlName);
		int GetSubControlFixedHeight(LPCTSTR pstrSubControlName);
		int GetSubControlFixedWdith(LPCTSTR pstrSubControlName);
		const CStdString GetSubControlUserData(LPCTSTR pstrSubControlName);
		bool SetSubControlText( LPCTSTR pstrSubControlName,LPCTSTR pstrText);
		bool SetSubControlFixedHeight(LPCTSTR pstrSubControlName,int cy);
		bool SetSubControlFixedWdith(LPCTSTR pstrSubControlName,int cx);
		bool SetSubControlUserData(LPCTSTR pstrSubControlName,LPCTSTR pstrText);

		virtual CUIControl* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags);
		virtual CUIControl* FindSubControl(LPCTSTR pstrSubControlName);
		virtual int FindSelectable(int iIndex, bool bForward = true) const;

		//////////////////////////////////////////////////////////////////
		// 滚动条相关
		virtual SIZE GetScrollPos() const;
		virtual SIZE GetScrollRange() const;
		virtual void SetScrollPos(SIZE szPos);
		virtual void ScrollUp();
		virtual void ScrollDown();
		virtual void LineUp();
		virtual void LineDown();
		virtual void PageUp();
		virtual void PageDown();
		virtual void HomeUp();
		virtual void EndDown();
		virtual void ScrollLeft();
		virtual void ScrollRight();
		virtual void LineLeft();
		virtual void LineRight();
		virtual void PageLeft();
		virtual void PageRight();
		virtual void HomeLeft();
		virtual void EndRight();
		virtual void EnableScrollBar(bool bEnableVertical = true, bool bEnableHorizontal = false);
		virtual CUIScrollBar* GetVerticalScrollBar() const;
		virtual CUIScrollBar* GetHorizontalScrollBar() const;
		virtual void SetScrollFocus();
		virtual void NeedScrollUpdate();
		virtual void DoScrollEvent(TUIEvent& event);
		virtual void KillScrollTimer(int nTimerID);

		//////////////////////////////////////////////////////////////////
		// 布局排序
		virtual void SetPos(RECT rc);
		virtual bool Sort(LPSORTPROC Proc, LPVOID pData = NULL);
		virtual SIZE EstimateSize(SIZE szAvailable, bool bSized = true);

		void DoEvent(TUIEvent& event);
		void DoPaint(HDC hDC, const RECT& rcPaint, UINT uType = 0);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void SetManager(CUIManager* pManager, CUIControl* pParent, bool bInit = true);

	protected:
		virtual void ProcessScrollBar(RECT rc, int cxRequired, int cyRequired);
		static int __cdecl SortFunc(LPVOID pOwner, LPCVOID pCtrl1, LPCVOID pCtrl2);

	protected:
		CStdPtrArray m_items;
		RECT m_rcInset;
		int m_iChildPadding;
		int m_iScrollRange;
		bool m_bAutoDestroy;
		bool m_bDelayedDestroy;
		bool m_bMouseChildEnabled;
		bool m_bScrollProcess;		// 防止SetPos循环调用
		bool m_bEventContainer;		// 是否接收鼠标事件
		UINT m_uAlign;				// 子控件对齐方式

		LPSORTPROC m_pSortFunc;
		LPVOID m_pSortData;

		CUIScrollBar* m_pVerticalScrollBar;
		CUIScrollBar* m_pHorizontalScrollBar;
		LONG m_dwDelayDeltaY;
		DWORD m_dwDelayNum;
		DWORD m_dwDelayLeft;
	};
	
} // namespace duisharp

#endif // __UICONTAINER_H__
