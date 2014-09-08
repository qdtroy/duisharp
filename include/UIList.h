#ifndef __UILIST_H__
#define __UILIST_H__

namespace duisharp {
	/////////////////////////////////////////////////////////////////////////////////////
	//

	class CUIListHeader;
	class CUIListBody;

#define UILIST_MAX_COLUMNS 32

	typedef struct tagTUIListInfo
	{
		int nColumns;
		RECT rcColumn[UILIST_MAX_COLUMNS];
		CStdString sFont;
		UINT uTextStyle;
		int nGlowSize;
		RECT rcTextPadding;
		DWORD dwTextColor;
		DWORD dwBkColor;
		CStdString sBkImage;
		CStdString sForeImage;
		DWORD dwAlternateTextColor;
		DWORD dwAlternateBkColor;
		CStdString sAlternateBkImage;
		bool bAlternateBk;
		DWORD dwSelectedTextColor;
		DWORD dwSelectedBkColor;
		CStdString sSelectedImage;
		DWORD dwHotTextColor;
		DWORD dwHotBkColor;
		CStdString sHotImage;
		DWORD dwDisabledTextColor;
		DWORD dwDisabledBkColor;
		CStdString sDisabledImage;
		DWORD dwLineColor;
		bool bShowHtml;
		bool bMultiExpandable;
	} TUIListInfo;

	typedef struct tagTUIListItemInfo
	{
		CStdString sFont;
		UINT uTextStyle;
		int nGlowSize;
		RECT rcTextPadding;
		DWORD dwTextColor;
		DWORD dwBkColor;
		CStdString sBkImage;
		CStdString sForeImage;
		DWORD dwSelectedTextColor;
		DWORD dwSelectedBkColor;
		CStdString sSelectedImage;
		DWORD dwHotTextColor;
		DWORD dwHotBkColor;
		CStdString sHotImage;
		DWORD dwDisabledTextColor;
		DWORD dwDisabledBkColor;
		CStdString sDisabledImage;
		bool bShowHtml;
	} TUIListItemInfo;

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class IUIListOwner
	{
	public:
		virtual TUIListInfo* GetListInfo() = 0;
		virtual int GetCurSel() const = 0;
		virtual bool SelectItem(int iIndex, bool bTakeFocus = false) = 0;
		virtual void DoEvent(TUIEvent& event) = 0;
	};

	class IUIList : public IUIListOwner
	{
	public:
		virtual CUIListHeader* GetHeader() const = 0;
		virtual CUIListBody* GetList() const = 0;
		virtual bool ExpandItem(int iIndex, bool bExpand = true) = 0;
		virtual int GetExpandedItem() const = 0;
	};

	class IUIListItem
	{
	public:
		virtual int GetIndex() const = 0;
		virtual void SetIndex(int iIndex) = 0;
		virtual IUIListOwner* GetOwner() = 0;
		virtual void SetOwner(CUIControl* pOwner) = 0;
		virtual bool IsSelected() const = 0;
		virtual bool Select(bool bSelect = true) = 0;
		virtual bool IsExpanded() const = 0;
		virtual bool Expand(bool bExpand = true) = 0;
		virtual CStdString GetItemText(int nIndex = 0) = 0;
		virtual void DrawItemText(HDC hDC, const RECT& rcItem) = 0;
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//

	class CUIListBody;
	class CUIListHeader;

	class DUISHARP_API CUIList : public CUIVerticalLayout, public IUIList
	{
	public:
		CUIList();

		LPCTSTR GetClass() const;
		UINT GetControlFlags() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		bool GetScrollSelect();
		void SetScrollSelect(bool bScrollSelect);
		int GetCurSel() const;
		bool SelectItem(int iIndex, bool bTakeFocus = false);

		CUIListHeader* GetHeader() const;  
		CUIListBody* GetList() const;
		TUIListInfo* GetListInfo();
		void SetListInfo(TUIListInfo Info);

		CUIControl* GetItemAt(int iIndex) const;
		int GetItemIndex(CUIControl* pControl) const;
		bool SetItemIndex(CUIControl* pControl, int iIndex);
		int GetCount() const;
		bool Add(CUIControl* pControl);
		bool AddAt(CUIControl* pControl, int iIndex);
		bool Remove(CUIControl* pControl);
		bool RemoveAt(int iIndex);
		void RemoveAll();
		bool Sort(LPSORTPROC Proc, LPVOID pData = NULL);

		void EnsureVisible(int iIndex);
		void Scroll(int dx, int dy);

		int GetChildPadding() const;
		void SetChildPadding(int iPadding);

		void SetItemFont(LPCTSTR pstrFont);
		void SetItemTextStyle(UINT uStyle);
		void SetItemTextPadding(RECT rc);
		void SetItemTextColor(DWORD dwTextColor);
		void SetItemBkColor(DWORD dwBkColor);
		void SetItemBkImage(LPCTSTR pStrImage);
		void SetItemForeImage(LPCTSTR pStrImage);
		void SetItemAlternateTextColor(DWORD dwTextColor);
		void SetItemAlternateBkColor(DWORD dwBkColor);
		void SetItemAlternateBkImage(LPCTSTR pStrImage);
		void SetAlternateBk(bool bAlternateBk);
		void SetSelectedItemTextColor(DWORD dwTextColor);
		void SetSelectedItemBkColor(DWORD dwBkColor);
		void SetSelectedItemImage(LPCTSTR pStrImage); 
		void SetHotItemTextColor(DWORD dwTextColor);
		void SetHotItemBkColor(DWORD dwBkColor);
		void SetHotItemImage(LPCTSTR pStrImage);
		void SetDisabledItemTextColor(DWORD dwTextColor);
		void SetDisabledItemBkColor(DWORD dwBkColor);
		void SetDisabledItemImage(LPCTSTR pStrImage);
		void SetItemLineColor(DWORD dwLineColor);
		void SetItemGlowSize(int iGlowSize);
		void SetItemShowHtml(bool bShowHtml = true);

		bool IsItemShowHtml();
		UINT GetItemTextStyle() const;
		RECT GetItemTextPadding() const;
		DWORD GetItemTextColor() const;
		DWORD GetItemBkColor() const;
		LPCTSTR GetItemBkImage() const;
		LPCTSTR GetItemForeImage() const;
		bool IsAlternateBk() const;
		DWORD GetSelectedItemTextColor() const;
		DWORD GetSelectedItemBkColor() const;
		LPCTSTR GetSelectedItemImage() const;
		DWORD GetHotItemTextColor() const;
		DWORD GetHotItemBkColor() const;
		LPCTSTR GetHotItemImage() const;
		DWORD GetDisabledItemTextColor() const;
		DWORD GetDisabledItemBkColor() const;
		LPCTSTR GetDisabledItemImage() const;
		DWORD GetItemLineColor() const;
		int GetItemGlowSize() const;

		void SetMultiExpanding(bool bMultiExpandable); 
		int GetExpandedItem() const;
		bool ExpandItem(int iIndex, bool bExpand = true);

		void SetPos(RECT rc);
		void DoEvent(TUIEvent& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		SIZE GetScrollPos() const;
		SIZE GetScrollRange() const;
		void SetScrollPos(SIZE szPos);
		void LineUp();
		void LineDown();
		void PageUp();
		void PageDown();
		void HomeUp();
		void EndDown();
		void LineLeft();
		void LineRight();
		void PageLeft();
		void PageRight();
		void HomeLeft();
		void EndRight();
		void EnableScrollBar(bool bEnableVertical = true, bool bEnableHorizontal = false);
		virtual CUIScrollBar* GetVerticalScrollBar() const;
		virtual CUIScrollBar* GetHorizontalScrollBar() const;

	protected:
		bool m_bScrollSelect;
		int m_iCurSel;
		int m_iExpandedItem;
		CUIListBody* m_pList;
		CUIListHeader* m_pHeader;
		TUIListInfo m_ListInfo;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CUIListBody : public CUIVerticalLayout
	{
	public:
		CUIListBody(CUIList* pOwner);

		virtual bool Sort(LPSORTPROC Proc, LPVOID pData = NULL);

		void SetScrollPos(SIZE szPos);
		void SetPos(RECT rc);
		void DoEvent(TUIEvent& event);

	protected:
		CUIList* m_pOwner;
	};

	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CUIListHeader : public CUIHorizontalLayout
	{
	public:
		CUIListHeader();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		SIZE EstimateSize(SIZE szAvailable, bool bSized = true);
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//

	class DUISHARP_API CUIListHeaderItem : public CUIButton
	{
	public:
		CUIListHeaderItem();

	public:
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);
		UINT GetControlFlags() const;

		void SetEnabled(bool bEnable = true);

		bool IsDragable() const;
		void SetDragable(bool bDragable);
		DWORD GetSepWidth() const;
		void SetSepWidth(int iWidth);

		LPCTSTR GetSepImage() const;
		void SetSepImage(LPCTSTR pStrImage);

		void DoEvent(TUIEvent& event);
		SIZE EstimateSize(SIZE szAvailable, bool bSized = true);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);
		RECT GetThumbRect() const;

		void PaintStatusImage(HDC hDC);

	protected:
		UINT m_uDragState;
		POINT m_ptLastMouse;
		bool m_bDragable;
		int m_iSepWidth;
		CStdString m_sSepImage;
		CStdString m_sSepImageModify;
	};


	/////////////////////////////////////////////////////////////////////////////////////
	//
	class DUISHARP_API CUIListItem : public CUIHorizontalLayout, public IUIListItem
	{
	public:
		CUIListItem();

	public:
		LPCTSTR GetClass() const;
		UINT GetControlFlags() const;
		LPVOID GetInterface(LPCTSTR pstrName);

	public:
		virtual SIZE EstimateSize(SIZE szAvailable, bool bSized = true);
		virtual bool Activate();

		CStdString GetItemText(int nIndex = 0);
		void SetItemText(int nIndex, LPCTSTR pstrText);

	public:
		IUIListOwner* GetOwner();
		void SetOwner(CUIControl* pOwner);
		void SetVisible(bool bVisible = true);
		void SetEnabled(bool bEnable = true);
		int GetIndex() const;
		void SetIndex(int iIndex);
		virtual bool IsSelected() const;
		virtual bool Select(bool bSelect = true);
		bool IsExpanded() const;
		bool Expand(bool bExpand = true);
		
	public:
		bool IsItemStyle() const;
		void SetItemStyle(bool bStyle);
		LPCTSTR GetItemFont() const;
		void SetItemFont(LPCTSTR pstrFont);
		UINT GetItemTextStyle() const;
		void SetItemTextStyle(UINT uStyle);
		RECT GetItemTextPadding() const;
		void SetItemTextPadding(RECT rc);
		DWORD GetItemTextColor() const;
		DWORD GetItemBkColor() const;
		LPCTSTR GetItemBkImage() const;
		void SetItemTextColor(DWORD dwTextColor);
		void SetItemBkColor(DWORD dwBkColor);
		void SetItemBkImage(LPCTSTR pStrImage);
		void SetItemForeImage(LPCTSTR pStrImage);
		LPCTSTR GetItemForeImage();
		DWORD GetSelectedItemTextColor() const;
		DWORD GetSelectedItemBkColor() const;
		LPCTSTR GetSelectedItemImage() const;
		void SetSelectedItemTextColor(DWORD dwTextColor);
		void SetSelectedItemBkColor(DWORD dwBkColor);
		void SetSelectedItemImage(LPCTSTR pStrImage);
		DWORD GetHotItemTextColor() const;
		DWORD GetHotItemBkColor() const;
		LPCTSTR GetHotItemImage() const;
		void SetHotItemTextColor(DWORD dwTextColor);
		void SetHotItemBkColor(DWORD dwBkColor);
		void SetHotItemImage(LPCTSTR pStrImage);
		DWORD GetDisabledItemTextColor() const;
		DWORD GetDisabledItemBkColor() const;
		LPCTSTR GetDisabledItemImage() const;
		void SetDisabledItemTextColor(DWORD dwTextColor);
		void SetDisabledItemBkColor(DWORD dwBkColor);
		void SetDisabledItemImage(LPCTSTR pStrImage);
		int GetItemGlowSize() const;
		void SetItemGlowSize(int iGlowSize);
		bool IsItemShowHtml() const;
		void SetItemShowHtml(bool bShowHtml);

	public:
		void DoEvent(TUIEvent& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		virtual void PaintBkImage(HDC hDC);
		virtual void PaintForeImage(HDC hDC);
		virtual void PaintText(HDC hDC);
		virtual void DrawStyleItemBk(HDC hDC, const RECT& rcItem);
		virtual void DrawStyleItemText(HDC hDC, const RECT& rcItem);
		virtual void DrawItemBk(HDC hDC, const RECT& rcItem);
		virtual void DrawItemText(HDC hDC, const RECT& rcItem);

	protected:
		bool m_bSelected;
		bool m_bItemStyle;
		int m_iIndex;
		UINT m_uButtonState;
		IUIListOwner* m_pOwner;
		TUIListItemInfo m_ItemInfo;
		CStdPtrArray m_aTexts;
	};
} // namespace duisharp

#endif // __UILIST_H__
