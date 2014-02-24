#ifndef __UITREE_H__
#define __UITREE_H__

namespace duisharp {

	//////////////////////////////////////////////////////////////////////
	//
	class CUITreeElement;

	class DUISHARP_API CUITree : public CUIList
	{
	public:
		CUITree();

	public:
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

	public:
		virtual bool Add(CUIControl* pControl);
		virtual bool Add(CUIControl* pRoot, CUIControl* pControl);
		virtual bool AddAt(CUIControl* pControl, int iIndex);
		virtual bool AddAt(CUIControl* pRoot, CUIControl* pControl, int iIndex);
		virtual bool Remove(CUIControl* pControl);

	public:
		virtual bool OnCheckBtnSelectChanged(void* param);
		virtual bool OnExpandBtnSelectChanged(void* param);
		virtual bool OnElementMsg(void * param);

		virtual bool SetItemCheck(CUITreeElement* pTreeItem, bool bSelected);
		virtual bool SetItemExpand(CUITreeElement* pTreeItem, bool bExpand = true);
		virtual bool SetItemExpand(int iIndex, bool bExpand = true);

		virtual void SetExpandVisible(bool bEnabled = true);
		virtual bool IsExpandVisible() const;
		virtual void SetCheckVisible(bool bEnabled = false);
		virtual bool IsCheckVisible() const;
		virtual bool IsClickExpand() const;
		virtual void SetClickExpand(bool bClick);

		virtual void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	private:
		bool m_bExpandVisible;
		bool m_bCheckVisible;
		bool m_bClickExpand;
		bool m_bExpanding;
	};

	//////////////////////////////////////////////////////////////////////
	//
	class DUISHARP_API CUITreeElement : public CUIListElement
	{
		typedef CUIListElement theBase;
	public:
		CUITreeElement();
		~CUITreeElement();

	public:
		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

	public:
		virtual bool Add(CUIControl* pControl);

		virtual int AddChildItem(CUIControl* pControl);
		virtual int AddChildItemAt(CUIControl* pControl, int iIndex);
		virtual bool RemoveChildItem(CUIControl* pControl);
		virtual void RemoveChildItemAll();

		int GetChildItemIndex(CUIControl* pControl);
		CUITreeElement* GetChildItemAt(int nIndex);
		CStdPtrArray GetChildItems();
		virtual bool HasChildItem() const;
		virtual int	GetChildItemCount() const;
		
		virtual CUITreeElement* GetParentItem() const;
		virtual void SetParentItem(CUITreeElement* pTreeItem);
		virtual void SetChildItemVisible(bool bVisible);
		virtual bool IsChildItemVisible() const;

	public:
		virtual void SetIndentBtnVisible(bool bVisible);
		virtual bool IsIndentBtnVisible();
		virtual void SetExpandVisible(bool bVisible);
		virtual bool IsExpandVisible();
		virtual void SetCheckVisible(bool bVisible);
		virtual bool IsCheckVisible();

		virtual void SetTree(CUITree *pOwner);
		virtual CUITree* GetTree() const;

		virtual void SetIndent(int nIndent);
		virtual int GetIndent() const;
		
		virtual void SetCheck(bool bChecked);
		virtual bool IsChecked() const;
					 
		virtual bool SetExpand(bool bExpanded);
		virtual bool IsExpanded() const;

		virtual void SetChildIndent(int nIndent);
		virtual int GetChildIndent() const;

		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

		virtual void DrawStyleItemText(HDC hDC, const RECT& rcItem);
		virtual void DrawItemText(HDC hDC, const RECT& rcItem);

	protected:
		void LayoutChild();

	protected:
		bool m_bChildVisible;
		int m_nChildIndent;
		CUIButton* m_pIndentBtn;
		CUIButton* m_pExpandBtn;
		CUIButton* m_pCheckBtn;

		CUITree* m_pTree;
		CUITreeElement* m_pParentItem;
		CStdPtrArray m_aChildItems;
	};
}

#endif // __UITREE_H__
