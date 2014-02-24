#ifndef __UILAYOUTS_H__
#define __UILAYOUTS_H__

namespace duisharp {

	class CUIContainer;
	/////////////////////////////////////////////////////////////////////////////////////
	//
	class DUISHARP_API CUIVerticalLayout : public CUIContainer
	{
	public:
		CUIVerticalLayout();
	
	public:
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;

	public:
		void SetPos(RECT rc);
		void DoPostPaint(HDC hDC, const RECT& rcPaint, UINT uType = 0);
		void SetSepHeight(int iHeight);
		int GetSepHeight() const;
		void SetSepImmMode(bool bImmediately);
		bool IsSepImmMode() const;

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		void DoEvent(TUIEvent& event);
		RECT GetThumbRect(bool bUseNew) const;

	protected:
		int m_iSepHeight;
		UINT m_uButtonState;
		POINT ptLastMouse;
		RECT m_rcNewPos;
		bool m_bImmMode;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CUIHorizontalLayout : public CUIContainer
	{
	public:
		CUIHorizontalLayout();
		
	public:
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;

	public:
		void SetSepWidth(int iWidth);
		int GetSepWidth() const;
		void SetSepImmMode(bool bImmediately);
		bool IsSepImmMode() const;

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		void DoEvent(TUIEvent& event);
		void SetPos(RECT rc);
		void DoPostPaint(HDC hDC, const RECT& rcPaint, UINT uType = 0);
		RECT GetThumbRect(bool bUseNew = true) const;

	protected:
		int m_iSepWidth;
		UINT m_uButtonState;
		POINT ptLastMouse;
		RECT m_rcNewPos;
		bool m_bImmMode;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CUITileLayout : public CUIContainer
	{
	public:
		CUITileLayout();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		void SetPos(RECT rc);

		SIZE GetItemSize() const;
		void SetItemSize(SIZE szItem);
		int GetColumns() const;
		void SetColumns(int nCols);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	protected:
		SIZE m_szItem;
		int m_nColumns;
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CUITabLayout : public CUIContainer
	{
	public:
		CUITabLayout();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		bool Add(CUIControl* pControl);
		bool AddAt(CUIControl* pControl, int iIndex);
		bool Remove(CUIControl* pControl);
		void RemoveAll();
		int GetCurSel() const;
		bool SelectItem(int iIndex);
		bool SelectItem(CUIControl* pControl);

		void SetPos(RECT rc);

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	protected:
		int m_iCurSel;
	};

} // namespace duisharp

#endif // __UILAYOUTS_H__
