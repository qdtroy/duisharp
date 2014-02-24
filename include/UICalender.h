#ifndef __UICALENDER_H__
#define __UICALENDER_H__

namespace duisharp {
	/////////////////////////////////////////////////////////////////////////////////////
	//

	class CCalenderWnd;
	class CCalenderEdit;

	class DUISHARP_API CUICalender : public CUIButton
	{
		friend CCalenderWnd;
		friend CCalenderEdit;
	public:
		CUICalender();

		LPCTSTR GetClass() const;
		LPVOID GetInterface(LPCTSTR pstrName);

		virtual void CreateEdit();
		virtual void DestroyEdit();
		virtual RECT CalEditPos();
		virtual void CloseDropBox();

		void DoInit();
		UINT GetControlFlags() const;

		CStdString GetDropBoxAttributeList();
		void SetDropBoxAttributeList(LPCTSTR pstrList);
		SIZE GetDropBoxSize() const;
		void SetDropBoxSize(SIZE szDropBox);
		bool IsDropList() const;
		void SetDropList(bool bDropList);
		
		bool Activate();

		void SetNativeEditBkColor(DWORD dwBkColor);
		DWORD GetNativeEditBkColor() const;

		void SetComposited(bool bComposited);
		bool IsComposited() const;

		LPCTSTR GetItemNormalImage() const;
		void SetItemNormalImage(LPCTSTR pStrImage);
		LPCTSTR GetItemHotImage() const;
		void SetItemHotImage(LPCTSTR pStrImage);
		LPCTSTR GetItemPushedImage() const;
		void SetItemPushedImage(LPCTSTR pStrImage);
		LPCTSTR GetItemFocusedImage() const;
		void SetItemFocusedImage(LPCTSTR pStrImage);
		LPCTSTR GetItemDisabledImage() const;
		void SetItemDisabledImage(LPCTSTR pStrImage);
		LPCTSTR GetItemSelectedImage() const;
		void SetItemSelectedImage(LPCTSTR pStrImage);
		LPCTSTR GetItemSelectedHotImage();
		void SetItemSelectedHotImage(LPCTSTR pStrImage);
		LPCTSTR GetItemSelectedPushedImage();
		void SetItemSelectedPushedImage(LPCTSTR pStrImage);
		LPCTSTR GetItemSelectedFocusedImage();
		void SetItemSelectedFocusedImage(LPCTSTR pStrImage);
		LPCTSTR GetItemSelectedDisabledImage();
		void SetItemSelectedDisabledImage(LPCTSTR pStrImage);

		SIZE EstimateSize(SIZE szAvailable, bool bSized = true);
		void SetPos(RECT rc);
		void DoEvent(TUIEvent& event);
		void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

	protected:
		CCalenderWnd* m_pWindow;
		CCalenderEdit* m_pEdit;
		
		bool m_bDropList;
		bool m_bComposited;
		SIZE m_szDropBox;
		DWORD m_dwEditbkColor;
		CStdString m_sDropBoxAttributes;

		CStdString m_sItemNormalImage;
		CStdString m_sItemHotImage;
		CStdString m_sItemPushedImage;
		CStdString m_sItemFocusedImage;
		CStdString m_sItemDisabledImage;
		CStdString m_sItemSelectedImage;
		CStdString m_sItemSelectedHotImage;
		CStdString m_sItemSelectedPushedImage;
		CStdString m_sItemSelectedFocusedImage;
		CStdString m_sItemSelectedDisabledImage;
	};

} // namespace duisharp

#endif // __UICOMBO_H__
